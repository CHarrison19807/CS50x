#include <cs50.h>
#include <stdio.h>
bool checksum(long number);
string cardType(long number);
void getDigits(long number);

int fourthDigit;
int thirdDigit;
int secondDigit;
int firstDigit;
int digitMult;
int digitValue;
int digitMultValue;
int digitSumMult;
int firstDigitMult;
int secondDigitMult;
bool valid = false;
int main(void)
{

    long number = get_long("Number: ");

    getDigits(number);
    valid = checksum(number);
    printf("%s", cardType(number));


}


bool checksum(long number) //luhn's algorithm
{
    long exponent = 1;
    long exponentTwo = 1;
    long exponentThree = 1;
    if (firstDigit != 0) //if visa or mastercard
    {
        for (int i = 15; i > 0; i--)
        {
            exponent *= 10;
            digitValue = (number / exponent) % 10;
            if (i % 2 != 0)
            {
                digitMultValue = digitValue * 2;
                firstDigitMult = digitMultValue % 10;
                secondDigitMult = (digitMultValue / 10) % 10;
                digitSumMult += firstDigitMult + secondDigitMult;
            }
            if (i % 2 == 0)
            {
                digitSumMult += digitValue;
            }
        }
        digitSumMult += number % 10;
        printf("%i\n", digitSumMult);
    }
    else if (fourthDigit == 4 && thirdDigit == secondDigit == firstDigit == 0) //if visa w/ 13 digits
    {
        for (int i = 12; i > 0; i--)
        {
            exponentTwo *= 10;
            digitValue = (number / exponentTwo) % 10;
            printf("%i\n", digitValue);
            if (i % 2 == 0)
            {
                digitMultValue = digitValue * 2;
                firstDigitMult = digitMultValue % 10;
                secondDigitMult = (digitMultValue / 10) % 10;
                digitSumMult += firstDigitMult + secondDigitMult;


            }
            if (i % 2 != 0)
            {
                digitSumMult += digitValue;

            }
        }
        digitSumMult += number % 10;
        printf("%i\n", digitSumMult);
    }
    else if (secondDigit == 3 && (thirdDigit == 4 || thirdDigit == 7)) //if amex
    {
        for (int i = 15; i > 0; i--)
        {
            exponentThree *= 10;
            digitValue = (number / exponentThree) % 10;
            if (i % 2 != 0)
            {
                digitMultValue = digitValue * 2;
                firstDigitMult = digitMultValue % 10;
                secondDigitMult = (digitMultValue / 10) % 10;
                digitSumMult += firstDigitMult + secondDigitMult;
                printf("%i\n", digitSumMult);

            }
            if (i % 2 == 0)
            {
                digitSumMult += digitValue;
                printf("%i\n", digitSumMult);
            }
        }
        digitSumMult += number % 10;
        printf("%i\n", digitSumMult);
    }

    if (digitSumMult % 10 == 0)
    {
        return true;
    }
    return false;
}

void getDigits(long number) // collects 1,2,3,4 digis of card to determine type
{
    long exponent = 1;
    for (int i = 15; i > 0; i--)
    {
        exponent *= 10;
        if (i == 1)
        {
            firstDigit = (number / exponent) % 10;
        }
        if (i == 2)
        {
            secondDigit = (number / exponent) % 10;
        }
        if (i == 3)
        {
            thirdDigit = (number / exponent) % 10;
        }
        if (i == 4)
        {
            fourthDigit = (number / exponent) % 10;
        }
    }
}

string cardType(long number) // returns the type of card
{
    if (valid)
    {
        if (firstDigit == 4)
        {
            return "VISA\n";
        }
        else if (fourthDigit == 4 && thirdDigit == secondDigit == firstDigit == 0)
        {
            return "VISA\n";
        }
        else if (firstDigit == 5 && (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5))
        {
            return "MASTERCARD\n";
        }
        else if (secondDigit == 3 && (thirdDigit == 4 || thirdDigit == 7))
        {
            return "AMEX\n";
        }
        else
        {
            return "INVALID\n";
        }
    }
    else
    {
        return "INVALID\n";
    }
}
