#include <stdio.h>

int main (void){

    int x;
    printf("x: ");

    //But we never set s to anything, so it’s an address with some random value, which means we are trying to store a string at
    //some random place in memory which might have other important things in it!

    scanf("%i", &x);
    printf("x is %i", x);

    //x is an int we initialized in our program, and & gets us the address of a variable.
    //So we are passing in the address of x to scanf, so it can store the value a user types, into x



}