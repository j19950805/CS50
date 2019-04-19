#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x;
    // Ensure x is between 1 & 8
    do {
        x = get_int("Height:");
    } while(x > 8 || x <= 0);
    // Print pyramid
    for(int i=0; i < x; i++) {
        for(int j=x ; j > i+1; j--) {
            printf(" ");    
        }
        for(int k=0; k < i+1; k++) {
            printf("#");    
        }
        printf("  ");
        for(int k=0; k < i+1; k++) {
            printf("#");    
        }
        printf("\n");    
    }
}
