#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    float x;
    do{
        x = get_float("Change owed:");
    }while(x<0);
    int y = round(x*100);
    int z = y/25 + y%25/10 + y%25%10/5 + y%25%10%5;
    printf("%i\n", z);
}
    
