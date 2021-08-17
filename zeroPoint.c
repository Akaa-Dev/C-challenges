/*
* Program: zero_point.c
* Author : Emmanuel Anokwuru
* Date :   18-12-2020
*/

#define NO_CRT_SECURE_WARNINGS
#define DEBUG 0
#define H 1e-8
#include <stdio.h>
#include<math.h>

double f(double x) {// implenting f(x)
	return cos(x);
}
double zero_point(double lower, double upper) { // finding the zero point of f(x) by bisection method
	double midpoint=0.0;
	int iteration = 1;
	//double ab_diff = ((lower - upper) * (lower - upper));// the absolute difference between lower and upper since |x-y|^2 = (x-y)^2
	if(DEBUG)printf("Iteration\t Lower \t Upper \t Middle \t f(lower)\t f(upper)\t f(middle)\t\n");
	while ((lower - upper) * (lower - upper) > 1e-8) { // loop continues until absolute difference becomes less than 10^-8
		midpoint = (lower + upper) / 2.0;
		if (f(midpoint) > 0) {
			
			if (DEBUG)printf("%d \t %lf \t %lf\t %lf \t %lf\t %lf\t %lf\n",iteration,lower,upper, midpoint,f(lower),f(upper),f(midpoint));
			//printf("f_upper is %lf \n", f(upper));
			lower = midpoint;
		}
		else if (f(midpoint) < 0) {
			
			if(DEBUG) printf("%d \t %lf \t %lf\t %lf \t %lf\t %lf\t %lf\n", iteration, lower, upper, midpoint, f(lower), f(upper), f(midpoint));
			//printf("f_lower is %lf \n ", f(lower));	
			upper = midpoint;
		}
	    iteration++;
	}	
	return midpoint;
	}

 double derivation(double x, double h){
	double first_derivation = (f(x + h) - f(x - h)) / (2 * h); // first derviaion of the f function.
	return first_derivation;
 }
 double extreme_value(double lower, double upper) {
	 double midpoint_value=0.0;
	 double xtreme_value=0.0;
	 while ((lower - upper) * (lower - upper) > 1e-8) {
		 midpoint_value = (lower + upper) / 2;
		 if (derivation(midpoint_value, H) > 0) {
			 lower = midpoint_value;
		 }
		 else{
			 upper = midpoint_value;
		 }
		 xtreme_value = midpoint_value;
		 
		 if (DEBUG)printf("This is the xtreme value %lf\n", xtreme_value);
	 }
	 return xtreme_value;
 }


 int main() {
	 //Exercise 2a
	 printf("Zero point of cosine:  %lf\n", zero_point(0.0, 2.0));

	 //Exercise 2b
	 printf("The first derivative of cosine 75 is %lf\n", derivation(75.0, H));
	 printf("The extreme value of cosine: %lf\n", extreme_value(0.0, 2.0));
	 return 0;
 }
