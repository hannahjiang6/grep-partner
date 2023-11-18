/*
 *  unit_tests.h
 *  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
 *  4/12/2023
 *
 *  CS 15 PROJECT 4 gerp
 *
 *  FILE PURPOSE:
 *  File to test cases for our program: gerp
 *
 */

#include "stringProcessing.h"
#include "DirNode.h"
#include "hash.h"
#include "gerp.h"

#include <fstream>
#include <string>
#include <cassert>
#include <sstream>

void stringProcessing_test() {
    // removing with upper and lowercase letters intact
    std::string test_string = stripNonAlphaNum("#hAnnaH!@$");
    assert(test_string == "hAnnaH");

    // removing to an empty string
    std::string test_string2 = stripNonAlphaNum("#");
    assert(test_string2 == "");

    // removing so only alphabetical and numerical chars are left
    std::string test_string3 = stripNonAlphaNum("zAcK#!$@03");
    assert(test_string3 == "zAcK#!$@03");

    // removing before and after with stuff inbetween
    std::string test_string4 = stripNonAlphaNum("@##!!#!@!#COMP-15!!!!!!!");
    assert(test_string4 == "COMP-15");
}

// void traversalTest(){
//     DirNode root("");
//     DirNode sub("second");
//     root.addSubDirectory(&sub);
//     root.addFile("file1.cpp");
//     root.addFile("file2.cpp");
//     sub.addFile("file3.cpp");
//     FSTreeTraversal(&root, "");
// }

void insert() {
    // create a hash table
    Hash table;

    // create a file vector
    std::vector<std::string> file;
    file.push_back("This is a test file.");
    file.push_back("It contains several lines.");
    file.push_back("Each line is a string.");

    // insert lines into the hash table
    table.insertToTable("This is line one.", 1, file);
    table.insertToTable("This is line two.", 2, file);
    table.insertToTable("This is line three.", 3, file);

    std::cout << table.table.size();
    // assert(table.table.size() == 3);
}

void insert_sameline() {
    // create a hash table
    Hash table;

    // create a file vector
    std::vector<std::string> file;
    file.push_back("This is a test test test file.");
    file.push_back("It contains several lines.");
    file.push_back("Each line is a string.");

    // insert lines into the hash table
    table.insertToTable("This is line one.", 1, file);
    table.insertToTable("This is line two.", 2, file);
    table.insertToTable("This is line three.", 3, file);

    std::cout << table.table.size();
    // assert(table.table.size() == 3);
}

void search() {
    Hash hash;
    std::vector<std::string> file = {"This is a test file", 
                                     "For the hash class", 
                                     "To check its search function hash"};

    hash.insertToTable(file[0], 0, file);
    hash.insertToTable(file[1], 1, file);
    hash.insertToTable(file[2], 2, file);

    std::set<lineLoc> *results = hash.search("hash", true);

    for (auto i : *results) {
        std::cout << i.key << " " << i.line << std::endl;
    }
    
    assert((*results->begin()).line == 1);
    assert((*results->begin()).key == "hash");

    for (std::set<lineLoc>::iterator it=results->begin(); 
         it!=results->end(); ++it) {
        std::cout << " " << it->line;
        std::cout << " " << it->table->at(it->line);
        std::cout << '\n';  

    }

    // std::cout << results[0].table->at(1) << "\n";
}

void search_sameline() {
    Hash hash;
    std::vector<std::string> file = {"This is a test file", 
                                     "For the hash class", 
                                     "To check its search function hash hash"};

    hash.insertToTable(file[0], 0, file);
    hash.insertToTable(file[1], 1, file);
    hash.insertToTable(file[2], 2, file);

    std::set<lineLoc> *results = hash.search("hash", true);

    // for (auto i : *results) {
    //     std::cout << i.table->at(i.line) << std::endl;
    // }
    
    assert((*results->begin()).line == 1);
    assert((*results->begin()).key == "hash");
}

void search_empty() {
    Hash hash;

    std::vector<std::string> file = {""};

    hash.insertToTable(file[0], 0, file);

    std::set<lineLoc> *results = hash.search("hash", true);

    assert(results == nullptr);
}

void fileVecInsert(){
    Gerp tool;
    tool.readFiles("tinyData");
    if (!tool.files.empty()) {
        assert(tool.files.front()[0] == "tinyData/a/found");
    }
}

void printDirTree(DirNode *curr, std::string word = "") {
    std::cout << word << curr->getName() << "/" << std::endl;

    for (int i = 0; i < curr->numSubDirs(); i++) {
        printDirTree(curr->getSubDir(i), word + "  ");
    }
    for (int i = 0; i < curr->numFiles(); i++) {
        std::cout << word << "  " << curr->getFile(i) << std::endl;
    }
}

void testFSTreeTraversal() {
    FSTree tree("tinyData");
    DirNode *root = tree.getRoot();

    Gerp gerp;
    gerp.FSTreeTraversal(root, "");

    printDirTree(root, "");
}


void printAll() {
    Gerp hashTable;
    hashTable.readFiles("tinyData");
    std::set<lineLoc> *results = hashTable.table.search("gerp", true);

    for (std::set<lineLoc>::iterator it=results->begin(); 
         it!=results->end(); ++it) {
        std::cout << "line " << it->line << " ";
        std::cout << "line words " << it->table->front();
        std::cout << '\n';  
    }

}

void printAll2() {
    Gerp hashTable;
    hashTable.readFiles("tinyData");
    std::set<lineLoc> *results = hashTable.table.search("remember", false);

    for (std::set<lineLoc>::iterator it=results->begin(); 
         it!=results->end(); ++it) {
        std::cout << it->line << " ";
        std::cout << it->table->front() << " ";
        std::cout << it->table->at(it->line);
        std::cout << '\n';
    }

}

void insertToTable_test() {
    Hash hashTable;
    std::vector<std::string> file;
    std::string line = "\'\"Joke\'";
    int lineNum = 1;

    hashTable.insertToTable(line, lineNum, file);
}