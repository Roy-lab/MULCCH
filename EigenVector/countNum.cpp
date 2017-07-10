//
//  countNum.cpp
//  consensusClustering
//
//  Created by Zhen Niu on 9/22/14.
//  Copyright (c) 2014 Zhen Niu. All rights reserved.
//

#include "countNum.h"

countNum::countNum(Matrix* totalMatrix)
{
    this->totalMatrix=totalMatrix;
    dim=totalMatrix->getColCnt();
}
countNum::~countNum()
{
}
int countNum::addFile1(string filename,bool firstime)
{
    ifstream file;
    const char * name=filename.c_str();
    file.open(name);
    string str;
    if(!file.good())
    {
        cout<<"Can not open "<<filename<<endl;
        return 1;
    }
    map<string, int> gene2cluster;
    while (getline(file, str))
    {
        char * word = new char [str.length()+1];
        strcpy (word, str.c_str());
        char* strain= strtok (word,"\t");
        int cluster=atoi(strtok(NULL,"\t"));
        string gene=string(strain);
        gene2cluster[gene]=cluster;
        if (firstime==true)
        {
            geneList.push_back(gene);
        }
    }
    int i=0;
    int j=0;
    for (;i<dim; i++)
    {
        for (j=i; j<dim; j++)
        {
            if (gene2cluster[geneList.at(i)]==gene2cluster[geneList.at(j)])
            {
                double current=totalMatrix->getValue(i,j);
                totalMatrix->setValue(current+1,i,j);
                totalMatrix->setValue(current+1,j,i);
            }
        }
    }
    return 0;
}

int countNum::addFile2(string filename,bool firstime)
{
    ifstream file;
    const char * name=filename.c_str();
    file.open(name);
    string str;
    if(!file.good())
    {
        cout<<"Can not open "<<filename<<endl;
        return 1;
    }
    map<string, int> gene2cluster;
    int i=0;
    int j=0;
    while (getline(file, str))
    {
        j=0;
        char * word = new char [str.length()+1];
        strcpy (word, str.c_str());
        char* value= strtok (word,"\t");
        string gene=string(value);
        
        if (firstime==true)
        {
            geneList.push_back(gene);
        }
        
        value=strtok(NULL,"\t");
        
        while (value!=NULL)
        {
        totalMatrix->setValue(atof(value),i,j);
        value=strtok(NULL,"\t");
            j++;
        }
        i++;
    }
    return 0;
}
int countNum::addMatrix(string filename)
{
    ifstream file;
    const char * name=filename.c_str();
    file.open(name);
    string str;
    if(!file.good())
    {
        cout<<"Can not open "<<filename<<endl;
        return 1;
    }
    map<string, int> gene2cluster;
    int i=0;
    int j=0;
    while (getline(file, str) && i<dim)
    {
        j=0;
        char * word = new char [str.length()+1];
        strcpy (word, str.c_str());
        char* value= strtok (word,"\t");

        while (value!=NULL && j<dim)
        {
        totalMatrix->setValue(atof(value),i,j);
        value=strtok(NULL,"\t");
        j++;
        }
     i++;
    }
//totalMatrix->showMatrix(); 
return 0;
}                               
int countNum::addAll(string fileList,int type)
{
    ifstream file;
    const char * List=fileList.c_str();
    file.open(List);
    string str;
    if(!file.good())
    {
        cout<<"Can not open "<<fileList<<endl;
        return 1;
    }
    getline(file, str);
    int i=0;
    cout<<"adding "<<str<<endl;
    if (type==1)
    {
        if(addFile1(str,true)==0)
        i=1;
        while (getline(file, str))
        {
            cout<<"adding "<<str<<endl;
            if(addFile1(str)==0)
            i++;
        }

    }
    if (type==2)
    {
        if(addFile2(str,true)==0)
        i=1;
        while (getline(file, str))
        {
            cout<<"adding "<<str<<endl;
            if(addFile2(str)==0)
            i++;
        }
        
    }
    cout<<i<<" files added!"<<endl;
    
    return 0;    
}

int countNum::writeResult(string vector)
{
    const char * vect=vector.c_str();
    ofstream file(vect);
    string writevector="";
    
    for (int i=0; i<dim; i++)
    {
        for (int j=0; j<dim; j++)
        {
            stringstream ss;
            ss<<totalMatrix->getValue(i, j);
            writevector+=ss.str()+"\t";
        }
        writevector+="\n";
        
    }
    file.write(writevector.c_str(), writevector.size());
   
    return 0;
}



