#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int difference(int index);
bool cycle(int start, int loser);

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    bool preferencesBool[MAX][MAX];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferencesBool[i][j] = false;
            preferencesBool[i][i] = true;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate = ranks[i];
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferencesBool[j][candidate] == false)
            {
                preferences[candidate][j]++;
                preferencesBool[candidate][j] = true;
            }
        }
    }

    // checking preferences[][]
    /* for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i  ", preferences[i][j]);
        }
        printf("\n");
    }
    printf("\n"); */

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    //checking pairs[]
    /* for (int i = 0; i < pair_count; i++)
    {
        printf("%i %i\n", pairs[i].winner, pairs[i].loser);
    } */
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        if (difference(i) < difference(i + 1))
        {
            // temporary pair to swap index in pairs[]
            pair temp;
            temp = pairs[i];

            pairs[i] = pairs[i + 1];
            pairs[i + 1] = temp;
            //testing difference, sort
            /* printf("difference(i) = %i difference(i+1) = %i\n", difference(i), difference(i + 1));
            for (int j = 0; j < pair_count; j++)
            {
                printf("%i %i\n", pairs[j].winner, pairs[j].loser);
            } */
        }
    }
    return;
}

int difference(int index)
{
    int difference;

    difference = preferences[pairs[index].winner][pairs[index].loser] - preferences[pairs[index].loser][pairs[index].winner];

    return difference;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}
bool cycle(int start, int loser)
{
    if (start == loser)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = true;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winner = false;
                break;
            }
        }
        if (winner)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
