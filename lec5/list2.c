#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//create node data type with number and a *next pointer

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main (void){

    //memory for numbers
    // *numbers is the first pointer that points to first node of list
    node *numbers =  NULL;

    while(true)
    {
        //prompt for number
        int number = get_int("number: ");

        if(number == INT_MAX){
            break;
        }

        //check whether number is the list
        bool found = false;
        for(node *ptr = numbers; ptr != NULL; ptr = ptr -> next)
        {
            // ptr -> number is like s[i].name, trying to access data the number variable in the node
            if(ptr->number == number)
            {
                found = true;
                break;
            }

        }

        // if not found, add the number to the list
        if(!found)
        {
            // creates a new node called n
            node *n = malloc(sizeof(node));
            if(!n)
            {
                return 1;
            }

            // Add number to list of n
            n->number = number;
            n->next = NULL;
            // if numbers not NULL
            //below loop is to find the end of the list
            // when end of list, place node n there
            if(numbers)
            {
                for(node *ptr = numbers ; ptr!= NULL; ptr = ptr -> next)
                {
                    if(!ptr->next)
                    {
                        ptr->next=n;
                        break;
                    }
                }
            }
            else
            {
                numbers = n;
            }
        }


    }


}
