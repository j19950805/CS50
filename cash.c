#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    float dollars;
    do
    {
    dollars = get_float("Change owed:");
    }
    while(dollars<0);
    int cents = round(dollars*100);
    int change = cents/25 + cents%25/10 + cents%25%10/5 + cents%25%10%5;
    printf("%i\n", change);
}
    
