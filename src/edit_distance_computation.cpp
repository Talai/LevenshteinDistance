/* 
 * File:                        EditDistance.hpp
 * Author:                      Aline Castendiek
 * Student ID:                  768297
 * Date:                        13/04/14
 * 1st operating system:        Linux [Ubuntu 3.11.0-19-generic]
 * 2nd operating system:        Windows 7 [Version 6.1.7601]
 * 1st Compiler:                g++ [4.8.1]
 * 2nd Compiler:                clang++ [3.2]
 * Doxygen version:             1.8.4 [Linux] + 1.8.6 [Windows]
 */
 
#include <iostream>                     // for std::cout
#include <cstdlib>                      // for exit()
#include "../include/EditDistance.hpp"  // EditDistance class

int main(int argc, char* argv[]) 
{
    /// Object of class EditDistance
    EditDistance ed;    
   
    // tests whether argc has exactly three arguments
    // otherwise prints error message with explanation
    if (argc != 3)
    {
        std::cerr << "USAGE: compute_ed FILE_1 FILE_2\n";
        std::cerr <<         "FILE_1, FILE_2 = text files containing ";
        std::cerr <<         "a single word per line.\n";
        exit(1);
    }
    
    /*
       Calls read in function which reads in two files, computes matrices and 
       edit distances between source words and target words and then prints
       them as well as the edit distance between them
     */ 
    ed.read_in(argv[1],argv[2]); 
    
    return 0;
}

        
