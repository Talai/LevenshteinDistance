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

#include <iostream>             // for std::cout  
#include <fstream>              // for std::ifstream
#include <new>                  // for std::nothrow
#include <cassert>              // for asserts
#include <cstdlib>              // for abort()
#include <string>               // for string class

#define NDEBUG


/** 
  @brief  The edit distance class represents the minimum number of editing 
          operations (insertion, deletion, substitution) beetween two strings 
          needed to transform one string into another.
*/    

class EditDistance                  
{
  public:
      /// Default constructor
      EditDistance()                                    
      {
          // calls init function to initalize object
          init();
      }
      
      
    /** @brief Reads in two files containing the strings to be compared,
               computes the edit distances beetween the strings contained in 
               the file and then prints the first string, the second string 
     *         and the edit distance between them.  
        @param filename1 Pointer to first file
        @param filename2 Pointer to second file
    */
    void read_in(const char* filename1, const char* filename2)
    {
        if (filename1 != 0 && filename2 != 0) {
            // string from first file 
            std::string word1;
            // string from second file
            std::string word2;
            // ifstream object reading strings from first file 
            std::ifstream in1(filename1);
            // ifstream object reading strings from second file 
            std::ifstream in2(filename2);

            // test whether it is possible to open both files
            if (in1.is_open()) {
                if (in2.is_open()) {

                    // as long as there are still lines in both files
                    while (in1.good() && in2.good()) {
                        // read both strings from both files and store them in 
                        // corresponding variables word1 and word2
                        std::getline(in1, word1);
                        std::getline(in2, word2);

                        // if both strings are empty, do not compute or print 
                        // anything at all 
                        if (!word1.empty() && !word2.empty()) {
                            // print first string, second string and the 
                            // edit distance between them

                            std::cout << word1 << "\t" << word2 << "\t\t\t";
                            std::cout << compute_ed(&word1, &word2) << "\n";

                        }
                    }
                }
                    // if it is not possible to open one of the files, print error 
                    // message for each file seperately 
                else {
                    std::cerr << "Unable to open '" << filename2 << "'\n";
                }
            } else {
                std::cerr << "Unable to open '" << filename1 << "'\n";
            }
        } 
        else 
        {
            std::cerr << "Memory error: Pointer to null. Could not read in files.\n";
        }
    }
   
    

private: 

//functions:  
    
    /** @brief Initalizes wordlenght variables m and n.   
        @note At the moment we create an object of the class EditDistance and 
              therefore the constructor of this class is called, the only 
              existing global variables are m and n, which is why we only 
              initialize those two inside the init function.        
     */         
    void init()                             
    {
        n = 0;
        m = 0;        
    } 
   
        
    /** 
        @brief Function for computing edit distance between two strings
        @param s Pointer to first string 
        @param t Pointer to second string
        @return Edit distance between the two strings
    */                      
    
