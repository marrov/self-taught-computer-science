#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser and a strength
typedef struct
{
    int winner;
    int loser;
}
pair;

pair pairs[MAX * (MAX - 1) / 2];

// Global count variables
int pair_count;
int candidate_count;

// Prototypes
void lock_pairs(void);
bool cycle(int src);
void print_locked(void);

int main (void)
{
    candidate_count = get_int("Number of candidates: ");

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = get_int("Number of pairs: ");

    for (int i = 0; i < pair_count; i++)
    {
        pairs[i].winner = get_int("Pair %i, winner: ", i + 1);
        pairs[i].loser  = get_int("Pair %i, loser : ", i + 1);
    }

    lock_pairs();
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Check if there will be a cycle (can't happen if i = 0)
        if (i == 0 || !cycle(i))
        {
            // lock pair
            locked[pairs[i].winner][pairs[i].loser] = 1;
            print_locked();
        }
    }
    return;
}

bool cycle(int src)
{
    return false;
}

// Prints out locked matrix for debugging purposes
void print_locked(void)
{
    printf("locked[i][j]:\n");
    int row, col;
    for (row = 0; row < candidate_count; row++)
    {
        for (col = 0; col < candidate_count; col++)
        {
            printf("%i     ", locked[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}
