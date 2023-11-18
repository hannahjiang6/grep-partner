/*
*  hash.h
*  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
*  4/12/2023
*
*  CS 15 PROJECT 4 gerp
*
*  FILE PURPOSE:
*  This file is our interface for the hash class. It holds all the functions 
*  that will be used for our hash table, and ultimately our gerp file.
* 
*/

#ifndef __HASH_H__
#define __HASH_H__

#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <set> 

#include "FSTree.h"

struct lineLoc {
    std::vector<std::string> *table;
    int line;
    std::string key;

    // lineLoc default constructor
    lineLoc() {
        table = nullptr;
        line = 0;
        key = "";
    };

    // lineLoc constructor
    lineLoc(std::vector<std::string> *Table, int Line, std::string Key) {
        table = Table;
        line = Line;
        key = Key;
    }
    
    // Define the less-than operator for lineLoc
    bool operator<(const lineLoc& other) const {
        if (table == other.table) {
            return line < other.line;
        }
        return table < other.table;
    }

    // Define the equality operator for lineLoc
    bool operator==(const lineLoc& other) const {
        return table == other.table && line == other.line && key == other.key;
    }
}; 

class Hash {
public:
    // constructor
    Hash();

    // destructor
    ~Hash();
    
    // public functions
    void insertToTable(std::string line, int lineNum, 
                       std::vector<std::string> &file);
    std::set<lineLoc> *search(std::string query, bool sensitive);
    std::string stripNonAlphaNum(std::string input);

private:
    // declaring variables
    std::vector<std::list<std::set<lineLoc>>> table;
    std::vector<std::list<std::set<lineLoc>>> caseTable;
    std::hash<std::string> wordHash;

    // private functions
    void resize(int num);
    void resizeHelper(std::vector<std::list<std::set<lineLoc>>> &Table);
    std::set<lineLoc> *searchHelper(std::vector<std::list<std::set<lineLoc>>> 
                                    &Table, std::string query, int key);
    bool iterator(std::vector<std::list<std::set<lineLoc>>> &Table, 
                  lineLoc val, int key);

    void addBoth(lineLoc val, int key, int key_c);
    void insertValue(lineLoc val, int &key, int index);
};

#endif