/*
 *  FSTreeTraversal.cpp
 *  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
 *  4/12/2023
 *
 *  CS 15 PROJECT 4 gerp
 *
 *  FILE PURPOSE:
 *  Traverses over a provided directory, printing out all paths to files
 *  in its and all subdirectories. 
 * 
 */

#include <iostream>

#include "FSTree.h"

void FSTreeTraversal(DirNode *curr, std::string path);

int main(int argc, char *argv[]) {
    // check for valid input
    if (argc != 2) {
        std::cerr << "Usage: ./treeTraversal Directory\n";
        exit(EXIT_FAILURE);
    }

    std::string directory = argv[1];
    FSTree root(directory);
    DirNode *node = root.getRoot();
    FSTreeTraversal(node, "");
    
    return 0;
}

void FSTreeTraversal(DirNode *curr, std::string path){
    for(int i = 0; i < curr->numSubDirs(); i++){
        FSTreeTraversal(curr->getSubDir(i), path + curr->getName() + "/");
    }
    for(int i = 0; i < curr->numFiles(); i++){
        std::cout << "\n" << path << curr->getName() << "/" << curr->getFile(i);
    }
}