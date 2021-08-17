/*
* program name: complex calculator
* WS2020
* Emmanuel Anokwuru
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES /* for M_PI */
#include <math.h>
#include <stdlib.h> /* for rand() */
#include <time.h> /* for time() in srand() */
#define STACK_VOLUME 10
#define DEBUG 1
#define LINE_MAX 10;


typedef struct struct_complex {
    double real;
    double imag;
} complex;
const complex I = { 0.0, 1.0 }; // imaginary unit
const complex ONE = { 1.0, 0.0 }; // real unit

void print_complex(complex c) {
    printf("%.3lf+%.3lf", c.real, c.imag);
}

complex add_complex_numbers(complex c1, complex c2) {
    complex result;
    result.real = c1.real + c2.real;
    result.imag = c1.imag + c2.imag;
    return result;
}
complex sub_complex_numbers(complex c1, complex c2) {
    complex result;
    result.real = c1.real - c2.real;
    result.imag = c1.imag - c2.imag;
    return result;
}
complex mul_complex_numbers(complex c1, complex c2) {
    complex result;
    result.real = c1.real * c2.real - c1.imag * c2.imag;
    result.imag = c1.real * c2.imag + c1.imag * c2.real;
    return result;
}
complex div_complex_numbers(complex c1, complex c2) {
    complex result = { 0,0 };
    //result.real = c1.real + c2.real;
    //result.imag = c1.imag + c2.imag;
    double denominator = c2.real * c2.real + c2.imag * c2.imag;
    result.real = (c1.real * c2.real + c1.imag * c2.imag) / denominator;
    result.imag = (c2.real * c1.imag - c2.imag * c1.real) / denominator;
    return result;
    return result;
}
complex complex_power(complex c, int num) { // takes in a complex and a number and then raises the complex to that number.
                                            // was only implemented in the complex_op function, not in complex_rp.
    complex product, result;
    result.real = c.real;
    result.imag = c.imag;
    for (int i = 1; i < num; i++) {
        product= result;
        result = mul_complex_numbers(product, c);
    }
    return result;
}

complex test_complex_power() { // testing for complex_power
    complex c1 = { 3, 4 };
    complex result =complex_power(c1, 2);
    complex result1 = complex_power(c1, 3);
    print_complex(result);
    printf("\n");
    print_complex(result1);
    return result1;
}


double complex_absolute(complex c) {
    return sqrt(c.real * c.real + c.imag * c.imag);
}
double complex_argument(complex c) {
    return atan2(c.imag/*Y*/, c.real/*X*/);
}
double complex_argument_degrees(complex c) {
    return atan2(c.imag/*Y*/, c.real/*X*/) / M_PI * 180;
}
complex complex_op(complex c1, complex c2,char operator) { //complex calculations,excluding complex power calculation.
    complex complex_result = {0,0};
    switch (operator) {  // different cases for operation
    case '+':complex_result = add_complex_numbers(c1, c2,operator);
        //print_complex(complex_result);
        break;
    case '-':complex_result = sub_complex_numbers(c1, c2, operator);
        //print_complex(complex_result);
        break;
    case '*':complex_result = mul_complex_numbers(c1, c2, operator);
        //print_complex(complex_result);
        break;
    case '/':complex_result = div_complex_numbers(c1, c2, operator);
        //print_complex(complex_result);
        break;
    //case '^':complex_result = complex_power(c1, power_value);
       // break;
    }

print_complex(complex_result);
return complex_result;
}

complex complexcalc(int argc, char **argv) {// does complex calculation, including power calculation
    complex c1 = { 0,0 }, c2 = { 0,0 }, complex_result = { 0,0 };
    int power_value=1;
    char operator=' ';
    FILE* fp;
    for (int i = 0; i < argc; i++) {
        sscanf(argv[1], "(%lf,%lf)", &c1.real, &c1.imag); //taking in input  for the first complex number
        operator=argv[2][0];
        if (operator== '^') { // checking if the operator is caret, if so, store second number as interger, not complex number.
            sscanf(argv[3], ("%d"), &power_value);
        }
        else {
            sscanf(argv[3], "(%lf,%lf)", &c2.real, &c2.imag);
        }
        printf("argv[%d] is : %s\n", i, argv[i]);
        if (operator!='^') {
            complex_result = complex_op(c1, c2, operator);
        }
        complex_result = complex_power(c1, power_value);
        if (operator!='+' && operator!='-' && operator!='*' && operator!='/' && operator!='^') { // error for operator input
            fprintf(stderr, "ERROR: Wrong operator\n");
            perror("Reason");
        }
    } if ((fp = fopen("computational_order.txt", "w")) != NULL) {//opens file for writing if open success
        printf("File is ready for writing!\n");
        fprintf(fp, "(%.1lf, %.1lf) %c (%1.lf, %.1lf)=(%.1lf, %.1lf)", c1.real, c1.imag, operator,c2.real, c2.imag, complex_result);//writing the calculation into the file
        fclose(fp);
        printf("Done writing!\n");
    }
    else { // do this if file open fails
        fprintf(stderr, "ERROR: cannot open file \"%s\"\n", fp);
        perror("Reason"); // OS tells us why it failed ... see "errno -l" on Linux
        exit(0);
    }
 
        print_complex(complex_result);
        return(complex_result);
    }

