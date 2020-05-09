/*---------------------------------------------------------------------------
  Code to test integration with Darrays and GSL
  
  student copy
  
  gcc -g lab_b.c   DynamicArrays.c  -DHW8 -std=c99 -lgsl -lgslcblas -o lab_b
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicArrays.h"

/* GSL */
#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

void readPoints(FILE *file, DArray *DArrayPtr);
void prepareDataForLS(int nr, int nc, const DArray *points);


int main(int argc, char *argv[]) {
   // Create a Darray with space for 10 objects (more than we need)
   DArray points;
   CreateDArray(&points, 10); //Create a dynamic array to hold the data points
   
   // The number of rows read in and the GSL polynomial power
   int nr;
   int nc;
   
   // Open file and read the data file
   char* inName = "testdata.txt"; 
   FILE* pointsFile = fopen (inName, "r");
   if (NULL == pointsFile) {
      fprintf (stderr, "Error: unable to open data points file '%s'\n", inName);
      fflush (stderr);
      DestroyDArray(&points);
      return(1);
   }
   
   /* Read the data in */
   printf("Reading data from %s...\n", inName); 
   readPoints (pointsFile, &points);
   fclose(pointsFile);

   /* print Darray */ 
   printf("The raw data in the Darray\n");
   for (int i=0;i<points.EntriesUsed;i++){
      printf("[%f,%f]\n",(points.Payload[i]).x, (points.Payload[i]).y);
   }
   
   // Number of rows read in
   nr = points.EntriesUsed;  
   
   // The number of columns defines the power. 1st order
   nc = 2;
   printf("\nDefining a first order solution matrix\n");
   prepareDataForLS(nr, nc, &points); //linear

   // The number of columns defines the power, 2nd order
   nc = 3;
   printf("\nDefining a second order solution matrix\n");
   prepareDataForLS(nr, nc, &points); //quadratic
   
   // The number of columns defines the power, 4nd order
   nc = 5;
   printf("\nDefining a fourth order solution matrix\n");
   prepareDataForLS(nr, nc, &points); //quadratic
   
   return 0;
}


/***************************************************************************************
 Reads the points data from file and returns it in a Darray
 
 Where: FILE *file     - open handle to read from
                         of the form:     22.0      6.7
                                          23.4      18.8
        DArray *DArrayPtr - Pointer to a dynamic array to store the data
  Returns: nothing
  Errors:  none
*****************************************************************************************/
void readPoints(FILE *file, DArray *DArrayPtr) {
  char String[256], *pch;
  Data tempData;

  /* Grab the data and put it in a Dynamic Array */
  while (fgets (String, 256, file))     {
      pch = strtok (String, "    ");
      tempData.x = atof(pch);
      pch = strtok (NULL, "  ");
      tempData.y = atof(pch);
      PushToDArray (DArrayPtr, &tempData);
    }     
    
  return;
} /* readPoints */


/***************************************************************************************
 This function takes data pairs (x,y) from a Darray and creates an A matrix and b vector
 corresponding to a least squares approximation.
 
 Where: int nr         - Number of rows in the Darray
        int nc         - The desired number of columns in the A matrix and hence the 
                         power of the resulting polynomial when the AtAx = Atb solution 
        DArray *points - Pointer to a dynamic array containing x,y data pairs
  Returns: nothing
  Errors:  none
*****************************************************************************************/
void prepareDataForLS(int nr, int nc, const DArray *points) {
   // Declare matrix A and vector b and allocate space
   gsl_matrix *A    = gsl_matrix_alloc(nr, nc);   
   gsl_vector *b    = gsl_vector_alloc(nr);        

   /* Make the first column of data 1's */
   for(int i = 0; i < nr; i++) {
      gsl_matrix_set(A,i,0,1);   // **update**
   }

   /* Initialize Matrix A with the data in "points"  */  
   for(int i = 0; i < nr; i++) {
      double x = points->Payload[i].x;
      
      /* Generate the powers across the columns */
      for(int j = 1; j < nc; j++) {
         gsl_matrix_set(A,i,j,x);   // **update**
         x *= points->Payload[i].x;
      }
   } /* End for i */
   
   
    /* Initialize vector b with y data */
   for(int i = 0; i < nr; i++) {
      gsl_vector_set(b,i, points->Payload[i].y);     // **update**
   }
   

   /* Print matrix A and vector  b */
   printf("Matrix A (%d x %d)\n", nr,nc);
   for(int i = 0; i < nr; i++) {
      printf("%3d: ", i);
      for(int j = 0; j < nc; j++) {
         printf("%12.5f ", gsl_matrix_get(A, i, j));
      }
      printf("\n");
   }
   
   printf("Vector b (%d x 1)\n", nr);
   for(int i = 0; i < nr; i++) {
      printf("%12.5f \n", gsl_vector_get(b, i));
   }
   printf("\n ******* --- *******\n\n");
   
   /* Free memory - VERY IMPORTANT! */
   gsl_matrix_free(A);
   gsl_vector_free(b);
}
