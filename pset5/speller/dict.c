#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

char word[45];

typedef struct node{

    char *word;
    struct node *next;

}node;

int hash(char* a){

    int b = tolower(a[0]) - 97;
    return(b);

}

node *hashtable[26];
int count = 0;

int main (void){

    FILE* fp = fopen("small", "r");
    int hash_num;

    while (fscanf(fp, "%s\n", word) != EOF){

        printf("%s", word);
        hash_num = hash(word);
        printf(" hashed to %d\n", hash_num);

        //new node
        node *new = malloc(sizeof(node));

        // allocate memory for word. (Unless int)
        new -> word = malloc(strlen(word)+1);

        strcpy(new->word, word);

        // if new
        if(hashtable[hash_num] == NULL){
            hashtable[hash_num] = new;
            new->next = NULL;
        }
        else{
            //append at head
            new->next = hashtable[hash_num];
            hashtable[hash_num] = new;
        }


    }
    count++;

    fclose(fp);

    return true;


}