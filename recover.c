#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Declares a new data type called BYTE which holds a byte's worth of data
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Checks to see if there are 2 command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    
    // Opens input file
    FILE *input = fopen(argv[1], "r");
    
    
    // Checks to see if the second command-line argument is a valid file to open
    if (!input)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    
    // Variable and array initialization
    BYTE *bytes = malloc(512 * sizeof(BYTE));
    int file_number = 0;
    char *image = malloc(50 * sizeof(char));
    
    
    // Reads the input file until it finds the first four byte pattern associated with the start of a JPG file. Stores the first 512 bytes in the bytes array
    do
    {
        fread(bytes, sizeof(BYTE), 512, input);
    }
    while (bytes[0] != 0xff || bytes[1] != 0xd8 || bytes[2] != 0xff || bytes[3] < 0xe0 || bytes[3] > 0xef);
    
    
    // Creates a file named ###.jpg where the ### are 3 digit numbers starting at 000.jpg
    sprintf(image, "%03i.jpg", file_number);
    FILE *jpg = fopen(image, "a");
    
    
    // Writes the 512 bytes stored in the bytes array in the newly created ###.jpg and stores the next 512 bytes of the input file in the bytes array
    fwrite(bytes, sizeof(BYTE), 512, jpg);
    fread(bytes, sizeof(BYTE), 512, input);
    
    
    // Repeats while you have not read past the end of the file...
    while (feof(input) == 0)
    {
        // If the stored 512 bytes have the first four byte JPG pattern, then the ###.jpg file will close and a new one will open (###+1).jpg
        // The 512 bytes will be inputted in the new file and the next 512 bytes of the input file are stored in the bytes array
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && bytes[3] >= 0xe0 && bytes[3] <= 0xef)
        {
            fclose(jpg);
            file_number++;
            sprintf(image, "%03i.jpg", file_number);
            jpg = fopen(image, "a");
            fwrite(bytes, sizeof(BYTE), 512, jpg);
            fread(bytes, sizeof(BYTE), 512, input);
        }
        // If the stored 512 bytes don't have the first four byte JPG pattern, then the stored bytes will be written at the end of the ###.jpg file
        // The next 512 bytes of the input file are stored in the bits array
        else
        {
            fwrite(bytes, sizeof(BYTE), 512, jpg);
            fread(bytes, sizeof(BYTE), 512, input);
        }
    }
    
    
    // Closes the last opened ###.jpg file and frees the image and bytes variables
    fclose(jpg);
    free(image);
    free(bytes);
}