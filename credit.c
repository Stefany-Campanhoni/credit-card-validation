#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool checkPattern(long card);
bool checkSum(long card, int digits);

int main(void)
{
    long cardNumber = get_long("Number: ");
    int digits = 0;
    long temp = cardNumber;

    while (temp != 0)
    {
        temp /= 10;
        digits++;
    }

    const bool isValid = checkSum(cardNumber, digits);

    const bool isPatternValid = checkPattern(cardNumber);

    if (!isValid || digits < 13 || !isPatternValid)
    {
        printf("INVALID\n");
    }
}

bool checkPattern(long card)
{
    long firstTwo = card - (card % (long) pow(10, 13));

    if (card - pow(10, 16) < 0)
    {
        if (firstTwo == 34 * pow(10, 13) || firstTwo == 37 * pow(10, 13))
        {
            printf("AMEX\n");
            return true;
        }
    }

    long firstOne = card - (card % (long) pow(10, 12));

    // printf("firstOne: %ld\n", firstOne);

    if (firstOne - pow(10, 13) >= 0)
    {
        firstOne = card - (card % (long) pow(10, 15));
        firstTwo = card - (card % (long) pow(10, 14));
    }

    if (firstOne == 4 * pow(10, 12) || firstOne == 4 * pow(10, 15))
    {
        printf("VISA\n");
        return true;
    }

    if (firstTwo == 51 * pow(10, 14) || firstTwo == 52 * pow(10, 14) || firstTwo == 53 * pow(10, 14) ||
        firstTwo == 54 * pow(10, 14) || firstTwo == 55 * pow(10, 14))
    {
        printf("MASTERCARD\n");
        return true;
    }

    return false;
}

bool checkSum(long card, int digits)
{
    int acc = 0;

    for (int i = 1; i <= digits; i++)
    {
        int digit = (card % (long) pow(10, i)) / (long) pow(10, i - 1);

        if (i % 2 == 0)
        {
            digit *= 2;

            if (digit > 9)
            {
                acc += digit / 10 + digit % 10;
            }
            else
            {
                acc += digit;
            }
        }
        else
        {
            acc += digit;
        }
    }

    if (acc % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
