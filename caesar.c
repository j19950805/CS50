#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool isnum(string num);
int main(int argc, string argv[])
{
    if (argc == 2 && isnum(argv[1]))
    {
        int key = (atoi(argv[1])) % 26;
        string pt = get_string("plaintext:  ");
        printf("ciphertext: ");
        int i = 0;
        while (pt[i] != 0)
        {
            if (islower(pt[i]))
            {
                printf("%c", 'a' + (pt[i] - 'a' + key) % 26);
            }    
            else if (isupper(pt[i]))
            {
                printf("%c", 'A' + (pt[i] - 'A' + key) % 26);
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
        return 1;
    }
}
bool isnum(string num)
{
    for (int i = 0; i < strlen(num); i++)
    {
        if (!isdigit(num[i]))
        {
            return 0;
        }
    }
    return 1;
}
