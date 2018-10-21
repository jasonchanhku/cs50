#include <stdio.h>

void swap (int *a, int *b){
    int tmp;
    tmp = *b;
    *b = *a;
    *a = tmp;
}


int main (void){

    int x = 1;
    int y = 2;
    swap(&x, &y);

    printf("x is %i and y is %i", x, y);

}