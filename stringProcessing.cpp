/*
 *  stringProcessing.cpp
 *  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
 *  4/12/2023
 *
 *  CS 15 PROJECT 4 gerp
 *
 *  FILE PURPOSE:
 *  Implementation of the stringProcessing.h function. The function takes an 
 *  inputted string and removes all preceeding and trailing non 
 *  alphabetical-numerical characters and returns a substring of the word. Will 
 *  be used for the final gerp project.
 * 
 */

#include "stringProcessing.h"
#include <cctype>

/*
 * name:      stripNonAlphaNum 
 * purpose:   takes an inputted string and removes all preceeding and trailing 
 *            non alphabetical-numerical characters
 * arguments: std::string input
 * returns:   a substring of the inputted word
 */
std::string stripNonAlphaNum(std::string input) {
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
