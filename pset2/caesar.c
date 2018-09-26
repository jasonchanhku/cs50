#include <cs50.h>
// for toupper, tolower, etc
#include <ctype.h>
#include <stdio.h>
//for str len
#include <string.h>
int main (int argc, string argv[]){

    //k conditions
    // - non-negative integer
    // - must be entered at command line
    if (argc != 2)
    {
        printf("Error!, not the right input format\n");
        exit(1);
    }

    //converts k into an integer
    int k = atoi(argv[1]);

    //get user input
    string plain = get_string("plaintext: ");
    printf("k is: %i\n", k);
    printf("plaintext is: %s\n", plain);

    //assume all lowercase first
    // make case for upper case and also spaces
    printf("ciphertext: ");
    for(int i = 0; i < strlen(plain); i++)
    {
        int ai = plain[i] - 97;
        int mod = (ai + k) % 26;
        printf("%c", (97 + mod));

    }

    printf("\n");

    /*
    printf("k is %i\n", k);

    printf("num is :%i\n",'A' + 20);

    printf("%i\n", 5 % 26 );
    */

}