#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // check for ONE filename placed
    {
        printf("Usage: recover [filename]\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) // invalid file
    {
        printf("Usage: recover [filename]\n");
        return 1;
    }
    uint8_t bytes[512];
    FILE *jpg;
    int fnum = 0;
    char name[8]; // size is 8 because there are 7 characters in "###.jpg" and you add 1 for null
    while (fread(bytes, 1, 512, file) == 512)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] <= 0xef && bytes[3] >= 0xe0))  // check for jpg header
        {
            sprintf(name, "%03i.jpg", fnum);
            if (fnum != 0)
            {
                // close old file
                fclose(jpg);
            }
            fnum++;
            jpg = fopen(name, "w");
        }
        if (fnum != 0)
        {
            // add the block to file
            fwrite(bytes, 1, 512, jpg);
        }
    }
}