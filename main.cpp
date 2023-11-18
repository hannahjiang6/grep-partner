/*
 *  main.cpp
 *  Hannah Jiang (hjiang03) and Zachary White (zwhite03)
 *  4/12/2023
 *
 *  CS 15 PROJECT 4 gerp
 *
 *  FILE PURPOSE:
 *  Runs the search engine program known as "gerp". Through the provided
 *  inputs, the program will do 1 of 2 things. Run the program or throw an 
 *  error if the inputs were not valid.
 *
 */

#include "gerp.h"

using namespace std;

/*
* main
* inputs : number of command line args, array of the args
* purpose : creates an instance of the gerp class, and calls 
*           its functions to index files and search
* outputs : returns 0 to indicate program success
*/
int main(int argc, char *argv[])
{
    // check for valid input
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile\n";
        exit(EXIT_FAILURE);
    }

    Gerp our_gerp;

    // strings the input and output file to send into the program
    string inputDirectory = argv[1];
    string outputFile = argv[2];

    our_gerp.readFiles(inputDirectory);
    our_gerp.queryLoop(outputFile);
    std::cout << "Goodbye! Thank you and have a nice day.\n";
    return 0;
}