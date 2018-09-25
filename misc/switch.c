#include <cs50.h>
#include <stdio.h>

int main (void){

    char c = get_char("Input char: ");

    //check input answer

    switch(c){

        case 'Y':
        case 'y':
            printf("yes\n");
            break;
        case 'N':
        case 'n':
            printf("no\n");
            break;

    }



}