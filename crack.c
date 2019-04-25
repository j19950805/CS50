#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2 && strlen(argv[1]) == 13)
    {
        //get salt value.
        char a[2];
        strncpy(a, argv[1], 2);
        const char *salt = a;
        
        char key[5] = "";
        //test one-charaters
        for (key[0] = 'A'; key[0]  <= 'z'; key[0]++)
        {
            const char *z = crypt(key, salt);
            if (strcmp(z, argv[1]) == 0)
            {
                printf("%s\n", key);
                return 0;
            }
            if (key[0] == 'Z')
            {
                key[0] = 'a' - 1;
            }   
        }
        //test two-charaters
        for (key[0] = 'A'; key[0]  <= 'z'; key[0]++)
        {
            for (key[1] = 'A'; key[1]  <= 'z'; key[1]++)
            {
                const char *z = crypt(key, salt);
                if (strcmp(z, argv[1]) == 0)
                {
                    printf("%s\n", key);
                    return 0;
                }
                if (key[1] == 'Z')
                {
                    key[1] = 'a' - 1;
                } 
            }
            if (key[0] == 'Z')
            {
                key[0] = 'a' - 1;
            }   
        }
        //test three-charaters
        for (key[0] = 'A'; key[0]  <= 'z'; key[0]++)
        {
            for (key[1] = 'A'; key[1]  <= 'z'; key[1]++)
            {
                for (key[2] = 'A'; key[2]  <= 'z'; key[2]++)
                {    
                    const char *z = crypt(key, salt);
                    if (strcmp(z, argv[1]) == 0)
                    {
                        printf("%s\n", key);
                        return 0;
                    }
                    if (key[2] == 'Z')
                    {
                        key[2] = 'a' - 1;
                    }
                }
                if (key[1] == 'Z')
                {
                    key[1] = 'a' - 1;
                } 
            }
            if (key[0] == 'Z')
            {
                key[0] = 'a' - 1;
            }   
        }
        //test four-charaters
        for (key[0] = 'A'; key[0]  <= 'z'; key[0]++)
        {
            for (key[1] = 'A'; key[1]  <= 'z'; key[1]++)
            {
                for (key[2] = 'A'; key[2]  <= 'z'; key[2]++)
                {    
                    for (key[3] = 'A'; key[3]  <= 'z'; key[3]++)
                    {
                        const char *z = crypt(key, salt);
                        if (strcmp(z, argv[1]) == 0)
                        {
                            printf("%s\n", key);
                            return 0;
                        }
                        if (key[3] == 'Z')
                        {
                            key[3] = 'a' - 1;
                        }
                    }
                    if (key[2] == 'Z')
                    {
                        key[2] = 'a' - 1;
                    }
                }
                if (key[1] == 'Z')
                {
                    key[1] = 'a' - 1;
                } 
            }
            if (key[0] == 'Z')
            {
                key[0] = 'a' - 1;
            }   
        }
        //test five-charaters
        for (key[0] = 'A'; key[0]  <= 'z'; key[0]++)
        {
            for (key[1] = 'A'; key[1]  <= 'z'; key[1]++)
            {
                for (key[2] = 'A'; key[2]  <= 'z'; key[2]++)
                {    
                    for (key[3] = 'A'; key[3]  <= 'z'; key[3]++)
                    {
                        for (key[4] = 'A'; key[4]  <= 'z'; key[4]++)
                        {
                            const char *z = crypt(key, salt);
                            if (strcmp(z, argv[1]) == 0)
                            {
                                printf("%s\n", key);
                                return 0;
                            }
                            if (key[4] == 'Z')
                            {
                                key[4] = 'a' - 1;
                            }
                            if (key[4] == 'z')
                            {
                                printf("Usage: ./crack hash\n");
                                return 1;
                            }
                        }
                        if (key[3] == 'Z')
                        {
                            key[3] = 'a' - 1;
                        }
                    }
                    if (key[2] == 'Z')
                    {
                        key[2] = 'a' - 1;
                    }
                }
                if (key[1] == 'Z')
                {
                    key[1] = 'a' - 1;
                } 
            }
            if (key[0] == 'Z')
            {
                key[0] = 'a' - 1;
            }   
        }
    }
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
}
