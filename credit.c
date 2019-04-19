#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    long x = get_long("Number:");
    int y = x / pow(10,12);
    int digit1, digit2;
    int sum_digit = 0;
    while(x >= 1)
    {
        digit1 = x / 10 % 10;
        digit2 = x % 10;
        if (digit1*2 / 10 == 0)
        {
            sum_digit = sum_digit + digit1 * 2 + digit2;   
        }
        else
        {
            sum_digit = sum_digit + digit1 * 2 % 10 + 1 + digit2;
        }
        x = x / 100;
    }
    
    if(sum_digit % 10 != 0){
        printf("INVALID\n");
    }
    else if(y / 10 == 34 || y / 10 == 37)
    {
        printf("AMEX\n");
    }
    else if(y / 100 < 99 && y / 100 > 9)
    {
        printf("MASTERCARD\n");
    }
    else if(y / 1000 == 4 || y == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
