// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hvalue = hash(word); // Calculates hash value for the word
    node *cursor = table[hvalue];     // Gets the head of the linked list

    while (cursor != NULL) // Goes through the node in the linked list
    {
        if (strcasecmp(cursor->word, word) ==
            0) // Checks if the current node's word matches the input word
        {
            return true;
        }

        cursor = cursor->next; // Moves to the next node
    }
    return false; // If the word is not found
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;                // Stores computed hash value
    for (int i = 0; word[i] != '\0'; i++) // Iterates through each character
    {
        hash = (hash << 2) ^ toupper(word[i]); // Shifts current hash value left by 2 and XOR it
                                               // with the uppercase version of the character
    }
    return hash % N; // Ensures the hash value fits within the bounds of the hash table
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");

    if (file == NULL) // Checks if file has opened
    {
        printf("The file has not opened\n");
        exit(-1);
    }
    // Read each word
    char word[LENGTH + 1]; // Array will store each word read from the file

    while (fscanf(file, "%s", word) != EOF)
    {
        // Process the word
        int index = hash(word); // Word is hashed to determine its index in the hash table

        node *node1 = malloc(sizeof(node)); // Node is allocated to store the word

        if (node1 == NULL) // Checks memory allocation
        {
            return false;
        }

        // Add each word to the hash table
        strcpy(node1->word, word);  // Word is copied into the new node
        node1->next = table[index]; // Node is inserted at the begining of the linked list at the
                                    // appropriate index in the hash table
        table[index] = node1;

        word_count++;
    }

    // Close the dictionary
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) // Iterates over each bucket in the hash table
    {
        node *cursor = table[i]; // Sets cursor to the head of the linked list in the current bucket
        while (cursor != NULL)   // Traverses the linked list
        {
            node *temp = cursor;   // Stores the current node in temp
            cursor = cursor->next; // Moves the cursor to the next node
            free(temp);            // Frees the allocated memory
        }
    }
    return true;
}
