#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

typedef struct node
{
    char word[5];
    struct node *next;

}
node;

int main (void){

    //creating node1 -> ["Hello" |  ] ->
    node *node1 = malloc(sizeof(node));
    strcpy(node1->word, "Hello");

    node *node2 = malloc(sizeof(node));
    strcpy(node2->word, "World");

    node1->next = node2;

    for(node *ptr = node1; ptr != NULL ; ptr = ptr->next  ){
        printf("String is: %s \n", ptr->word);
    }
}