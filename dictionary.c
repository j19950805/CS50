// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Set dictionary size counter to zero
int size_dictionary = 0;

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // Set cursor begin from root;
        node *cursor = root;
        for (int i = 0, length = strlen(word) + 1; i < length; i++)
        {
            int x;
            if (isalpha(word[i]) == true)
            {
                x = tolower(word[i]) - 'a';
                printf("%i", x);
            }
            else if (isalpha(word[0]) == false)
            {
                break;
            }
            else
            {
                x = 26;
            }

            // Check if the letter path already exist
            if (cursor->children[x] == NULL)
            {

                // Set a new node
                node *new_node = malloc(sizeof(node));
                if (new_node == NULL)
                {
                    unload();
                    return false;
                }
                new_node->is_word = false;
                for (int j = 0; j < N; j++)
                {
                    new_node->children[j] = NULL;
                }

                // Link the children pointer to the new node
                cursor->children[x] = new_node;
            }

            //move the cursor down along the letter path till the end of the word
            if (word[i] != 0)
            {
                cursor = cursor->children[x];
            }
        }

        // Set "is_word = true" at the end node of the path
        cursor->is_word = true;

        // Count the number of words we load from dictionary
        size_dictionary++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Check if the dictionary load
    if (size_dictionary > 0)
    {
        return size_dictionary;

    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Set cursor begin from root;
    node *cursor = root;

    node *tmp;

    // Check if the word can go through one path in the tries
    for (int i = 0, length = strlen(word) + 1; i < length ; i++)
    {
        int x;
        if ((isalpha(word[i])) == true)
        {
            x = tolower(word[i]) - 'a';
        }
        else
        {
            x = 26;
        }

        // Set tmp to cursor before the cursor jumpping into a null children pointer
        tmp = cursor;
        cursor = cursor->children[x];
        if (cursor == NULL)
        {
            return false;
        }
    }

    // Check if the end of the path referring to a word
    if (tmp->is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Unloads dictionary from memory, returning true if successful else false

// Declare a recursion function
void destroy(node *destroy_node);

bool unload(void)
{
    // Set dictionary size counter to zero
    size_dictionary = 0;

    // Set cursor begin from root;
    node *cursor = root;

    // Execute the recursion function;
    destroy(cursor);

    // Finished
    return true;
}


void destroy(node *destroy_node)
{
    // Check if we touch an end of a path and set recursive case
    for (int i = 0; i < N; i++)
    {
        if (destroy_node->children[i] != NULL)
        {
            destroy(destroy_node->children[i]);
        }
    }

    // Base case: free the memory of the end of a path
    free(destroy_node);
}