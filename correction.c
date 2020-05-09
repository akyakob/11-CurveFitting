/******************************************************************
 * Program to correct the data for the sensor
 * Note: Each student gets unique data, so this exact equation will
 * differ for each students solution
 * Be sure to use Honer's factorization  
 * ***************************************************************/

#include <stdio.h>
#include <stdlib.h>


/* Polynomial */
static double poly[7][8] = 
{//x^0 x^1 x^2 xi^3 x^4 x^5 x^6 x^7
  {135.293, 0.057803,0,0,0,0,0,0}, /* ord 1 */
  {-48.9559, 0.293484, -5.31075e-05,0,0,0,0,0}, /* ord 2 */
  {18.593, 0.128131, 3.88032e-05, -1.39931e-08,0,0,0,0}, // ord 3 
  {19.2659,0.164136,-1.28369e-05,7.38272e-09,-2.69443e-12,0,0,0}, // ord 4
  {-46.4788,0.327508,-0.000120999,2.54017e-08,4.39819e-13,-7.95045e-16,0,0}, // ord 5
  {-112.76,0.440934,-0.00017106,2.90992e-08,-1.31379e-13,2.30907e-16,-1.77553e-19,0}, // ord 6
  {120.54,-0.174221,0.000308641,-7.64567e-08,-1.90118e-11,7.33056e-15,3.25179e-19,-1.94387e-22} // ord 7
};

double evalPoly(int x){
	 /*solution to poly, Horner's method*/
	 return poly[ORD][0] + x *
		(poly[ORD][1] + x *
		(poly[ORD][2] + x *
		(poly[ORD][3] + x *
		(poly[ORD][4] + x *
		(poly[ORD][5] + x *
		(poly[ORD][6] + x *
		(poly[ORD][7])))))));
}

/* Runs the data through the fitting line */

int main(int argc, char *argv[])
{
    int res, real, ideal;
    
    while(scanf("%d %d", &ideal, &real) != EOF)
    {
     /* Insert your polynomial here, be sure to round properly */
	double temp = evalPoly(real);
 	/* round */
	if (temp >= 0.0) {
          (temp+=0.5);
        }
	else{
	  (temp-=0.5);
	}
	res = real - (int)temp;
        printf("%d %d\n", ideal, res);
    } /*end while*/
    return 0;
}
