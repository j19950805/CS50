// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // check n value
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "Invalid multiple.\n");
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

    // Change width and height value in HEADER
    int originwidth = bi.biWidth;

    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine resized padding for scanlines
    int padding_2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Change size value in HEADER
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + padding_2) * abs(bi.biHeight);
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;
    printf("biSizeImage:%i, bfSize:%i\n", bi.biSizeImage, bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int vertical = 0;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline and resize horizontally
        for (int j = 0; j < originwidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile and resize horizontally
            for (int l = 0; l < n; l++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }


        vertical++;

        // Go back to startpoint
        if(vertical < n)
        {
            fseek(inptr, - sizeof(RGBTRIPLE) * originwidth , SEEK_CUR);
        }
        else
        {
            vertical = 0;
            // skip over padding, if any
            fseek(inptr, padding_1, SEEK_CUR);
        }


        // Add padding back (to demonstrate how)
        for (int k = 0; k < padding_2; k++)
        {
            fputc(0x00, outptr);
        }

    }
    printf("biSizeImage:%i, bfSize:%i\n", bi.biSizeImage, bf.bfSize);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
