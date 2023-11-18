/*
 *  stringProcessing.h
 *  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
 *  4/12/2023
 *
 *  CS 15 PROJECT 4 gerp
 *
 *  FILE PURPOSE:
 *  Interface for stringProcessing function. Holds the function that will
 *  strip a string (that is inputted) to only alphabetical-numerical characters 
 *  only. It returns the string without the non alphabetical-numerical 
 *  characters in it. Will be used for the final gerp project.
 * 
 */


#ifndef __STRINGPROCESSING_H__
#define __STRINGPROCESSING_H__

#include <iostream>

std::string stripNonAlphaNum(std::string input);

#endif