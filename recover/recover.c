#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Checks for a single command-line argument
    if (argc != 2)
    {
        printf("Usage: recover [memory card]\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Checks if the memory card has opened
    if (card == NULL)
    {
        printf("The file has not opened\n");
        exit(-1);
    }
    else
    {

        // Create a buffer for a block of data
        uint8_t *buffer = malloc(512 * sizeof(uint8_t)); // Malloc dynamically allocates memory

        if (buffer == NULL)
        {
            printf("The memory has not been allocated");
        }

        int i = 0;
        FILE *img = NULL; // Initializing pointer to null to avoid giving it a garbage value
        // While there's still data left to read from the memory card
        while (fread(buffer, 1, 512, card) == 512)
        {
            // Create JPEGS from the data
            char filename[8];

            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0) // Checks if all 4 bytes are present in the block to
                                            // signify the start of a JPEG file
            {
                if (img != NULL) // Checks if image file is open
                {
                    fclose(img);
                }

                // Make a new JPEG file
                sprintf(filename, "%03i.jpg", i); // Prints the filename of the images
                img = fopen(
                    filename,
                    "w"); // Opens the new file in order to write the data found in the memory card
                i++;      // Increments the file number
            }

            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img); // Writes the data into the file
            }
        }
        fclose(img);  // Closes the image file
        fclose(card); // Closes the card
        free(buffer); // Dynamically de-allocates memory
    }
}
