// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <cs50.h>
#include "dictionary.h"

typedef struct node{

    char *word;
    struct node *next;

}node;

char word[LENGTH + 1];
node *hashtable[26];
int count = 0;

int hash(const char* a){

    int b = tolower(a[0]) - 97;
    return(b);

}

// Returns true if word is in dictionary else false
bool check(const char *words)
{

    //start a checker pointer
    node *checker = malloc(sizeof(node));

    //determine hashing
    int bucket = hash(words);

    //set checker to point to head of that bucket
    checker = hashtable[bucket];

    while(checker != NULL){

        if(strcasecmp(checker->word, words)==0){
            return true;
        }
        checker = checker -> next;

    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE* fp = fopen(dictionary, "r");
    int hash_num;

    while (fscanf(fp, "%s\n", word) != EOF){

        //printf("%s", word);
        hash_num = hash(word);
        //printf(" hashed to %d\n", hash_num);

        //new node
        node *new = malloc(sizeof(node));

        // first pointer (necessary)?
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

        count++;

    }
    fclose(fp);

    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for(int i = 0; i < 26; i++){

        node *cursor;

        cursor = hashtable[i];

        while(cursor){
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
            return true;
        }

        hashtable[i] = NULL;
    }


    return false;
}
