
* Program Name: integrals.c
* Name of Author: Emmanuel Anokwuru
* Date: 06.01.2021
*/


#define _CRT_NO_SECURE_WARNINGS
#define _USE_MATH_DEFINES
#define DEBUG 0
#include <stdio.h>
#include <math.h>



double f(double x) {
	//return cos(M_PI * x);
	return cos(M_PI*x);
}

double area (double left_x, double right_x){
	double b = right_x - left_x; // the width of the rectangle
	if (DEBUG) printf(" width = %lf\n", b);
	double x = (right_x + left_x) / 2; // the middle point between the two points, in other words, 
	if (DEBUG) printf(" height = %lf\n", x);
	if (DEBUG) printf("The function of x = %lf\n", f(x)); //the height of the rectangle id the function of the middle point
	double area_of_rectangle=(b * f(x));
	if (DEBUG) printf("the area of this rectangle is %lf\n", b * f(x));
	return(area_of_rectangle);
}

double integral(double left_x, double right_x, int steps) {
	double new_interval=0.0;
	double sum_of_area=0.0;
	double change_in_width = (right_x - left_x) / steps;
	while (new_interval <= right_x) {
		new_interval = change_in_width + left_x;
		if (DEBUG) printf("The new values are %lf, %lf\n", left_x, new_interval);
		sum_of_area += area(left_x,new_interval); 
		if (DEBUG) printf("The sum of area is %lf\n", sum_of_area);
		left_x =new_interval; 
		if (DEBUG) printf("The new values are %lf, %lf\n", left_x, new_interval);
	}
	return sum_of_area;	
}

int main() {
	
	double area_of_first_rectangle= area(-0.5, 0.5); // testing for area of the first rectangle
	printf("The area of the first rectangle is %llf\n", area_of_first_rectangle);
	

	
	double integral_value = integral(-0.5, 0.5, 1000);
	printf("The sum of area is %lf\n", integral_value);
	return 0;
}


	
