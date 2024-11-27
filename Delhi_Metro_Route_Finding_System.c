#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define NUMBER_OF_STATIONS 85

typedef struct Node
{
    char name[50];
    int idx;
    struct Node **neighbours;
    int neighbourCount;
} Node;

Node *stations[NUMBER_OF_STATIONS];
char *stationsName[] = {
    // Blue line
    "DWARKA SECTOR 21",
    "DWARKA",
    "DWARKA MOR",
    "NAWADA",
    "UTTAM NAGAR WEST",
    "UTTAM NAGAR EAST",
    "JANAKPURI WEST",
    "JANAKPURI EAST",
    "TILAK NAGAR",
    "SUBHASH NAGAR",
    "TAGORE GARDEN",
    "RAJOURI GARDEN",
    "RAMESH NAGAR",
    "MOTI NAGAR",
    "KIRTI NAGAR",
    "SHADIPUR",
    "PATEL NAGAR",
    "RAJENDRA PLACE",
    "KAROL BAGH",
    "JHANDEWALAN",
    "RK ASHRAM MARG",
    // line connection
    "RAJIV CHOWK",
    "BARAKHAMBA ROAD",
    "PRAGATI MAIDAN",
    "INDRAPRASTHA",
    // line divided
    "YAMUNA BANK",
    "AKSHARDHAM",
    "MAYUR VIHAR 1",
    "MAYUR VIHAR EXTENTION",
    "NEW ASHOK NAGAR",
    "NOIDA SECTOR 15",
    "NOIDA SECTOR 16",
    "NOIDA SECTOR 18",
    "BOTANICAL GARDEN",
    "GOLF COURSE",
    "NOIDA CITY CENTER",
    "NOIDA SECTOR 34",
    "NOIDA SECTOR 52",
    "NOIDA SECTOR 61",
    "NOIDA SECTOR 59",
    "NOIDA SECTOR 62",
    "NOIDA ELECTRONIC CITY",
    "LAXMI NAGAR",
    "NIRMAN VIHAR",
    "PREET VIHAR",
    "KARKARDUMA",
    "ANAND VIHAR ISBT",
    "KAUSHAMBI",
    // Yellow line
    "SAMAYPUR BADLI",
    "ROHINI SECTOR 18",
    "HAIDERPUR BADLI MOR",
    "JAHANGIR PURI",
    "ADARDH NAGAR",
    "AZADPUR",
    "MODEL TOWN",
    "G.T.B. NAGAR",
    "VISHWAVIDYALAYA",
    "VIDHAN SABHA",
    "CIVIL LINE",
    "KAHMERE GATE",
    "CHANDNI CHOWK",
    "CHAWRI BAZAR",
    "NEW DELHI",
    // line connection
    "RAJIV CHOWK",
    "PATEL CHOWK",
    "CENTRAL SECRETARIAT",
    "UDYOG BHAWAN",
    "LOK KALYAN MARG",
    "JOR BAGH",
    "DILLI HAAT - INA",
    "AIIMS",
    "GREEN PARK",
    "HAUZ KHAS",
    "MALVIYA NAGAR",
    "SAKET",
    "QUTUB MINAR",
    "CHHATARPUR",
    "SULTANPUR",
    "GHITORNI",
    "ARJANGARH",
    "GURU DRONACHARYA",
    "SIKANDERPUR",
    "M G ROAD",
    "IFFCO CHOWK",
    "HUDA CITY CENTER",
};

int connections[150][6] = {
    // Blue line
    {1},
    {0, 2},
    {1, 3},
    {2, 4},
    {3, 5},
    {4, 6},
    {5, 7},
    {6, 8},
    {7, 9},
    {8, 10},
    {9, 11},
    {10, 12},
    {11, 13},
    {12, 14},
    {13, 15},
    {14, 16},
    {15, 17},
    {16, 18},
    {17, 19},
    {18, 20},
    {19, 21},
    // RAJIV CHOWK
    {20, 22, 62, 64},
    {21, 23},
    {22, 24},
    {23, 25},
    // YAMUNA BANK
    {24, 26, 42},
    {25, 27},
    {26, 28},
    {27, 29},
    {28, 30},
    {29, 31},
    {30, 32},
    {31, 33},
    {32, 34},
    {33, 35},
    {34, 36},
    {35, 37},
    {36, 38},
    {37, 39},
    {38, 40},
    {39, 41},
    // NOIDA ELECTRONIC CITY
    {40},
    {25, 43},
    {42, 44},
    {43, 45},
    {44, 46},
    {45, 47},
    {46},
    // YELLOW LINE
    {47},
    {48, 50},
    {49, 51},
    {50, 52},
    {51, 53},
    {52, 54},
    {53, 55},
    {54, 56},
    {55, 57},
    {56, 58},
    {57, 59},
    {58, 60},
    {59, 61},
    {60, 62},
    // RAJIV CHOWK
    {61, 63, 20, 22},
    {62, 64},
    {63, 65},
    {64, 66},
    {65, 67},
    {66, 68},
    {67, 69},
    {68, 70},
    {69, 71},
    {70, 72},
    {71, 73},
    {72, 74},
    {73, 75},
    {74, 76},
    {75, 77},
    {76, 78},
    {77, 79},
    {78, 80},
    {79, 81},
    {80, 82},
    {81, 83},
    {82, 84},
    {83}

};

int connectionsCount[150] = {
    // BLUE
    1, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 4, 2, 2, 2,
    3, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 4, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 2,
    2, 2, 2, 2, 1};

