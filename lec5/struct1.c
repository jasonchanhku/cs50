#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

#include "struct.h"

int main (void){

    //allocate space for students
    int enrollment = get_int("Enrollment: ");
    //struct named students of length enrollment
    student students[enrollment];

    //prompt for student names and dorm
    for(int i = 0; i < enrollment ; i++){

        students[i].name = get_string("name: ");
        students[i].dorm = get_string("dorm: ");

    }

    //save students to disk
    FILE *file = fopen("students.csv", "w");
    //if successfully opened
    if(file){

        for(int i = 0; i < enrollment; i++){

            // Used to print to a file in a specific, formatted fashion, fprintf prints to the file fp as the string format indicates.

            fprintf(file, "%s,%s\n", students[i].name, students[i].dorm);

        }
        fclose(file);
    }



}