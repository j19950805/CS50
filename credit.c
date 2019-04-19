#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    long x = get_long("Number:");
    long y = x;
    int digit1, digit2;
    int sum_digit1 = 0;
    int sum_digit2 = 0;
    while(x > 1)
    {
        digit1 = x / 10 % 10;
        if (digit1*2/10 == 0)
        {
            sum_digit1 = sum_digit1 + digit1*2;   
        }
        else
        {
            sum_digit1 = sum_digit1 + digit1 * 2 % 10 + 1;
        }
        digit2 = x % 10;
        sum_digit2 = sum_digit2 + digit2;
        x = x / 100;
    }
    int result = sum_digit1 + sum_digit2;
    int z = y/pow(10,12);
    
    if(result%10 != 0){
        printf("INVALID\n");
    }
    else if(z/10 == 34 || z/10 == 37)
    {
        printf("AMEX\n");
    }
    else if(z/100 < 99 && z/100 > 9)
    {
        printf("MASTERCARD\n");
    }
    else if(z/1000 == 4 || z == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
