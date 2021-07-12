#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser and a strength
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

// Auxiliary array for merge sort
pair p_aux[MAX * (MAX - 1) / 2];

// Global count variables
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// My own function prototypes
void merge_sort(int fst, int lst);
void merge(int fst, int mid, int lst);

// Debugging function prototypes
void print_preferences(void);
void print_locked(void);
void print_pairs_info(pair pairs_arr[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    print_preferences();
    add_pairs();
    print_pairs_info(pairs);
    sort_pairs();
    print_pairs_info(pairs);
    lock_pairs();

    /*
    print_winner();
    */

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Check if candidate has already been voted for
            if (rank != 0)
            {
                for (int j = 0; j < rank; j++)
                {
                    if (strcmp(name, candidates[ranks[j]]) == 0)
                    {
                        return false;
                    }
                }
            }
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Use the ranked structure of ranks[] to loop through
    // all candiates, for all other candidates which are not
    // themselves nor have been chosen previously
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Traverse only lower part of the preferences array (excluding diagonal)
    for (int i = 1; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            // If there is a tie in preferences between two candidates
            // do not generate a pair as there is no winner or loser
            if (preferences[i][j] != preferences[j][i])
            {
                // Update winner and loser in pair
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser  = j;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser  = i;
                }

                // Update the global the pair count
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Initialize auxiliary pairs array
    for (int i = 0; i < pair_count; i++)
    {
        p_aux[i] = pairs[i];
    }

    // Sort pairs array with merge sort
    merge_sort(0, pair_count);

    return;
}

void merge_sort(int fst, int lst)
{
    // Check if array has only one element
    if (fst == lst)
    {
        return;
    }

    // Calculate midpoint of the array
    int mid = (lst + fst + 1) / 2;

    // Sort left half, then sort right half
    merge_sort(fst, mid - 1);
    merge_sort(mid, lst);

    // Merge both halves
    merge(fst, mid, lst);

    return;
}

void merge(int fst, int mid, int lst)
{
    // Initialize two indexes, one for each half (left and right)
    int idx_l = 0, idx_r = 0;

    // Set the auxiliary array size equal to combined sizes of left and right
    int n_aux = lst - fst + 1;

    // Loop for merging both halves into the auxiliary array
    for (int i = 0; i <= n_aux; i++)
    {
        // Check if out of bounds
        if (fst + idx_l > mid - 1)
        {
            // If out of bounds in left, copy all remaining items in right
            for (int j = mid + idx_r; j <= lst; j++)
            {
                p_aux[i + (j - (mid + idx_r))] = pairs[j];
            }
            break;
        }
        else if (mid + idx_r > lst)
        {
            // If out of bounds in right, copy all remaining items in left
            for (int j = fst + idx_l; j <= mid - 1; j++)
            {
                p_aux[i + (j - (fst + idx_l))] = pairs[j];
            }
            break;
        }

        // Define strength for left and right halves
        int str_l = preferences[pairs[fst + idx_l].winner][pairs[fst + idx_l].loser];
        int str_r = preferences[pairs[mid + idx_r].winner][pairs[mid + idx_r].loser];

        // Compare strength in first item in left with strength with first item in right and copy the highest
        if (str_l >= str_r)
        {
            p_aux[i] = pairs[fst + idx_l];
            idx_l++;
        }
        else
        {
            p_aux[i] = pairs[mid + idx_r];
            idx_r++;
        }
    }

    // Update the original array with the contents of the auxiliary array
    for (int i = 0; i < n_aux; i++)
    {
        pairs[fst + i] = p_aux[i];
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool cycle = 0;
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle)
        {
            // lock pair
            locked[pairs[i].winner][pairs[i].loser] = 1;
            print_locked();
        }
        else
        {
            break;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

// Prints out preferences matrix for debugging purposes
void print_preferences(void)
{
    printf("preferences[i][j]:\n");
    int row, col;
    for (row = 0; row < candidate_count; row++)
    {
        for (col = 0; col < candidate_count; col++)
        {
            printf("%i     ", preferences[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    return;
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

// Prints out info about pairs for debugging purposes
void print_pairs_info(pair pairs_arr[])
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair number %i, ", i);
        printf("Winner: %s, Loser: %s", candidates[pairs_arr[i].winner], candidates[pairs_arr[i].loser]);
        printf(", by %i ", preferences[pairs_arr[i].winner][pairs_arr[i].loser]);
        printf("to %i \n", preferences[pairs_arr[i].loser][pairs_arr[i].winner]);
    }
    printf("\n");
    return;
}