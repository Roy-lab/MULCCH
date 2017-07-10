//
//  countNum.h
//  consensusClustering
//
//  Created by Zhen Niu on 9/22/14.
//  Copyright (c) 2014 Zhen Niu. All rights reserved.
//

#ifndef __consensusClustering__countNum__
#define __consensusClustering__countNum__

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include "Matrix.h"
#endif /* defined(__consensusClustering__countNum__) */
using namespace std;

class countNum
{
public:
    countNum(Matrix* totalMatrix);
    ~countNum();
    int addFile1(string filename,bool firstime=false);
    int addFile2(string filename,bool firstime=false);
    int addAll(string fileList,int type);
    int writeResult(string vector);
    int addMatrix(string filename);
private:
    Matrix * totalMatrix;

    vector<string> geneList;
    int dim;
};

