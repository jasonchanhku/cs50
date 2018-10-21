#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main (void){

    int *x;
    int *y;
    //must have malloc when initialize pointer
    x = malloc(sizeof(int));

    *x = 45;
    ///always remember to derefernce it
    printf("x is %i\n", *x);

    y = x;
    *y = 15;
    printf("x is %i and y is %i\n", *x, *y);
}