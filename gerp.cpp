/*
*  gerp.cpp
*  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
*  4/12/2023
*
*  CS 15 PROJECT 4 gerp
*
*  FILE PURPOSE:
*  This file defines the implementation of our Gerp class, which is responsible 
*  for searching for lines of text across a set of files in a given directory
*  The Gerp class has several functions, including a constructor and 
*  destructor, a function for reading files from a given directory, querying 
*  the user for the search function, opening a file, traversing a given 
*  directory tree, and inserting the contents of a file into the search table.
* 
*/

#include "gerp.h"
#include <fstream>
#include <sstream>

/*
 * name:      Gerp 
 * purpose:   constructor for the files
 * arguments: none
 */
Gerp::Gerp() { 
    std::vector<std::vector<std::string>*> fileList;
    files = fileList;
}

/*
 * name:      ~Gerp 
 * purpose:   destructor for the files
 * arguments: none
 */
Gerp::~Gerp() {
    // iterates over the files to delete them
    for (std::vector<std::vector<std::string>*>::iterator it = files.begin(); 
         it != files.end(); ++it) {
        delete *it;
    }
}

/*
 * name:      readFiles 
 * purpose:   reads in the files using FSTreeTraversal into a tree
 * arguments: directory to index as a string
 */
void Gerp::readFiles(std::string directory) {
    try {
        FSTree dir(directory);
        FSTreeTraversal(dir.getRoot(), "");
    } catch (std::runtime_error &e) {
        std::cout << "Could not build index, exiting.\n";
        exit(EXIT_FAILURE);
    }
}

/*
 * name:      queryLoop 
 * purpose:   takes in a query and responds to query
 * arguments: name of file to write to
 */
void Gerp::queryLoop(std::string output) {
    std::ofstream outfile(output);
    std::string query = "";
    std::cout << "Query? ";
    std::cin >> query;
    while ((query != "@q") and (query != "@quit")) {
        if (query == "@i" or query == "@insensitive") {
            std::cin >> query;
            query = table.stripNonAlphaNum(query);
            std::set<lineLoc> *results = table.search(query, false);
            if (results == nullptr) {
                error(query, outfile, true);
            } else {
                writeOut(results, outfile);
            }
        } else if (query == "@f") {
            std::cin >> query;
            outfile = changeOutput(outfile, query);
        } else {
            query = table.stripNonAlphaNum(query);
            std::set<lineLoc> *results = table.search(query, true);
            if (results == nullptr) {
                error(query, outfile, false);
            } else {
                writeOut(results, outfile);
            }
        }
        std::cout << "Query? ";
        std::cin >> query;
    }
}

/*
 * name:      error 
 * purpose:   prints out an error message if the query was not found
 * arguments: inputted query, file to write to, type of search as a bool
 */
void Gerp::error(std::string query, std::ofstream &outputFile, bool sensitive) {
    if (sensitive) {
        outputFile << query << " Not Found.\n";
    } else {
        outputFile << query << " Not Found. Try with @insensitive or @i.\n";
    }
}

/*
 * name:      writeOut 
 * purpose:   writes out the data into the outputFile
 * arguments: set of the word's instances, file to write to
 */
void Gerp::writeOut(std::set<lineLoc> *results, std::ofstream &outputFile) {
    // writes into the outputFile the results of what the program has found
    for (std::set<lineLoc>::iterator it=results->begin(); 
         it!=results->end(); ++it) {
        outputFile << it->table->at(0) << ":" << it->line << ": ";
        outputFile << it->table->at(it->line) << "\n";  
    }
}

/*
 * name:      changeOutput 
 * purpose:   changes the outputFile
 * arguments: filestream currently writing to, name of new file to write to
 * returns:   ofstream of the new file
 */
std::ofstream Gerp::changeOutput(std::ofstream &outfile, std::string newFile) {
    // changes the outfile
    outfile.close();
    std::ofstream newStream(newFile);
    return newStream;
}

/*
 * name:      openFile 
 * purpose:   opens the files for reading
 * arguments: name of file to open
 * returns:   infile input stream to read from
 */
std::ifstream Gerp::openFile(std::string filename) {
    // opens a new file
    std::ifstream infile;
    infile.open(filename);
    
    if (not infile) {
        // if not able to open throw a runtime error
        std::stringstream ss;
        ss << "Unable to open file " << filename;
        throw std::runtime_error(ss.str());
    }

    return infile;
}

/*
 * name:      FSTreeTraversal
 * purpose:   creates a tree using the directoryNode and traverses through it 
 *            getting the files
 * arguments: current directory that you are indexing, path to that dirNode
 */
void Gerp::FSTreeTraversal(DirNode *curr, std::string path) {
    // goes through the directory and creates a path to each subdirectory
    for (int i = 0; i < curr->numSubDirs(); i++) {
        FSTreeTraversal(curr->getSubDir(i), path + curr->getName() + "/");
    }

    // opens the files and sends it into insertToFiles to be read for hashing
    for (int i = 0; i < curr->numFiles(); i++) {
        std::ifstream infile = openFile(path + curr->getName() + "/" 
                                        + curr->getFile(i));
        insertToFiles(infile, path + curr->getName() + "/" + curr->getFile(i));
        infile.close();
    }
}

/*
 * name:      insertToFiles 
 * purpose:   it takes a file and inserts it into a vector where the first 
 *            element is the name and the preceeding elements in the vector are 
 *            each a line of the file
 * arguments: filestream to read from, name of the file
 */
void Gerp::insertToFiles(std::istream &infile, std::string name) {
    int lineNum = 1;
    std::string line = "";
    std::vector<std::string> *curr_file = new std::vector<std::string>;

    // inserts the files to be read for hashing
    curr_file->push_back(name);

    while (std::getline(infile, line)) {
        curr_file->push_back(line);
        table.insertToTable(line, lineNum, *curr_file);
        lineNum++;
    }

    files.push_back(curr_file);
}
