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

//Inititalization of variables and arrays
int pair_count;
int candidate_count;
int usage[MAX];
int winner_votes[MAX * (MAX - 1) / 2];
int loser_votes[MAX * (MAX - 1) / 2];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
        
        // Used later for the vote function
        for (int u = 0; u < candidate_count; u++)
        {
            usage[u] = 0;
        }
        
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
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(name, candidates[a]) == 0)
        {
            ranks[rank] = a;
            usage[a]++;
            if (usage[a] > 1)
            {
                return false;
            }
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int b = 0; b < candidate_count; b++)
    {
        for (int c = b + 1; c < candidate_count; c++)
        {
            if (b < c)
            {
                preferences[ranks[b]][ranks[c]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int e = 0; e < candidate_count; e++)
    {
        for (int f = e + 1; f < candidate_count; f++)
        {
            if (preferences[e][f] > preferences[f][e])
            {
                pairs[pair_count].winner = e;
                winner_votes[pair_count] = preferences[e][f];
                pairs[pair_count].loser = f;
                loser_votes[pair_count] = preferences[f][e];
                pair_count++;
            }
            else if (preferences[e][f] < preferences[f][e])
            {
                pairs[pair_count].winner = f;
                winner_votes[pair_count] = preferences[f][e];
                pairs[pair_count].loser = e;
                loser_votes[pair_count] = preferences[e][f];
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int h = 0; h < pair_count; h++)
    {
        for (int i = h + 1; i < pair_count; i++)
        {
            if (winner_votes[h] < winner_votes[i])
            {
                int j = pairs[h].winner;
                pairs[h].winner = pairs[i].winner;
                pairs[i].winner = j;
                
                int k = pairs[h].loser;
                pairs[h].loser = pairs[i].loser;
                pairs[i].loser = k;
                
                int x = winner_votes[h];
                winner_votes[h] = winner_votes[i];
                winner_votes[i] = x;
                
                int y = loser_votes[h];
                loser_votes[h] = loser_votes[i];
                loser_votes[i] = y;
            }
        }
    }
    return;
}

//Checks to see if there is a cycle by checking if the edges of the graph are used more than once
bool check_cycle_help(int index, bool visited[])
{
    if (visited[index])
    {
        return true;
    }
    visited[index] = true;
    for (int n = 0; n < candidate_count; n++)
    {
        if (locked[index][n] && check_cycle_help(n, visited))
        {
            return true;
        }
    }
    return false;
}

//First sets all the elements in the visited array to false and then refers to the helper to see if there is a cycle
bool check_cycle(int start)
{
    bool visited[candidate_count];
    for (int l = 0; l < candidate_count; l++)
    {
        visited[l] = false;
    }
    return check_cycle_help(start, visited);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int m = 0; m < pair_count; m++)
    {
        locked[pairs[m].winner][pairs[m].loser] = true;
        if (check_cycle(m))
        {
            locked[pairs[m].winner][pairs[m].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int counter[candidate_count];
    
    //Establishes the value of 0 for each element of the array
    for (int q = 0; q < candidate_count; q++)
    {
        counter[q] = 0;
    }
    
    //Adds one to the elements of the array in which the candidate p is locked in under o
    for (int o = 0; o < candidate_count; o++)
    {
        for (int p = 0; p < candidate_count; p++)
        {
            if (locked[o][p] == true)
            {
                counter[p]++;
            }
        }
    }
    
    //Prints out the candidates that are the sources of the graph
    for (int r = 0; r < candidate_count; r++)
    {
        if (counter[r] == 0)
        {
            printf("%s\n", candidates[r]);
        }
    }
    return;
}