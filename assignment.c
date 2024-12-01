#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;


// this part of the code checks if the number of arguments passed to the program is correct.
// my initial thought was to set "!= 2", however, after some research,
// i put 3 instead of 2, because apparently the program name is also an argument. so, if the given argc is anything except 3, 
// it's automatically incorrect.
// therefore, at the end comes argc (which is 3 with program itself) -1.

    if (argc != 3) { 
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1;
    }

//"Instead of n, the program will output the actual number of arguments passed to the program."

    printf("You provided %d arguments\n", argc - 1);


//"The program will then check if all arguments passed are integers greater than 0. 
//If this is not the case, the program will output the following text to the standard output:" 

    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]); // convert the argument to an integer with "atoi"
        if (num <= 0) {
            printf("Incorrect usage. The parameters you provided are not positive integers\n");
            return 1; // if the number is not positive, the program will return 1 and exit.
        
        }
    }



//"The program will then create a dynamically allocated matrix of integers using the dimensions passed as parameters. 
//For instance, if the program is called with ``assignment 5 10``, a matrix of 5 rows and 10 columns will be created. 
//Each entry of this matrix will be initialized to a random integer between 1 and 100."

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    int **matrix = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (maxrand - minrand + 1) + minrand;
        }
    }


//"The program will create a file called ``matrix.txt`` that contains the previously generated matrix with one row on each line, 
//and using a whitespace separator between each entry. No whitespace should be appended at the end of each line. 
//The last row should end with a carriage return."

    FILE *file = fopen("matrix.txt", "w");
    if (file == NULL) {                         // check if the file was created successfully, just an additional error handling
        printf("File could not be created\n");
        return 1;
    }


// writing the matrix to the txt file

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < cols - 1) { // add a whitespace separator between each entry, except for the last one
                fprintf(file, " ");
            }
        }
        
        fprintf(file, "\n"); // add a newline character at the end of each row

    }   

    fclose(file);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]); // free the memory allocated for each row
    }

    free(matrix); // free the memory allocated for the matrix

    return 0;

}