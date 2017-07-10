//
//  generateEigenvector.cpp
//  consensusClustering
//
//  Created by Zhen Niu on 9/22/14.
//  Copyright (c) 2014 Zhen Niu. All rights reserved.
//

#include "generateEigenvector.h"
EigenVector::EigenVector(Matrix *similarity)
{
    this->Similarity=similarity;
    this->dim=Similarity->getColCnt();
}
EigenVector::EigenVector()
{
    
}
EigenVector::~EigenVector()
{
    delete Degree;
    delete LaplacianMatrix;
    delete EGvector;
    delete EGvalue;
}

int EigenVector::inputSimilarityMatrix(Matrix *similarity)
{
   this->Similarity=similarity;
   this->dim=Similarity->getColCnt();
   return 0;
}
int EigenVector::setSimilarityMatrix(double th, int binary)
{
   for(int i=0;i<dim;i++){
   for(int j=0;j<dim;j++){
if(Similarity->getValue(i, j)>=th)
{
if(binary==1)
Similarity->setValue(1, i, j);
}
else
Similarity->setValue(0, i, j);

}
}
return 0;
}

int EigenVector::generateDegreeMatrix()
{
    Degree=new Matrix(dim,dim);
    Degree->setAllValues(0);
    
    for(int i=0;i<dim;i++)
    {
        int degree=0;
        int j=0;
        for(;j<dim;j++)
        {
           degree+=Similarity->getValue(i, j);
 //cout<<degree<<endl;
 //cout<<Similarity->getValue(i, j)<<endl<<endl;  
      }
        Degree->setValue(degree, i, i);
    
    }
    return 0;
}
//flag==1 unnormalized ==2 normalized
int EigenVector::generateLaplacianMatrix(int flag)
{
   //Similarity->showMatrix();

   //Degree->showMatrix();
   LaplacianMatrix=Degree->subtractMatrix(Similarity);
   
  if (flag==1)
  {
  for (int i=0;i<dim;i++) 
  {
  double v=Degree->getValue(i,i);
  Degree->setValue(sqrt(1/v),i,i);
  }
  //Degree->showMatrix();
  Matrix * temp=Degree->multiplyMatrix(LaplacianMatrix);
  delete LaplacianMatrix;
  //temp->showMatrix();
  LaplacianMatrix=temp->multiplyMatrix(Degree);
  //LaplacianMatrix->showMatrix();
  delete temp;

  }
 // LaplacianMatrix->showMatrix();
  return 0;
}


int EigenVector::generateEigenvector()
{
    gsl_vector *eval = gsl_vector_alloc (dim);
    //every column is one eigen vector
    gsl_matrix *evec = gsl_matrix_alloc (dim, dim);
    
    gsl_eigen_symmv_workspace * w =gsl_eigen_symmv_alloc (dim);
    
    gsl_eigen_symmv (LaplacianMatrix->matrix, eval, evec, w);
    
    gsl_eigen_symmv_free (w);
    gsl_eigen_symmv_sort (eval, evec,GSL_EIGEN_SORT_ABS_ASC);
    
    EGvalue=new Matrix(dim,1);
    EGvector=new Matrix(dim,dim);
   int i=0;
   int j=0; 
   for (i=0; i<dim; i++) {
      double v=gsl_vector_get(eval,i);  
      EGvalue->setValue(v,i,0);
           
 for (j=0; j<dim; j++) {
             v=gsl_matrix_get(evec,i,j);
             EGvector->setValue(v,i,j);
         }
    }
    gsl_matrix_free (evec);
    gsl_vector_free (eval);

 return 0;
}

int EigenVector::writeResult(string vector,string value)
{
   const char *vect = vector.c_str();
  const char *val = value.c_str();    

    ofstream file(vect);
    ofstream file2(val);
    string writevector="";
    string writevalue="";
    for (int i=0; i<dim; i++)
    {
        ostringstream ss;
        
        double v=EGvalue->getValue(i, 0);
        ss<<v;
        writevalue+=ss.str()+"\n";
        for (int j=0; j<dim; j++)
        {
            ostringstream ss;
            
            double v=EGvector->getValue(i, j);
            ss<<v;
            writevector+=ss.str()+"\t";
        }
        writevector+="\n";
        
    }
    file.write(writevector.c_str(), writevector.size());
    file2.write(writevalue.c_str(), writevalue.size());
    return 0;
}





