#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Variables used in the latter portion of the code
    int cipher_letter;
    int letter_counter;
    int n;
    int x;
    int y;
    int z;
    
    
    //Tests to see if there are only 2 command line arguments (one being the command to run the code and the other being the cipher)
    if (argc != 2)
    {
        printf("Error 1: There must be two sets of input- the command to run the code and the cipher key without any spaces.\n");
        return 1;
    }
    
    
    //Checks to see if any letter is used more than once in the cipher
    int ascii[122];
    for (n = 0; n < 122; n++)
    {
        ascii[n] = 0;
    }
    for (cipher_letter = 0; cipher_letter < 26; cipher_letter++)
    {
        x = argv[1][cipher_letter];
        ascii[x]++;
        if (argv[1][cipher_letter] >= 'a' && argv[1][cipher_letter] <= 'z')
        {
            if ((ascii[x] + ascii [x - 32]) > 1)
            {
                printf("Error 2: Duplicate use of letters in cipher (can only use each letter once)\n");
                return 1;
            }
        }
        if (argv[1][cipher_letter] >= 'A' && argv[1][cipher_letter] <= 'Z')
        {
            if ((ascii[x] + ascii [x + 32]) > 1)
            {
                printf("Error 2: Duplicate use of letters in cipher (can only use each letter once)\n");
                return 1;
            }
        }
    }
    
    
    //Counts the total number of letters inputted in the cipher
    for (cipher_letter = 0, letter_counter = 0; cipher_letter < 26; cipher_letter++)
    {
        if (argv[1][cipher_letter] >= 'a' && argv[1][cipher_letter] <= 'z')
        {
            letter_counter++;
        }
        if (argv[1][cipher_letter] >= 'A' && argv[1][cipher_letter] <= 'Z')
        {
            letter_counter++;
        }
    }
    
    
    //If the inputted cypher is not 26 letters, then an error message will be given
    if (letter_counter != 26)
    {
        printf("Error 3: Cipher does not contain the 26 letter input required\n");
        return 1;
    }
    
    
    //Asks the user to provide text to be translated using the cipher
    string answer = get_string("plaintext:  ");
    
    
    //Translates the inputted text using the cipher
    for (y = 0; y < strlen(answer); y++)
    {
        //Translates any lowercase letters
        if (answer[y] >= 'a' && answer[y] <= 'z')
        {
            z = answer[y] - 97;
            argv[1][z] = tolower(argv[1][z]);
            answer[y] = argv[1][z];
        }
        
        //Translates any uppercase letters
        else if (answer[y] >= 'A' && answer[y] <= 'Z')
        {
            z = answer[y] - 65;
            argv[1][z] = toupper(argv[1][z]);
            answer[y] = argv[1][z];
        }
    }
    
    
    //This is the outputted text transalated using the cipher
    printf("ciphertext: %s\n", answer);
}