typedef struct { // struct for stacking complex numbers
    complex complx_num[STACK_VOLUME];
    int stack_index;
} complex_stack;
complex_stack stack_of_complex_numbers = { 0 };


complex complex_rpn(int argc, char **argv) {
    complex c, c1= { 0, 0 }, c2= { 0, 0 }, complex_result= { 0, 0 };
   // int power_value;
    char operator;
    //char buffer [10];
    int arg_counter = 0;
    FILE* fp;
    
    for (int i = 0; i < argc; i++) { // looping through the arguments of the command line.
        //if(sscanf(argv[1], "(%lf,%lf)"))
        int input_value = sscanf(argv[i], "(%lf,%lf)", &c.real, &c.imag);//taking in inputs complex numbers
        //printf("argv[%d] is : %s\n", i, argv[i]);
        if (input_value > 0) {
            stack_of_complex_numbers.complx_num[stack_of_complex_numbers.stack_index++] = c;
            if (++arg_counter == 1) {
                c1 = c;
            }
            else {
                c2 = c;
                //c1 = complex_result;
            }
        } 
        else {
                 operator=argv[i][0];
                 c2 = stack_of_complex_numbers.complx_num[--stack_of_complex_numbers.stack_index]; // 
                 c1 = stack_of_complex_numbers.complx_num[--stack_of_complex_numbers.stack_index];
                 complex_result = complex_op(c1, c2, operator);
                 stack_of_complex_numbers.complx_num[stack_of_complex_numbers.stack_index++] = complex_result;
                }
            printf("argv[%d] is : %s\n", i, argv[i]);
           // complex_result = complex_op(c1, c2, operator);
            //stack_of_complex_numbers.complx_num[stack_of_complex_numbers.stack_index--];
        }
    complex_result = stack_of_complex_numbers.complx_num[--stack_of_complex_numbers.stack_index];
    if ((fp = fopen("computational_order.txt", "w")) != NULL) {//opens file for writing if open success
        printf("File is ready for writing!\n");
        fprintf(fp, "(%.1lf, %.1lf) %c (%1.lf, %.1lf)=(%.1lf, %.1lf)",c1.real, c1.imag, operator,c2.real, c2.imag, complex_result);//writing the calculation into the file
        fclose(fp);
        printf("Done writing!\n");
    }
    else { // do this if file open fails
        fprintf(stderr, "ERROR: cannot open file \"%s\"\n", fp);
        perror("Reason"); // OS tells us why it failed ... see "errno -l" on Linux
        exit(0);
    }
    
    return complex_result;
    }
    
   

/*double test_rpn(){// tests rpn calculation
    printf("Time for calculations!!!\n");
    char complex_arg[7] = { (1,2),(1,2), '+'};
   // complex_arg[0] = (1,2);
   // complex_arg[1] = (2,1);
    //complex_arg[2] =  '*';
   // complex_arg[3] = (0,1);
   // complex_arg[4] = '+';
    printf("%.1lf,%.1lf\n", complex_arg[2]);
    complex result1 = complex_rpn(7, *complex_arg);
    /*complex result2 = complex_rpn(int argc, char** argv);
    complex result3 = complex_rpn(int argc, char** argv);
    complex result4 = complex_rpn(int argc, char** argv);
    complex result5 = complex_rpn(int argc, char** argv);
    complex result6 = complex_rpn(int argc, char** argv);
    complex result7 = complex_rpn(int argc, char** argv);
    complex result8 = complex_rpn(int argc, char** argv);
    complex result9 = complex_rpn(int argc, char** argv);
    complex result10 = complex_rpn(int argc, char** argv);*/
    //printf("%.1lf\n", result1);
    //printf("%.1lf\n", result2);
  //  return;
//}*/


    int main(int argc, char** argv) {
       /* printf("Type in R for RPN notation or N for normal calculation notation: ");
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], 'r') == 0) { complex complex_result1 = complex_rpn(argc, argv); };
        }*/
        //test_rpn();
     complex_rpn();
    //printf("%s",'^');
    //complex complex_result1 = complex_rpn(argc, argv);
    //complex complex_result2 = complexcalc(argc, argv);
    
    //test_complex_power();
    //print_complex(power);
    printf("\n");
    //system("PAUSE");
    return 0;
    }
   
     
    


