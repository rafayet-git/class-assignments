#include <cs50.h>
#include <stdio.h>

void maro(int height)
{
    //rows
    for (int i = 0 ; i < height ; i++)
    {
        //add space to cols
        for (int h = 0 ; h < height - i - 1 ; h++)
        {
            printf(" ");
        }
        // the actual hasntags
        for (int j = 0 ; j < i + 1 ; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

int main(void)
{
    int h;
    // check if height is between 1-8
    do
    {
        h = get_int("Positive Number: ");
    }
    while (h < 1 || h > 8);
    // does the mareo
    maro(h);
}