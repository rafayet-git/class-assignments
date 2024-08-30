// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 150000; // worst case scenario for word
unsigned int numwords = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);
    for (node *c = table[h]; c != NULL; c = c->next)
    {
        if (strcasecmp(word, c->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int total = 0;
    int length = strlen(word);
    // hash word by adding lower value to total
    for (int i = 0; i < length; i++)
    {
        total += (tolower(word[i]) * (i + 1));
    }
    return total % N; //make sure its not over size
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char word[LENGTH + 1]; // extra 1 for null character
    int has; // hash of word
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *tmp = malloc(sizeof(node)); // do not free here
        if (tmp == NULL)
        {
            return false;
        }
        has = hash(word);
        numwords++;
        strcpy(tmp->word, word);
        tmp->next = table[has]; // point to next word to add to list
        table[has] = tmp;

    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numwords;
    // numwords is always 0 when unloaded
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //for loop to find non-null value, then use while to free all
    for (int i = 0; i < N; i++)
    {
        node *nextword = table[i];
        while (nextword != NULL) // dont do anything if there is nothing on the table
        {
            node *temp = nextword;
            nextword = nextword->next; // store tmp value for next word
            free(temp);
            i++;
        }
    }
    return true;
}
