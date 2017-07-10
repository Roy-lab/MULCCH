//
//  generateEigenvector.h
//  consensusClustering
//
//  Created by Zhen Niu on 9/22/14.
//  Copyright (c) 2014 Zhen Niu. All rights reserved.
//

#ifndef __consensusClustering__generateEigenvector__
#define __consensusClustering__generateEigenvector__

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Matrix.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <math.h> 
using namespace std;
#endif /* defined(__consensusClustering__generateEigenvector__) */

class EigenVector
{
public:
    EigenVector(Matrix *similarity);
    EigenVector();
    ~EigenVector();
    int inputSimilarityMatrix(Matrix *similarity);
    int generateDegreeMatrix();
    int generateLaplacianMatrix(int flag=1);
    int generateEigenvector();
    int writeResult(string vector,string value);
    int setSimilarityMatrix(double th, int binary);
    
private:
    Matrix* Similarity;
    Matrix* Degree;
    Matrix* LaplacianMatrix;
    Matrix* EGvector;
    Matrix* EGvalue;
    int dim;
    int k;
    
};
