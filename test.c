#include <cs50.h>
#include <stdio.h>
#include <crypt.h>

int main(void)
{
    string x = get_string("password:");
    const char *salt = "50";
    const char *z = crypt(x , salt);
    printf("%s\n", z);
}
