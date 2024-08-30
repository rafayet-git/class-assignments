#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for atoi
#include <ctype.h> //for isdigit

bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        // nums in ascii table
        if (s[i] < 48 || s[i] > 57)
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    // using char type causes issues with value over 127
    int newch = c;
    //lowercsae
    if (newch >= 97)
    {
        newch += n;
        while (newch > 122)
        {
            newch -= 26;
        }
    }
    //uppercase
    else if (newch <= 90)
    {
        newch += n;
        while (newch > 90)
        {
            newch -= 26;
        }
    }

    return newch;
}

int main(int argc, string argv[])
{
    // fail case
    if (argc != 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    else if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");
        for (int i = 0; i < strlen(plaintext); i++)
        {
            // dont edit non letters
            if (isalpha(plaintext[i]))
            {
                plaintext[i] = rotate(plaintext[i], key);
            }
        }
        printf("ciphertext: %s\n", plaintext);
    }

}