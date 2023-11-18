/*
*  hash.cpp
*  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
*  4/12/2023
*
*  CS 15 PROJECT 4 gerp
*
*  FILE PURPOSE:
*  This file contains the implementation of our hash class, which is used for 
*  indexing words in a text file. The class uses a hash function to map each 
*  word to a unique index, which is then used to store the word in a vector of 
*  lists of sets. Each set contains line locations where the word occurs in the 
*  file. The class also provides methods for resizing the hash table, searching 
*  for a word, and adding a new line location to the hash table. 
*  
*/

#include "hash.h"
#include <sstream>
#include <fstream>

/*
 * name:      Hash 
 * purpose:   intializes all structures in the hash tables
 * arguments: none
 */
Hash::Hash() {
    std::list<std::set<lineLoc>> tableRow;
    //makes the table with size 1000 to keep collisions low
    table.push_back(tableRow);
    table.resize(1000);
    //same as above
    std::list<std::set<lineLoc>> caseTableRow;
    caseTable.push_back(caseTableRow);
    caseTable.resize(1000);
    
    std::hash<std::string> newHash;
    wordHash = newHash;
}

/*
 * name:      ~Hash 
 * purpose:   destructor for the hash tables
 * arguments: none
 */
Hash::~Hash() {
    
}

/*
 * name:      resize 
 * purpose:   increases the capacity of one of the hash tables
 * arguments: number representing which table to resize
 */
void Hash::resize(int num) {
    // calls a helper function to resize based on type of hash table
    if (num == 1) {
        resizeHelper(table);
    } else {
        resizeHelper(caseTable);
    }
}

/*
 * name:      resizeHelper 
 * purpose:   resizes the hash tables based on which table it is
 * arguments: the Hash table to resize
 */
void Hash::resizeHelper(std::vector<std::list<std::set<lineLoc>>> &Table) {
    std::vector<std::list<std::set<lineLoc>>> new_table(table.size() * 2);

    // iterates over the vector
    for (auto &lst : Table) {\
        // iterates over the list
        for (auto &st : lst) {
            // iterates over the set
            for (auto &loc : st) {
                // resizes the table
                int new_key = wordHash(loc.key) % new_table.size();
                std::set<lineLoc> new_set;
                new_set.insert(loc);
                new_table[new_key].push_back(new_set);
            }
        }
    }

    Table = std::move(new_table);
}

/*
 * name:      insertToTable 
 * purpose:   inserts the words into the hashTable
 * arguments: text of a line, number of the line in the file,
 *            address of vector the file is stored in
 */
void Hash::insertToTable(std::string line, int lineNum,
                         std::vector<std::string> &file) {
    std::stringstream ss(line);
    std::string curr;
    // reads in the words from the file and adds them to the hash table
    while (ss >> curr) {
        // strips the queries of non-alpha-num characters
        curr = stripNonAlphaNum(curr);
        int key = wordHash(curr);
        lineLoc val(&file, lineNum, curr);
        for(int i = 0; i < static_cast<int>(curr.size()); i++){
            curr[i] = std::tolower(curr[i]);
        }
        // creates different keys based on the hash table it's being added into
        int key_c = wordHash(curr);
        key %= table.size();
        key_c %= caseTable.size();
        addBoth(val, key, key_c);
    }

    // resizes the tables if 66% of the capacity is reached
    if (table.size() > table.capacity() / 2 * 3) {
        resize(1);
    }
    if (caseTable.size() > caseTable.capacity() / 2 * 3) {
        resize(2);
    }
}

/*
 * name:      addBoth 
 * purpose:   adds the data/key for both the case sensitive and insensitive 
 *            cases into the hash table
 * arguments: Struct containing the data to be stored, case sensitive key, 
            case insensitive key int
 */
void Hash::addBoth(lineLoc val, int key, int key_c){
    bool found = iterator(table, val, key);

    if (not found) {
        insertValue(val, key, 1);
    }

    // turn the word into lowercase
    for (int i=0; i < static_cast<int>(val.key.size()); i++) {
        val.key[i] = std::tolower(val.key[i]);
    }

    found = iterator(caseTable, val, key_c);
    if (not found) {
        insertValue(val, key_c, 2);
    }
}

/*
 * name:      search 
 * purpose:   searches through the hash tables to find the word in the directory
 * arguments: the query as a string, bool of whether the search is case 
            sensitive or not
 * returns:  The set corresponding to the query containing lineLoc structs
 */
std::set<lineLoc> *Hash::search(std::string query, bool sensitive) {
    int key = wordHash(query);
    // searches different hash tables depending on if it is case sensitive
    if (sensitive) {
        key %= table.size();
        return searchHelper(table, query, key);
    } else {
        for(int i = 0; i < static_cast<int>(query.size()); i++){
            query[i] = std::tolower(query[i]);
        }
        key %= caseTable.size();
        return searchHelper(caseTable, query, key);
    }
}

/*
 * name:      searchHelper 
 * purpose:   helper for the search function to find the word
 * arguments: Table to search through, query provided by user, 
            key generated from the query
 * returns:   a set of structs
 */
std::set<lineLoc> *Hash::searchHelper
(std::vector<std::list<std::set<lineLoc>>> &Table, 
 std::string query, int key) {
    // base case if query is empty (e.g a stripped word !@# == "")
    if (query == "") {
        return nullptr;
    }

    // iterates over the table and returns the address of i if it finds the key
    for (auto &i : Table[key]) {
        auto it = i.begin();
        if (it != i.end() and it->key == query){
            return &i;
        }
    }
    return nullptr;
}

/*
 * name:      iterator 
 * purpose:   iterates over the table to check if the val already exists
 * arguments: table to iterate over, value to check for, key for value
 * returns:   bool whether the value exists in the table
 */
bool Hash::iterator(std::vector<std::list<std::set<lineLoc>>> &Table, 
                    lineLoc val, int key) {
    // iterates over table
    for (auto &i : Table[key]) {
        auto it = i.begin();
        // returns a bool depending on if the key was found or not
        if(it != i.end() and it->key == val.key) {
            i.insert(val);
            return true;
        }
    }
    return false;
}

/*
 * name:      insertValue 
 * purpose:   inserts the struct into the hash table
 * arguments: lineLoc to insert, the key for that value, table to insert to
 */
void Hash::insertValue(lineLoc val, int &key, int index) {
    std::set<lineLoc> s;
    s.insert(val);

    // inserts the struct to the back of the list
    if (index == 1) {
        table[key].push_back(s);
    } else {
        caseTable[key].push_back(s);
    }
}

/*
 * name:      stripNonAlphaNum 
 * purpose:   takes an inputted string and removes all preceeding and trailing 
 *            non alphabetical-numerical characters
 * arguments: string to be stripped
 * returns:   a substring of the inputted word without special characters
 */
std::string Hash::stripNonAlphaNum(std::string input) {
    // declaring variables
    int length = input.length();
    int start = 0;
    int end = length-1;
    
    // index until it finds an alphabetical or numerical char from the 
    // beginning of the string
    while ((start < length) and (not std::isalnum(input[start]))) {
        start++;
    }

    // index until it finds an alphabetical or numerical char from the end of 
    // the string
    while ((end >= 0) and (not std::isalnum(input[end]))) {
        end--;
    }

    // returns a substring of the inputted word starting at the indexes
    return input.substr(start, end-start+1);
}