    int compute_ed(std::string* s, std::string* t)
    {
        if (s != 0 && t != 0)
        {
            // represents current matrix cell in row
            unsigned i;
            // represents current matrix cell in column
            unsigned j;
            
            m = s->length();  
            n = t->length();

            // if one string is empty then return lenght of the other string
            if (m == 0) return n;
            if (n == 0) return m;

            // represents a dynamic matrix for the two strings to be compared
            unsigned** d = new_matrix(); 

            // testing whether wordlength functions properly
            assert(m >= 0);
            assert(n >= 0); 

            assert(d != 0);

            // below in every matrix cell is written a value consecutively
            // until we reach the last cell of a matrix row, we fill it with a 
            // value in ascending order
            for (i = 1; i <= m; ++i)
            {
                d[i][0] = i;
            }

            // same procedure for matrix columns
            for (j = 1; j <= n; ++j)
            {
                d[0][j] = j;    
            }

            // now the actual computing is done:
            // via two nested loops each letter of each word is compared
            for (j = 1; j <= n; ++j)
            {
                for (i = 1; i <= m; ++i)
                {
                    // if the letter is the same we do not compute a cost 
                    // instead we add a zero to the current cost
                    // keep in mind that string starts at [0] and matrix at [1]
                    // (that is why we write i-1 and j-1)
                    // string member function "at" returns char at a given index 
                    if (s->at(i-1) == t->at(j-1))
                    {
                        d[i][j] = d[i-1][j-1];
                    }
                    else
                    {
                        // if it's not the same letter we use the minimum 
                        // function determine the minimal cost
                        d[i][j] = 
                                /* we use the minimum function twice to cover 
                                   all three operations because it can only have
                                   two arguments at a time
                                   (of course it would also be able to write a 
                                   minimum function with three arguments)
                                */
                                minimum 
                                (
                                   d[i-1][j] + 1,               // deletion
                                   minimum            
                                   (
                                      d[i][j-1] + 1,            // insertion
                                      d[i-1][j-1] + 1           // substitution
                                   )  
                                );
                    }
                }
            }    
            // the computed distance beetween the two strings
            unsigned result = d[m][n];      
            /**  @note We need to save the result in a seperate variable 
                       because we are going to delete the matrix first and
                       then we return the actual value at the end of the 
                       function.
            */ 

            clear_matrix(d);

            return result;                         
        }

        // if of the string pointers points to zero
        else 
        {
            std::cerr << "Memory error: Pointer to null.\n";
            return -1;
        }
    }
      
        
    /** 
       @brief Creates a matrix the size of the two strings to be compared by 
              allocating dynamic memory from heap
       @return A pointer to the newly created matrix, or more precisely, 
               a pointer to an array containing an array of pointers  
     */           
   unsigned** new_matrix()              
    {
  
       assert(m > 0);
       assert(n > 0);
       
       /* pointer storing the adress of the new matrix
          allocates memory for elements of rows 
          std::nothrow indicates not to throw an exception on failure,
          but to return a null pointer instead
       */
       unsigned** pointer_to_d = new (std::nothrow) unsigned* [m+1];
       /**   @note Array size needs to be [m+1] and [n+1] because matrix cell 
                   [0][0] represents the empty string and is therefore only 
                   used for edit distance calculation, but not included in the 
                   wordlenght. 
       */    
       // if the pointer points to null (as specified above), print error 
       // message and abort program
       if (pointer_to_d == 0) 
       {
           std::cerr << "No more heap space left. Aborting.\n";
           abort();
       }
       
       // allocates memory for elements of columns
       for (unsigned i = 0; i < m+1; ++i)
       {
           // same procedure as above
           pointer_to_d[i] = new (std::nothrow) unsigned[n+1];
           
           if (pointer_to_d[i] == 0) 
           {
               std::cerr << "No more heap space left. Aborting.\n";
               abort();
           } 
           // writes zero in every cell (just in case)
           for (unsigned j = 0; j < n+1; ++j)
           {
               pointer_to_d[i][j] = 0;
           }
       }
       return pointer_to_d;
    }
    
   
     /** @brief Deletes dynamically allocated matrix    
         @param to_delete Pointer to the matrix that will be deleted 
                (pointer to an array with an array of pointers)
      */
    void clear_matrix(unsigned** to_delete)                        
    {
        if (to_delete != 0) {
            for (unsigned i = 0; i < m + 1; ++i) {
                if (to_delete[i] != 0) {
                    // delete columns first
                    delete [] to_delete[i];
                }
            }
            // now delete rows as well
            delete [] to_delete;
            // set pointer to zero (just in case) 
            to_delete = 0;
        }
    }     


     /** @brief Compares two values and returns smaller value   
         @param a Value 1 to be compared 
         @param b Value 2 to be compared   
         @return Smaller value of both values 
      */
    unsigned minimum (unsigned a, unsigned b)    
    {
        if (a <= b) return a;
        else return b;
    }
  
    
     /* 
      unsigned wordlength(char* s)     
      {
        unsigned i = 0;
        // necessary typecast from pointer to int because a pointer cannot be 
        // 'not equal to zero'
        while(((int) *s) != 0)
        {
           ++i;
           ++s;
        }
        return i;
      }
     */
   
   //variables:    

   /// Length of source word
   unsigned m;                              
   /// Length of target word
   unsigned n;                               
        
};      // EditDistance
