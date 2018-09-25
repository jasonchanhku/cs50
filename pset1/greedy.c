// greedy algorithm implementation

#include <stdio.h>
#include <cs50.h>

int main (void){

    float d = get_float("Change owed: ");
    int c = d*100;
    printf("Change owed is: %i\n", c);
    // Greedy algorithm
    // 0.25, 0.10, 0.05, 1.00
    // while still bigger than 1, subtract value, then keep adding, then follow by smaller coins

    // multiple while ?

    int count = 0;

    while (c >= 25){

        c -= 25;
        count +=1;

    }
    printf("%f\n", (float)c/100);
    printf("Count is: %i\n", count);
    while (c >= 10){

        c -= 10;
        count +=1;

    }
    printf("%f\n", (float)c/100);
    printf("Count is: %i\n", count);
    while (c >= 5){

        c -= 5;
        count +=1;

    }
    printf("%f\n", (float)c/100);
    printf("Count is: %i\n", count);
    while( c >= 1){

        c -= 1;
        count +=1;
    }
    printf("%f\n", (float)c/100);
    printf("Count is: %i\n", count);
    printf("number of coins is: %i\n", count);

}