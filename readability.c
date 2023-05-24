#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //Get text input from user
    string text = get_string("Text: ");

    //Create variable for number of letters
    double letters = 0;

    //Create variable for number of words (It starts off as 1 because in the word counter, it will only pick up words that have spaces after it. This will exclude the last word in the text because it only ends with a period)
    double words = 1;

    //Create variable for number of sentences
    double sentences = 0;

    //This is the function to count the number of letters, words and sentences in the inputted text
    for (int n = 0, b = strlen(text); n < b; n++)
    {
        //Counts the number of lowercase letters in the input
        if (text[n] >= 'a' && text[n] <= 'z')
        {
            letters++;
        }
        //Counts the number of uppercase letters in the input (added to same "letters" variable as the counter above)
        if (text[n] >= 'A' && text[n] <= 'Z')
        {
            letters++;
        }
        //Counts the number of words in the input (looks for spaces, periods, exclamation points and question marks to increase counter)
        if (text[n] == ' ')
        {
            words++;
        }
        //Counts the number of sentences in the input (looks for periods, exclamation points and question marks to increase counter)
        if (text[n] == 33 || text[n] == 46 || text[n] == 63)
        {
            sentences++;
        }
        //Every other character inputted is not counted towards any counter variable
        else
        {
        }
    }

    //This is the grade level formula based on the Coleman-Liau Index, which prints out the estimated grade level needed to read and understand the inputted text
    double grade_level = (0.0588 * letters / words * 100) - (0.296 * sentences / words * 100) - 15.8;

    grade_level = round(grade_level);

    //If the grade level is less than one
    if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", grade_level);
    }
}