#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x;
    do
    {
    x = get_int("Height:");
    }
    while(x>8 || x<=0);
    
    int i,j,k;
    for (i=0; i<x; i++)
    {
        for(k=x ; k>i+1; k--)
        {
            printf(" ");
        }
        for(j=0; j<i+1; j++)
        {
            printf("#");
        }
    printf("\n");     
    }
    return x;
}

