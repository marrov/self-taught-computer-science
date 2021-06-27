#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void sort_candidates_by_votes(void);
void swap_candidate_position(int index_i, int index_j);
void print_candidates(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Update that candidate’s vote total
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
            break;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Sort candidates by votes, with the one with most votes first
    sort_candidates_by_votes();

    // As the array of candidates is ordered, first is always (at least)
    // one of the winners
    printf("%s\n", candidates[0].name);

    // Check (and print) if there are any more winners, so start at 1 not 0
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes == candidates[0].votes)
        {
            printf("%s\n", candidates[i].name);
        }
        else
        {
            // Exit the loop if there are no more winners
            break;
        }
    }
}

// Initially I will implement selection sort
void sort_candidates_by_votes(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int max = 0, index_max = i;
        for (int j = i; j < candidate_count; j++)
        {
            if (candidates[j].votes > max)
            {
                // Update current max and index of max
                max = candidates[j].votes;
                index_max = j;
            }
        }

        // Swap highest value with first element of unsorted part, if different
        if (i != index_max)
        {
            swap_candidate_position(i, index_max);
        }
    }
}

// Swap the ith candidate with the jth candidate
void swap_candidate_position(int index_i, int index_j)
{
    candidate temp;

    temp                = candidates[index_i];
    candidates[index_i] = candidates[index_j];
    candidates[index_j] = temp;
}

// Debugging tool to access (global variable) candidates
void print_candidates(void)
{
    printf("\n");
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%s has ", candidates[i].name);
        printf("%i votes\n", candidates[i].votes);

    }
}