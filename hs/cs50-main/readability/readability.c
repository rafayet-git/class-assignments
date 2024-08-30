#include <cs50.h>
#include <stdio.h>
#include <string.h> // use for strlen
#include <math.h>   // use for round

int count_sentences(string text)
{
    // similar code to count_letters
    int total = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            total++;
        }
    }
    return total;
}

int count_words(string text)
{
    // similar code to count_letters
    int total = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            total++;
        }
    }
    return total;
}

int count_letters(string text)
{
    int total = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] < 91 && text[i] > 64) || (text[i] < 123 && text[i] > 96))
        {
            total++;
        }
    }
    return total;
}

int main(void)
{
    string h = get_string("text: ");
    // i had to use floats otherwise the answer would just stick to 1.84 because s is always 0
    float W = count_words(h);
    float L = (count_letters(h) / W) * 100;
    float S = (count_sentences(h) / W) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8); // round needed for int 
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}