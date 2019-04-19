#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x;
    // Ensure x is between 1 & 8
    do
    {
        x = get_int("Height:");
    } 
    while(x>8 || x<=0);
    
    // Print pyramid
    for (int i=0; i<x; i++)
    {
        for(int k=x ; k>i+1; k--)
        {
            printf(" ");
        }
        for(int j=0; j<i+1; j++)
        {
            printf("#");
        }
    printf("\n");     
    }
}

