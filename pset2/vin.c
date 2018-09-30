#include <cs50.h>
// for toupper, tolower, etc
#include <ctype.h>
#include <stdio.h>
//for str len
#include <string.h>

/*

TODO (completed)

Get the key, k
- 2nd cmd line argument,
- must be alphabetical

Get the plaintext
- get_string

Ciphering
- get the len of key
- normalize the indexing
- positioning will be x % len

*/


int main (int argc, string argv[]){

    //k conditions
    // - 2nd argument of command line
    // - must be alphabetical
    // - upper or lowercase in different (last priority)
    if (argc != 2)
    {
        printf("Error!, not the right input format\n");
        exit(1);
    }

    //creates k
    string k = argv[1];
    //more efficient to initialize here than calling function repetitively
    int l = strlen(k);

    // check if k is fully a string or not
    // use for loop as isalpha only takes one char at a time
    for(int i = 0 ; i < l; i++){
        //if not, then exit
        if(!isalpha(k[i])){
            printf("key is not fully alphabetical!\n");
            exit(1);
        }
    }
    //at this point, k has been verified
    //get user input for plaintext
    string plain = get_string("plaintext: ");
    printf("k is: %s\n", k);
    printf("plaintext is: %s\n", plain);

    // make case for upper case and also spaces
    printf("ciphertext: ");

    int rot = 0;
    for(int i = 0; i < strlen(plain); i++)
    {

        if isalpha(plain[i]){

            //case for lowercase
            if islower(plain[i]){

                //position of current iteration in key
                int pos = rot % l;
                // normalize key index
                int index = tolower(k[pos]) - 97;
                // normalize plaintext index
                int ai = plain[i] - 97;
                // compute shifts in current iteration
                int mod = (ai + index) % 26;
                // convert back to ASCII and print
                printf("%c", (97 + mod));
                rot++;

            }
            //case for uppercase

            else if isupper(plain[i]){

                //position of current iteration in key
                int pos = rot % l;
                // normalize key index
                int index = toupper(k[pos]) - 65;
                // normalize plaintext index
                int ai = plain[i] - 65;
                // compute shifts in current iteration
                int mod = (ai + index) % 26;
                // convert back to ASCII and print
                printf("%c", (65 + mod));
                rot++;

            }


        }
    // assuming rest of cases are integers, space, and special chars (!isalpha)
    else{
        printf("%c", plain[i]);
        }

    }

    printf("\n");


}