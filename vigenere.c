#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool isword(string word);
int main(int argc, string argv[])
{    
    if (argc == 2 && isword(argv[1]))
    {
        int key_length = strlen(argv[1]);
        int key[key_length];
        for (int i = 0; i < key_length ; i++)
        {
            if (isupper(argv[1][i]))
            {
                key[i] = (argv[1][i] - 'A');                   
            }
            else
            {
                key[i] = (argv[1][i] - 'a'); 
            }
        }
        string pt = get_string("plaintext:  ");
        printf("ciphertext: ");
        int k = 0;
        for (int j = 0; j < strlen(pt); j++)
        { 
            if (islower(pt[j]))
            {
                printf("%c", 'a' + (pt[j] - 'a' + key[k % key_length]) % 26);
            }    
            else if (isupper(pt[j]))
            {
                printf("%c", 'A' + (pt[j] - 'A' + key[k % key_length]) % 26);
            }
            else
            {
                printf("%c", pt[j]);
                k--;
            }
            k++;
        }
        printf("\n");    
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
}

bool isword(string word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        if (!isalpha(word[i]))
        {
            return 0;
        }
    }
    return 1;
}    
