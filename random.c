/* Program : Random.c
Author: Emmanuel Anokwuru
Date : 6.1.2020
*/
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define DEBUG 1
#include <stdio.h>
#include <math.h>
#include <stdlib.h> /* for rand() */
#include <time.h>   /* for time() in srand() */


int histogram_array[6] = { 0 }; // g;lobal array; array for storing the histogram experiment.
double gauss(double x) {
    double exp_side;
    double fraction_side;
    double mean = 0;
    double std_dev = 1;
    double gaussian;
    exp_side = exp(-0.5 * ((x - mean) / std_dev) * ((x - mean) / std_dev)); // the exponential part of the formular
    fraction_side = 1 / (std_dev * sqrt(2 * M_PI)); // the fraction part of the formular
    gaussian = fraction_side * exp_side;
    return gaussian;
}
int dice() {
    int min = 1;
    int max = 6;
    return rand() % (max) + min;
}
void dice_statistics(int throws, int experiments) {
    int dice_value; // storing the value of each dice throw.
    int sum_of_values;
    //int ocurrance[6];
    int average;
    double overall_average;
    int overall_sum = 0;


    for (int y = 0; y < experiments; y++){ // iterating through the number of experiments
        sum_of_values = 0;
        average = 0;
        
        for (int i = 0; i < throws; i++){ // getting the sum of results for each throw
            dice_value = dice();
            sum_of_values += dice_value;
           if(DEBUG) printf("the value is %d\n", dice_value);
        }
        overall_sum += sum_of_values;
        average = sum_of_values / throws;
        printf("experiment %d sum :%d average is %d\n", y + 1, sum_of_values, average);
        histogram_array[sum_of_values]++;
    }
    overall_average = overall_sum/experiments;
    for (int i = 1; i < 6; i++){
        printf("The occurance of %d is %d\n",i, histogram_array[i]);
    }

}
int main() {
    srand(time(0));
    printf(" gauss: %lf\n", gauss(1));
    dice_statistics(2, 100);
}
