#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

typedef struct node{

    int info;
    struct node *next;

}
node;

node *head = NULL;
node *hashtable[26];
int count = 0;

void insert(int x){

    node *ptr = malloc(sizeof(node));
    ptr -> info = x;
    ptr -> next = head;
    head = ptr;

// head -> ()

// ptr -> [1 | ] -> head -> ()

// head -> [1 | ] -> ()

// ptr -> [2 | ] -> head -> [1 | ] -> ()

// head -> [2 | ] -> [1 | ] -> ()


}



int main (void){

    int x, n;
    printf("Number of elements: \n");
    scanf("%d", &n);

    for (int i = 0 ; i < n ; i++){

        printf("Enter element: \n");
        scanf("%d", &x);
        insert(x);


    }

    for(node *ptr = head; ptr!=NULL; ptr= ptr->next){
        printf("element is: %d\n", ptr-> info);

    }


}