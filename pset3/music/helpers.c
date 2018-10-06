// Helper functions for music

#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    //more readable and also more portable
    //same as doing int x = (int)d - 48
    int n = fraction[0] - '0';
    int d = fraction[2] - '0';


    return ((int)(((float)n/d) * 8));


}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{

    //Frequency = letter difference factor * octave difference factor * pitch adjustment factor
    char letter = note[0];
    int octave = note[strlen(note)-1] - '0';

    //letter difference
    double ld ;

        switch(letter)
    {
        case 'C' :
            ld = (pow(2.0, (-9.0 / 12.0)));
            break;
        case 'D' :
            ld = (pow(2.0, (-7.0 / 12.0)));
            break;
        case 'E' :
            ld = (pow(2.0, (-5.0 / 12.0)));
            break;
        case 'F' :
            ld = (pow(2.0, (-4.0 / 12.0)));
            break;
        case 'G' :
            ld = (pow(2.0, (-2.0 / 12.0)));
            break;
        case 'A' :
            ld = 1;
            break;
        case 'B' :
            ld = (pow(2.0, (2.0 / 12.0)));
            break;
        default :
            return 0;
    }

    //pitch adjustment
    double pd;

    if(note[1]=='#'){
        pd = pow(2.0, (1.0/12.0));
    }
    else if(note[1]=='b'){
        pd = pow(2.0, (-1.0/12.0));
    }
    else{
        pd = 1;
    }

    //octave difference
    double od = pow(2.0, (octave-4));

    //printf("Letter note is %c and octave is %d and ld is %f and od is %f\n", letter, octave, ld, od);

    return round(440.0*ld*od*pd);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if(strcmp(s, "")){
        return false;
    }
    else{
        return true;
    }
}

/*
// for testing test cases
int main(void){

    // is_rest test
    string a = get_string("enter string: \n");
    printf("It is %d\n", is_rest(a));

    //type casting test
    printf("fraction test %d\n", (int)(((float)3/8) * 8));
    printf("%d\n", duration("3/8"));
    printf("freq is %d\n", frequency("G#4"));
}
*/