void buildMap()
{

    for (int i = 0; i < NUMBER_OF_STATIONS; i++)
    {

        stations[i] = (Node *)malloc(sizeof(Node));
        strcpy(stations[i]->name, stationsName[i]);
        stations[i]->idx = i;
        stations[i]->neighbourCount = connectionsCount[i];
        stations[i]->neighbours = (Node **)malloc(connectionsCount[i] * sizeof(Node));
    }

    for (int currStation = 0; currStation < NUMBER_OF_STATIONS; currStation++)
    {
        for (int ngbrs = 0; ngbrs < connectionsCount[currStation]; ngbrs++)
        {
            stations[currStation]->neighbours[ngbrs] = stations[connections[currStation][ngbrs]];
        }
    }
}

void findStationIndex(Node *curr, int visited[], int *idx, const char *station)
{

    if (strcmp(curr->name, station) == 0)
    {

        *idx = curr->idx;
        return;
    }
    visited[curr->idx] = 1;

    for (int i = 0; i < curr->neighbourCount; i++)
    {

        if (!visited[curr->neighbours[i]->idx])
        {

            findStationIndex(curr->neighbours[i], visited, idx, station);
        }
    }
}

void findPath(Node *curr, int visited[], char path[100][50], char shortestPath[100][50], const char *dest, int *currLen, int *shortestLen, int pathIndex)
{

    strcpy(path[pathIndex], curr->name);

    if (strcmp(curr->name, dest) == 0)
    {

        if (*currLen > pathIndex + 1)
        {

            *currLen = pathIndex + 1;
            *shortestLen = *currLen;
            for (int i = 0; i < *currLen; i++)
            {

                strcpy(shortestPath[i], path[i]);
            }
        }
        return;
    }

    visited[curr->idx] = 1;

    for (int i = 0; i < curr->neighbourCount; i++)
    {

        if (!visited[curr->neighbours[i]->idx])
        {

            findPath(curr->neighbours[i], visited, path, shortestPath, dest, currLen, shortestLen, pathIndex + 1);
        }
    }

    visited[curr->idx] = 0;
}

void printPath(char shortestPath[100][50], int pathLen)
{
    printf("\n\nYour path is as follows:\n");
    int distance = pathLen - 1;
    int fare = 0;
    if (distance <= 2)
    {

        fare = 10;
    }
    else if (distance <= 5)
    {

        fare = 15;
    }
    else if (distance <= 10)
    {

        fare = 20;
    }
    else if (distance <= 15)
    {

        fare = 25;
    }
    else
    {

        fare = 30;
    }

    // Print the path

    for (int i = 0; i < pathLen; i++)
    {

        printf("%s", shortestPath[i]);

        if (i != pathLen - 1)
        {

            printf(" ==> ");
        }
    }

    printf("\n\nYour Total Fare: $ %d\n", fare);
    printf("Your Total Distance: %d km\n", distance);
}

void query(const char *source, const char *dest)
{

    int sourceIdx = -1, destIdx = -1;
    int visitedSrc[NUMBER_OF_STATIONS] = {0};
    int visitedDest[NUMBER_OF_STATIONS] = {0};

    findStationIndex(stations[0], visitedSrc, &sourceIdx, source);
    findStationIndex(stations[0], visitedDest, &destIdx, dest);

    if (sourceIdx == -1 || destIdx == -1)
    {

        printf("\nIncorrect Source Station or Destination Station\n");
        return;
    }

    int visitedPath[NUMBER_OF_STATIONS] = {0};
    char path[100][50];
    char shortestPath[100][50];
    int currLen = 500;
    int shortestLen = 0;

    findPath(stations[sourceIdx], visitedPath, path, shortestPath, dest, &currLen, &shortestLen, 0);
    printPath(shortestPath, shortestLen);
}

void showHomeScreen()
{

    printf("\n\t\t\t\tWELCOME TO METRO GUIDE\n\n");
    time_t now = time(NULL);
    printf("\t\t\t\t%s\n", ctime(&now));
}

int main()
{

    buildMap();
    showHomeScreen();

    char flag;
    printf("\nSTART PROGRAM? [Y/N]: ");
    scanf(" %c", &flag);

    if (flag == 'n' || flag == 'N')
    {

        return 0;
    }

    while (1)
    {

        printf("\n#################### MENU ####################\n");
        printf("1. Show Station List.\n");
        printf("2. Find your way.\n");
        printf("3. Contact Us.\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
        {

            for (int i = 0; i < NUMBER_OF_STATIONS; i++)
            {

                printf("%d. %s\n", i + 1, stationsName[i]);
            }
            break;
        }

        case 2:
        {

            char start[50], end[50];
            printf("\nEnter the starting station name: ");
            getchar();
            fgets(start, 50, stdin);

            start[strcspn(start, "\n")] = '\0';
            printf("\nEnter where you want to get off: ");
            fgets(end, 50, stdin);

            end[strcspn(end, "\n")] = '\0';

            for (int i = 0; start[i]; i++)
            {

                start[i] = toupper(start[i]);
            }

            for (int i = 0; end[i]; i++)
            {

                end[i] = toupper(end[i]);
            }

            query(start, end);
            break;
        }

        case 3:
        {

            printf("\nContact us at: 9922102108@mail.jiit.ac.in\n");
            printf("\nContact us at: 9922102101@mail.jiit.ac.in\n");
            printf("\nContact us at: 9922102102@mail.jiit.ac.in\n");
            printf("\nTHANK YOU!\n");
            break;
        }

        default:
        {

            printf("Wrong input!\n");
            break;
        }
        }

        char charChoice;
        printf("\nWould you like to continue? [Y/N]: ");
        scanf(" %c", &charChoice);

        if (charChoice != 'y' && charChoice != 'Y')
        {

            break;
        }
    }

    return 0;
}
