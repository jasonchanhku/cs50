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

    //print it all out

    for(int i = 0; i < enrollment; i++){

        printf("Student name is %s and stays in %s\n", students[i].name, students[i].dorm);
    }

    // problem is that it does not save the data, throws it away



}