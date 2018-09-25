#include <stdio.h>
#include <cs50.h>

int main (void){

    int n = get_int("Height: ");

    for (int i = 1; i <= n; i++)
    {

        for(int x = 0; x <= n - i - 1; x++){

            printf(" ");
        }


        for(int j = 0; j <= i; j++){


            printf("#");

        }
        printf(" ");

        //include this bit for double sided pyramid

        for(int x = 0; x <= i; x++){


            printf("#");

        }

        printf("\n");
    }



}