#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    int key = (atoi(argv[1])) % 26;
    if (argc == 2 && key > 0)
    {
        string pt = get_string("plaintext:  ");
        printf("ciphertext: ");
        int i = 0;
        while (pt[i] != 0)
        {
            if (islower(pt[i]))
            {
                if (pt[i] + key > 'z')
                {
                    printf("%c", pt[i] + key - 26);
                }
                else
                {
                    printf("%c", pt[i] + key);    
                }      
            }
            else if (isupper(pt[i]))
            {
                if (pt[i] + key > 'Z')
                {
                    printf("%c", pt[i] + key - 26);
                }
                else
                {
                    printf("%c", pt[i] + key);    
                }
            }
            else
            {
                printf("%c", pt[i]);
            }
            i++;
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");    
    }
}
