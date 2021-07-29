// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
// NB: global variables are automatically initialized to zero (i.e NULL for pointers)
node *table[N];

// (Global) number of words in dictionary
int N_WORDS = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain hash value to use as index
    unsigned int hashidx = hash(word);

    // Traverse the linked list on the hash table location given by the index
    for (node *tmp = table[hashidx]; tmp != NULL; tmp = tmp->next)
    {
        // Compare strings, case-insentiviely
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // First attempt: simple first letter in word hash function
    // return toupper(word[0]) - 'A';

    // Second attemp: djb2 from http://www.cse.yorku.ca/~oz/hash.html
    // This is a case-insensitive implementation of djb2
    unsigned long hash = 5381;

    for (const char *c = word; *c != '\0'; c++)
    {
        hash = ((hash << 5) + hash) + toupper(*c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictfile = fopen(dictionary, "r");
    if (dictfile == NULL)
    {
        return false;
    }

    // Initialize temporary word
    char tmpword[LENGTH + 1];

    // Read strings from file one at a time
    while (fscanf(dictfile, "%s", tmpword) != EOF)
    {
        // Allocate memory for new node
        node *dictword = malloc(sizeof(node));
        if (dictword == NULL)
        {
            return false;
        }
        else
        {
            // Copy word into node
            strcpy(dictword->word, tmpword);
            // Set next to NULL
            dictword->next = NULL;
        }

        // Hash word to obtain hash value to use as index
        unsigned int hashidx = hash(dictword->word);

        // Insert node into hash table at hash index
        dictword->next = table[hashidx];
        table[hashidx] = dictword;

        // Update count of words in dictionary
        N_WORDS++;
    }

    // Close files and free memory
    fclose(dictfile);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return N_WORDS;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) // For each element in the hash table array
    {
        // Free the linked list associcated with that array position
        while (table[i] != NULL)
        {
            // Store pointer to next node
            node *tmp = table[i]->next;
            // Free node at the list's head
            free(table[i]);
            // Make list point at next node
            table[i] = tmp;
        }
    }

    return true;
}
