#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    float dollars;
    // Check if x is a non-negative real number
    do
    {
        dollars = get_float("Change owed:");
    }
    while (dollars < 0);
    // Change dollars to cents
    int cents = round(dollars * 100);
    // Calculate how many coins do customer get back and print the result
    int cash = cents / 25 + cents % 25 / 10 + cents % 25 % 10 / 5 + cents % 25 % 10 % 5;
    printf("%i\n", cash);
}
    
