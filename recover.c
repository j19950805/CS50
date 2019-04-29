// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }


    char filename[8];
    BYTE block[512];
    int i = 0;

    while (fread(&block, 1, 512, inptr) == 512)
    {

        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // create output image file
            sprintf(filename, "%.3i.jpg", i);
            FILE *img = fopen(filename, "w");
            i++;
            do
            {
                // copy data from input file
                fwrite(&block, 1, 512, img);
                if (fread(&block, 1, 512, inptr) == 512)
                {
                    fseek(inptr, -512, SEEK_CUR);
                    fread(&block, 1, 512, inptr);
                }
                else
                {
                    break;
                }
            }
            // check the end of an image's data and determine next startpoint
            while (!(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0));

            // close outfile
            fclose(img);
            fseek(inptr, -512, SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // success
    return 0;
}
