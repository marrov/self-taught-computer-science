#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int compute_cli(int n_letters, int n_words, int n_sentences);

int main(void)
{
    // Prompt user for text string
    string text = get_string("Text: ");

    // Get number of letters, words, and sentences in text string
    // Note: this could be done with one function but requires passing
    // array with pointers and that will be covered in week 4
    int n_letters   = count_letters(text);
    int n_words     = count_words(text);
    int n_sentences = count_sentences(text);

    // Calculate the Coleman-Liau index
    int cli = compute_cli(n_letters, n_words, n_sentences);

    // Print out the grade level based on the CL index
    if (cli < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cli > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", cli);
    }
}

// Obtain number of letters in the string
int count_letters(string text)
{
    int n_letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            n_letters++;
        }
    }

    return n_letters;
}

// Obtain number of words in the string
int count_words(string text)
{
    int n_spaces = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isblank(text[i]) == 1)
        {
            n_spaces++;
        }
    }

    int n_words = n_spaces + 1;

    return n_words;
}

// Obtain number of letters in the string
int count_sentences(string text)
{
    int n_punct = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            n_punct++;
        }
    }

    int n_sentences = n_punct;

    return n_sentences;
}

// Calculate the Coleman-Liau index
int compute_cli(int n_letters, int n_words, int n_sentences)
{
    // Calculate L average number of letters per 100 words
    float l = 100. * n_letters / n_words;

    // Calculate S average number of letters per 100 words
    float s = 100. * n_sentences / n_words;

    // Compute formula
    int cli = round(0.0588 * l - 0.296 * s - 15.8);

    return cli;
}
