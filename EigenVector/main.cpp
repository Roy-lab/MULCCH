//
//  main.cpp
//  consensusClustering
//
//  Created by Zhen Niu on 9/21/14.
//  Copyright (c) 2014 Zhen Niu. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include "generateEigenvector.h"
#include "countNum.h"

int startEigen(string filenames,Matrix * totalMatrix,string output,string simi,int normal,double threshold, int binary);
int main(int argc, char **argv)
{

	if (argc!=13) {
		cout<<"Usage:./Eigen[-s similarity file | -l file list] -d dimension -n [0|1] normalize -t threshold -b binary -o outfile\n";
		return 1;
	}
	char c;
	string filenames;
	int geneNum; 
	string output;
	string s="NULL";
	int normal=1;
	double threshold=0;
	int binary=0;
	while ((c = getopt (argc, argv, "t:b:d:s:l:n:o:")) != -1)
		switch (c)
		{
			case 'n':
				normal=atoi(optarg);
				break;
			case 's':
				s=optarg;
				break;
			case 'l':
				filenames=optarg;
				break;
			case 'd':
				geneNum=atoi(optarg);
				break;
			case 'o':
				output =optarg;
				break;
			case 't':
				threshold=atof(optarg);
				break;
			case 'b':
				binary=atoi(optarg);
				break;
			case '?':
				cout<<"Usage:./Eigen[-s similarity file | -l file list] -d dimension -n [0|1] normalize -o outfile\n";
		}
	Matrix * totalMatrix=new Matrix(geneNum,geneNum);

	startEigen(filenames, totalMatrix,output,s,normal,threshold, binary);
	return 0;
}

int startEigen(string filenames,Matrix * totalMatrix,string output,string simi,int normal,double threshold, int binary)
{

	countNum c=countNum(totalMatrix);
	cout<<"start add file."<<endl;
	if (simi.compare("NULL")==0){
		c.addAll(filenames, 1);
		cout<<"writing result of similarity matrix."<<endl;
		c.writeResult(output+"_similarity.txt");
	}
	else
   c.addMatrix(simi);
    
    cout<<"start compute eigenvalue."<<endl;
    EigenVector e=EigenVector(totalMatrix);
 
   if(threshold>0){
    cout<<"adjusting similarity matrix by threshold"<<endl;
    e.setSimilarityMatrix(threshold, binary);
   } 
   // EigenVector e=EigenVector(totalMatrix);
    cout<<"generating degree matrix."<<endl;
    e.generateDegreeMatrix();
    cout<<"generating laplacian matrix."<<endl;
    e.generateLaplacianMatrix(normal);
    cout<<"computing eigenvalue."<<endl;
    e.generateEigenvector();
    cout<<"writing result of eigenvalue."<<endl;
    string Vect=output+"_vector.txt";
    string Val=output+"_value.txt";
    e.writeResult(Vect,Val);
    return 0;
}



