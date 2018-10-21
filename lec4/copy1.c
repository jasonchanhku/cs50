#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main (void){

    //get string
    char *s = get_string("s: ");
    if(!s){
        return 1;
    }

    //allocate another memory for it
    char *t = malloc((strlen(s) + 1)* sizeof(char));

    if(!t){
        return 1;
    }

    // now s and t have seprate memory addresses
    for(int i = 0 ; i < strlen(s); i++ ){

        t[i] = s[i];

    }

    //capitalization

    if(strlen(t) > 0){
        t[0] = toupper(t[0]);
    }

    // print strings
    printf("s: %s\n", s);
    printf("t: %s\n", t);

    // free memory
    free(t);
    return 0;


}