/******************************************************************************
 * @file: latin_square_functions.c
 *
 * WISC NETID hyuan73
 * CANVAS USERNAME Yuan Haoyang
 * WISC ID NUMBER 9082704376
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Yuan Haoyang (hyuan73@wisc.edu)
 * @modified: //TODO
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/
extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in, 
                            size_t *n) {
    /* BEGIN MODIFYING CODE HERE */
    //read file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Open file failed\n");
    }
    char *next_text = (char *) malloc(1002 * sizeof(char));
    if(fgets(next_text, 1002, fp) != NULL){
	*n = strlen(next_text) - 1;
    }
    //create a new readfile
    //initialize
    *latin_square_in =(char **) malloc(1002 * sizeof(char *));
    for(int i = 0; i < *n; i++){
        *(*latin_square_in + i) = (char *) malloc(1002 * sizeof(char));
    }
    for(int j = 0; j < *n; j++){
	*(*(*latin_square_in) + j) = *(next_text + j);
    }
    //valuei
    for(int i = 1; i < *n; i++){
	//already read one row
        char *temp = malloc(1002 * sizeof(char *));
        fgets(temp, 1002, fp);
        for(int j = 0; j < *n; j++){
            *(*(*latin_square_in + i) + j) = *(temp + j);
        }
	free(temp);
    }
    free(next_text);
    fclose(fp);
    /* END MODIFYING CODE HERE */
}

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
    for(int i = 0; i < n; i++){
       for(int h = 0; h < n; h++){
            char temp = *(*(latin_square + i) + h);
            int tempCount = 0;
            //check this how many times this element appeared
            for(int j = 0; j < n; j++){
                for(int k = 0; k < n; k++){
                    if(*(*(latin_square + j) + k) == temp){
                        tempCount++;
                    }
                }
            }
            if(tempCount != n){
                return 0;
            }
       }
    }
    /* END MODIFYING CODE HERE */
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    int output = 1;
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
    /* BEGIN MODIFYING CODE HERE */
    for(int i = 0; i < n; i++){
       for(int h = 0; h < n; h++){
            char temp = *(*(latin_square + i) + h);
	    int rowError = 0;
	    //check rows
            for(int j = h + 1; j < n; j++){
                    if(*(*(latin_square + i) + j) == temp){
                        printf("Error in row %d\n", i);
                        rowError = 1;
			output = 0;
			break;
                    }
            }
	    if(rowError == 1){
		break;
	    }
       }
    }
	 //check columns
	for(int i = 0; i < n; i++){
	    for(int j = 0; j < n; j++){
		int colError = 0;
	    	char temp = *(*(latin_square + j) + i);
		for(int k = j + 1; k < n; k++){
                	if(*(*(latin_square + k) + i) == temp){
                	    printf("Error in column %d\n", i);
			    colError = 1;
			    output = 0;	
			    break;
                	}
            	}
		if(colError == 1){
			break;
		}
	    }
       }

    /* END MODIFYING CODE HERE */
    return output;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
    /* BEGIN MODIFYING CODE HERE */
    for(int i = 0; i < n; i++){
        free(*(latin_square + i));
    }
    free(latin_square);
    /* END MODIFYING CODE HERE */
}


