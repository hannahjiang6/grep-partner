/*
*  gerp.h
*  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
*  4/12/2023
*
*  CS 15 PROJECT 4 gerp
*
*  FILE PURPOSE:
*  This file holds the interface for our Gerp class and its functions. It holds 
*  all the functions that will be used for reading files and inserting the data 
*  into the Hash table.
* 
*/

#ifndef __GERP_H__
#define __GERP_H__

#include "hash.h"

class Gerp {
public:
    // constructor
    Gerp();
    
    // destructor
    ~Gerp();

    // public functions
    void readFiles(std::string directory);
    void queryLoop(std::string output);

private:
    // declaring variables
    std::vector<std::vector<std::string>*> files;
    Hash table;

    // private functions
    void writeOut(std::set<lineLoc> *results, std::ofstream &outputFile);
    void error(std::string query, std::ofstream &outputFile, bool sensitive);
    void FSTreeTraversal(DirNode *curr, std::string path);
    void insertToFiles(std::istream &infile, std::string name);

    // file opening functions
    std::ifstream openFile(std::string filename);
    std::ofstream changeOutput(std::ofstream &outfile, std::string newFile);
    
};

#endif