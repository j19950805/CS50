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
        int i = 0;
        while (argv[1][i] != 0)
        {
            if (isupper(argv[1][i]))
            {
                key[i] = (argv[1][i] - 'A');                   
            }
            else
            {
                key[i] = (argv[1][i] - 'a'); 
            }
            i++;
        }
        string pt = get_string("plaintext:  ");
        printf("ciphertext: ");
        int j = 0;
        int k = 0;
        while (pt[j] != 0)
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
            j++;
            k++;
        }
        printf("\n");    
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");    
    }
}

bool isword(string word)
{
    int i = 0;
    while (word[i] != 0)
    {
        if(isalpha(word[i]))
        {
            i++;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}    
