// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Dynamically allocates variables 'h' and 'w'
    int *h = malloc(sizeof(int));
    *h = hash(word);
    char *w = malloc(strlen(word) + 1);
    
    // If there are no words with the has value in the dictionary, returns false (also free's variable 'h' and 'w')
    if (table[*h] == NULL)
    {
        free(h);
        free(w);
        return false;
    }
    
    // Creates a temporary pointer that will move through the hash table with the hash value of the selected word (also free's 'h')
    node *temp = table[*h];
    free(h);
    
    // Converts the word from text to all lowercase to match the dictionary format, stored in the previously declared variable 'w'
    for (int i = 0, l = strlen(word) + 1; i < l; i++)
    {
        w[i] = tolower(word[i]);
    }
    
    // Checks to see if the selected word is the first word in the hash array (free's 'w' and returns true if they match)
    if (strcmp(temp->word, w) == 0 )
    {
        free(w);
        return true;
    }
    
    // Checks through every other word with the same hash value (free's 'w' and returns true if any matches the selected word)
    while (temp->next != NULL)
    {
        temp = temp->next;
        if (strcmp(temp->word, w) == 0)
        {
            free(w);
            return true;
        }
    }
    
    // If the word is not found in the hash table, returns false and free's 'w'
    free(w);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // This is the popular hash function djb2
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }
    
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Sets all of the hash tables elements to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    // Opens dictionary file put in as argv(1) or as default dictionaries/large
    FILE *file = fopen(dictionary, "r");
    
    // If the file cannot be opened, closes file and returns false
    if (!file)
    {
        fclose(file);
        return false;
    }
    
    // Dynamically allocates a variable for the current read word from the dictionary, with the size of the maximum length of a word + 1
    char *read_word = malloc(LENGTH + 1);
    
    // Scans each word one by one from the dictionary file opened
    while (fscanf(file, "%s", read_word) != EOF)
    {
        // Dynamically allocates variable 'h' for the hash value of the read word
        unsigned int *h = malloc(sizeof(unsigned int));
        *h = hash(read_word);
        
        // Creates a new node for the new word
        node *n = malloc(sizeof(node));
        
        // Checks to see if we have run out of space, if so, free's 'h' and 'read_word' and closes the file while also returning false
        if (n == NULL)
        {
            free(h);
            free(read_word);
            fclose(file);
            return false;
        }
        
        // Transfers the scanned word from the file to the 'n' node's word element
        for (int i = 0, s = strlen(read_word) + 1; i < s; i++)
        {
            n->word[i] = read_word[i];
        }
        
        // Makes n->next NULL
        n->next = NULL;
        
        // If this is the first word inputted into the hash table with its hash value, then sets the initial table node equal to the new node
        if (table[*h] == NULL)
        {
            table[*h] = n;
        }
        
        // If this is not the first word, links the node into the next available spot
        else
        {
            node *temp = table[*h];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = n;
        }
        
        // Free's variable 'h'
        free(h);
    }
    
    // If all works out, free's 'read_word' and closed the dictionary file while also returning true
    free(read_word);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Creates a variable 'counter'
    int counter = 0;
    
    // Runs through each of the bucket's linked lists to see how many words were added into the hash table
    // Increases counter by 1 each time a node is found
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        while (temp != NULL)
        {
            counter++;
            temp = temp->next;
        }
    }
    
    // Returns the counter value for amount of words in the hash table
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free's the hash table starting from each array's head node, then moving onto the next linked node
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    
    // Returns true
    return true;
}
