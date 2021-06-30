#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <cs50.h>

// Prototypes
bool check_key(string key);

// Constants
const int KEYLEN = 26;

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // If two cli-args (run-command + key) given, check if the last one (i.e. the key) is invalid
        bool isvalid = check_key(argv[argc - 1]);

        if (!isvalid)
        {
            printf("Invalid key! The key should contain 26 unique alphabetic characters.\n");
            return 1;
        }
    }
    else
    {
        // If other than two cli-args, display correct usage and return err code (1)
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Prompt user for plaintext string
    string plaintext = get_string("plaintext:  ");

    // Initialize difference array and key (from cli-arg)
    int diff[KEYLEN];
    string key = argv[argc - 1];

    // Calculate array with differences between key and upper-case alphabet
    for (int i = 0; i < KEYLEN; i++)
    {
        diff[i] = toupper(key[i]) - ('A' + i);
    }

    // Initialize ciphertext as character array
    int len_plaintext = strlen(plaintext);
    char ciphertext[len_plaintext];

    // Apply difference to plaintext to encript plaintext into ciphertext
    for (int i = 0; i < len_plaintext; i++)
    {
        if (isalpha(plaintext[i]) != 0)
        {
            ciphertext[i] = plaintext[i] + diff[toupper(plaintext[i]) - 'A'];
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }

    }

    // Print out ciphertext as indivisual characters (because had check50 errors if print as string)
    printf("ciphertext: ");

    for (int i = 0; i < len_plaintext; i++)
    {
        printf("%c", ciphertext[i]);
    }

    printf("\n");

    return 0;
}

bool check_key(string key)
{
    bool isvalid;

    // Does the key have KEYLEN elemets?
    if (strlen(key) == KEYLEN)
    {
        // Start assuming 26 char key is valid and invalidate if
        // it does not meet the conditions
        isvalid = 1;

        for (int i = 0; i < KEYLEN; i++)
        {
            // Does the key have only letters?
            if (isalpha(key[i]) == 0)
            {
                isvalid = 0;
                break;
            }

            // Does the key have no repeating elemets?
            int counter = 0;

            for (int j = 0; j < KEYLEN; j++)
            {
                if (toupper(key[j]) == 'A' + i)
                {
                    counter++;
                }
            }

            if (counter != 1)
            {
                isvalid = 0;
                break;
            }
        }
    }
    else
    {
        isvalid = 0;
    }

    return isvalid;
}

