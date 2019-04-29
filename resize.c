// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: f infile outfile\n");
        return 1;
    }

    // remember filenames
    float f = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // check n value
    if (f <= 0 || f > 100)
    {
        fprintf(stderr, "Invalid f.\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine original padding for scanlines
    int padding_1 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Change width and height value in HEADER and save the original value
    int originwidth = bi.biWidth;
    int originheight = abs(bi.biHeight);

    bi.biWidth = ceil(bi.biWidth * f);
    bi.biHeight = ceil(bi.biHeight * f);

    // determine resized padding for scanlines
    int padding_2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Change size value in HEADER
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + padding_2) * abs(bi.biHeight);
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, v_resize_count = 0; i < originheight; i++)
    {
        // skip some scanlines when shrinking an image
        if (ceil(f * i + f) - ceil(f * i) == 0)
        {
            fseek(inptr, sizeof(RGBTRIPLE) * originwidth + padding_1, SEEK_CUR);
            continue;
        }

        // iterate over pixels in scanline and resize horizontally
        for (int j = 0; j < originwidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile and resize horizontally
            for (int k = 0; k < ceil(f * j + f) - ceil(f * j); k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        v_resize_count++;

        // Add padding to output image
        for (int l = 0; l < padding_2; l++)
        {
            fputc(0x00, outptr);
        }


        // Check if we need to copy the scanline again
        if (v_resize_count < ceil(f * i + f) - ceil(f * i))
        {
            // Go back to startpoint and copy the scanline again
            fseek(inptr, - sizeof(RGBTRIPLE) * originwidth, SEEK_CUR);
            i--;
        }
        else
        {
            // skip over padding in input file , if any
            fseek(inptr, padding_1, SEEK_CUR);
            // Set counter for next scanline
            v_resize_count = 0;
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
