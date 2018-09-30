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
    {   //case for lowercase
        if islower(plain[i]){

            // can this be turned into a function ? but for lower a is 97 for upper it is 65
            int ai = plain[i] - 97;
            int mod = (ai + k) % 26;
            printf("%c", (97 + mod));

        }
        //case for uppercase
        else if isupper(plain[i]){

            // can this be turned into a function ? but for lower a is 97 for upper it is 65
            int ai = plain[i] - 65;
            int mod = (ai + k) % 26;
            printf("%c", (65 + mod));

        }
        // assuming rest of cases are integers, space, and special chars (!isalpha)
        else{
            printf("%c", plain[i]);
        }

    }

    printf("\n");


}