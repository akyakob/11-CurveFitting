/*---------------------------------------------------------------------------
  This program demonstrates a simple Ax=b QR solver
  student copy 
  gcc -g  -std=c99 lab_a.c -lgsl -lgslcblas -o lab_a
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

/* GSL */
#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

#define NR (3) //NUMBER ROWS
#define NC (3) //NUMBER COLUMNS 

int main(int argc, char *argv[]) {

   int row = 0; 
   int col = 0;

   gsl_matrix *A;          // The A matrix
  // gsl_matrix *AT;          // The A matrix
  // gsl_matrix *ATA;          // The A matrix
   gsl_vector *b;          // b vector
  // gsl_vector *ATB;          // b vector
   gsl_vector *x;          // The answer
   gsl_vector *tau;        // Householder coefficients 
   gsl_vector *res;        // vector of residuals       

   // Allocate space for all the data 
   A   = gsl_matrix_alloc(NR,NC);    
  // AT  = gsl_matrix_alloc(NR,NC);    
  // ATA = gsl_matrix_alloc(NR,NC);    
   b   = gsl_vector_alloc(NC);        
  // ATB = gsl_vector_alloc(NC);        
   x   = gsl_vector_alloc(NC);        
   tau = gsl_vector_alloc(NC);     // required place holder for GSL 
   res = gsl_vector_alloc(NC);     // Contains the residual 

   
   // Encode the following polynomial in GSL
   //2x1 + 8x2 + 6x3 = 20
   //4x1 + 2x2 - 2x3 = -2
   //3x1 -  x2 +  x3 = 11
   // encode the A matrix
     gsl_matrix_set(A,0,0,2);
     gsl_matrix_set(A,0,1,8);
     gsl_matrix_set(A,0,2,6);
     gsl_matrix_set(A,1,0,4);
     gsl_matrix_set(A,1,1,2);
     gsl_matrix_set(A,1,2,-2);
     gsl_matrix_set(A,2,0,3);
     gsl_matrix_set(A,2,1,-1);
     gsl_matrix_set(A,2,2,1);
   
   // Encode the b vector
     gsl_vector_set(b,0,20); 
     gsl_vector_set(b,1,-2); 
     gsl_vector_set(b,2,11); 
   
   /* Print matrix A and vector  b */
   printf("Matrix A (%d x %d)\n", NR, NC);
   for(int i = 0; i < NR; i++) {
      printf("%3d: ", i);
      for(int j = 0; j < NC; j++) {
         printf("%12.5f ", gsl_matrix_get(A, i, j));
      }
      printf("\n");
   }
   printf("Vector b (%d x 1)\n", NR);
   for(int i = 0; i < NR; i++) {
      printf("%12.5f \n", gsl_vector_get(b, i));
   }

   //  Use GSL QR decomposition to do the Ax=b math
       // gsl_matrix_transpose_memcpy(AT,A);
       // gsl_blas_dgemv(CblasNoTrans,1.0,AT,b,0.0,ATB);
       // gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,1.0,AT,A,0.0,ATA);
        gsl_linalg_QR_decomp(A,tau);
        gsl_linalg_QR_lssolve(A,tau,b,x,res);  

   printf("\nSolution vector x (%d x 1)\n", NR);
   for(int i = 0; i < NR; i++) {
      printf("%12.5f \n", gsl_vector_get(x, i));
   }
   printf("\n");
   
   /* Free memory - VERY IMPORTANT! */
      gsl_matrix_free(A);
      A=NULL;
      gsl_vector_free(b);
      b=NULL;
      gsl_vector_free(x);
      x=NULL;
      gsl_vector_free(tau);
      tau=NULL;
      gsl_vector_free(res);
      res=NULL; 
   
   }
