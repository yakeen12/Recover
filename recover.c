#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>



int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover card.raw");
        return 1;
    }

    // Open file.
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    unsigned char buffer[512];

    int count_image = 0;

    FILE *OtputFile = NULL;
    char *filename = malloc(8 * sizeof(char));


    while (fread(buffer, sizeof(char), 512, file) != 0)
    {

        //check if bytes is start of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //write jpeg into file name in form 001.jpg, 002.jpg and so on
            sprintf(filename, "%03i.jpg", count_image);

            //open Out_file for writing
            OtputFile = fopen(filename, "w");



            count_image++;
        }

        if (OtputFile != NULL)
        {
            fwrite(buffer, sizeof(char), 512, OtputFile);
        }

    }

    free(filename);
    fclose(OtputFile);
    fclose(file);




}
