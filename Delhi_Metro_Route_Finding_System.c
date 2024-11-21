#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define NUMBER_OF_STATIONS 40

// Structure for a Node
typedef struct Node {
    char name[50];
    int idx;
    struct Node** neighbours;
    int neighbourCount;
} Node;

Node* stations[NUMBER_OF_STATIONS];
char* stationsName[] = {
    "SHAHEED STHAL", "HINDON", "ARTHALA", "MOHAN NAGAR", "SHYAM PARK", "MAJOR MOHIT SHARMA", "RAJ BAGH",
    "SHAHEED NAGAR", "DILSHAD GARDEN", "JHILMIL", "MANSAROVAR PARK", "SHAHDARA", "WELCOME", "SEELAMPUR",
    "VAISHALI", "KAUSHAMBI", "ANAND VIHAR", "KARKARDUMA", "PREET VIHAR", "NIRMAN VIHAR", "LAXMI NAGAR",
    "YAMUNA BANK", "INDRAPRASTHA", "AKSHARDHAM", "MAYUR VIHAR-I", "MAYUR VIHAR EXTENSION", "NEW ASHOK NAGAR",
    "SHIV VIHAR", "JOHRI ENCLAVE", "GOKULPURI", "MAUJPUR", "JAFFRABAD", "EAST AZAD NAGAR", "KRISHNA NAGAR",
    "KARKARDUMA COURT", "IP EXTENSION", "MANDAWALI", "EAST VINOD NAGAR", "TRILOKPURI", "MAYUR VIHAR POCKET I"
};

int connections[40][5] = {
    {1}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}, {6, 8}, {7, 9}, {8, 10}, {9, 11}, {10, 12}, {11, 13, 31, 32}, {12},
    {15}, {14, 16}, {15, 17, 35}, {16, 18, 34}, {17, 19}, {18, 20}, {19, 21}, {20, 22, 23}, {21}, {21, 24}, {23, 25, 39},
    {24, 26}, {25}, {28}, {27, 29}, {28, 30}, {29, 31}, {30, 12}, {12, 33}, {32, 34}, {17, 33}, {16, 36}, {35, 37},
    {36, 38}, {37, 39}, {38, 24}
};
int connectionsCount[40] = {
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 2, 3, 3, 2, 2, 2, 3, 1, 2, 3, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

void buildMap() {
    for (int i = 0; i < NUMBER_OF_STATIONS; i++) {
        stations[i] = (Node*)malloc(sizeof(Node));
        strcpy(stations[i]->name, stationsName[i]);
        stations[i]->idx = i;
        stations[i]->neighbourCount = connectionsCount[i];
        stations[i]->neighbours = (Node**)malloc(connectionsCount[i] * sizeof(Node*));
    }

    for (int currStation = 0; currStation < NUMBER_OF_STATIONS; currStation++) {
        for (int ngbrs = 0; ngbrs < connectionsCount[currStation]; ngbrs++) {
            stations[currStation]->neighbours[ngbrs] = stations[connections[currStation][ngbrs]];
        }
    }
}

void findStationIndex(Node* curr, int visited[], int* idx, const char* station) {
    if (strcmp(curr->name, station) == 0) {
        *idx = curr->idx;
        return;
    }
    visited[curr->idx] = 1;
    for (int i = 0; i < curr->neighbourCount; i++) {
        if (!visited[curr->neighbours[i]->idx]) {
            findStationIndex(curr->neighbours[i], visited, idx, station);
        }
    }
}

void findPath(Node* curr, int visited[], char path[100][50], char shortestPath[100][50], const char* dest, int* currLen, int* shortestLen, int pathIndex) {
    strcpy(path[pathIndex], curr->name);

    if (strcmp(curr->name, dest) == 0) {
        if (*currLen > pathIndex + 1) {
            *currLen = pathIndex + 1;
            *shortestLen = *currLen;
            for (int i = 0; i < *currLen; i++) {
                strcpy(shortestPath[i], path[i]);
            }
        }
        return;
    }

    visited[curr->idx] = 1;

    for (int i = 0; i < curr->neighbourCount; i++) {
        if (!visited[curr->neighbours[i]->idx]) {
            findPath(curr->neighbours[i], visited, path, shortestPath, dest, currLen, shortestLen, pathIndex + 1);
        }
    }
    visited[curr->idx] = 0;
}

void printPath(char shortestPath[100][50], int pathLen) {
    printf("\n\nYour path is as follows:\n");
    int fare = 20 * (pathLen - 1);
    int distance = pathLen - 1;

    for (int i = 0; i < pathLen; i++) {
        printf("%s", shortestPath[i]);
        if (i != pathLen - 1) {
            printf(" ==> ");
        }
    }
    printf("\n\nYour Total Fare: %d\n", fare);
    printf("Your Total Distance: %dkm\n", distance);
}

void query(const char* source, const char* dest) {
    int sourceIdx = -1, destIdx = -1;
    int visitedSrc[NUMBER_OF_STATIONS] = {0};
    int visitedDest[NUMBER_OF_STATIONS] = {0};

    findStationIndex(stations[0], visitedSrc, &sourceIdx, source);
    findStationIndex(stations[0], visitedDest, &destIdx, dest);

    if (sourceIdx == -1 || destIdx == -1) {
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

void showHomeScreen() {
    printf("\n\t\t\t\tWELCOME TO METRO GUIDE\n\n");
    time_t now = time(NULL);
    printf("\t\t\t\t%s\n", ctime(&now));
}

int main() {
    buildMap();
    showHomeScreen();

    char flag;
    printf("\nSTART PROGRAM? [Y/N]: ");
    scanf(" %c", &flag);

    if (flag == 'n' || flag == 'N') {
        return 0;
    }

    while (1) {
        printf("\n#################### MENU ####################\n");
        printf("1. Show Station List.\n");
        printf("2. Find your way.\n");
        printf("3. Contact Us.\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                for (int i = 0; i < NUMBER_OF_STATIONS; i++) {
                    printf("%d. %s\n", i, stationsName[i]);
                }
                break;

            case 2: {
                char start[50], end[50];
                printf("\nEnter the starting station name: ");
                getchar(); // clear newline
                fgets(start, 50, stdin);
                start[strcspn(start, "\n")] = '\0'; // Remove newline character
                printf("\nEnter where you want to get off: ");
                fgets(end, 50, stdin);
                end[strcspn(end, "\n")] = '\0'; // Remove newline character
                for (int i = 0; start[i]; i++) start[i] = toupper(start[i]);
                for (int i = 0; end[i]; i++) end[i] = toupper(end[i]);
                query(start, end);
                break;
            }

            case 3:
                printf("\nContact us at: 9922102108@mail.jiit.ac.in\n");
                printf("\nContact us at: 9922102101@mail.jiit.ac.in\n");
                printf("\nContact us at: 9922102102@mail.jiit.ac.in\n");
                printf("\nTHANK YOU!\n");
                break;

            default:
                printf("Wrong input!\n");
                break;
        }

        char charChoice;
        printf("\nWould you like to continue? [Y/N]: ");
        scanf(" %c", &charChoice);
        if (charChoice != 'y' && charChoice != 'Y') {
            break;
        }
    }

    return 0;
}
