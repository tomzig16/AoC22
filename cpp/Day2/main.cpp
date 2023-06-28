#include "../HelperFunctions.h"
#include <string>

#define FILE_PATH "/Users/tomaszi/dev/Other/AoC22/Day2/day2input.txt"

#define POINTS_FOR_X 1 // Rock
#define POINTS_FOR_Y 2 // Paper
#define POINTS_FOR_Z 3 // Scissors

#define POINTS_FOR_LOSING 0
#define POINTS_FOR_WINNING 6
#define POINTS_FOR_DRAW 3

int GetPointsForLetter(char letter){
    if(letter == 'X') return POINTS_FOR_X; // Rock
    if(letter == 'Y') return POINTS_FOR_Y; // Paper
    if(letter == 'Z') return POINTS_FOR_Z; // Scissors
    return 0;
}

int GetPointsForResult(char opponentInput, char myInput){
    if(opponentInput == 'A'){
        if(myInput == 'X') return POINTS_FOR_DRAW;
        if(myInput == 'Y') return POINTS_FOR_WINNING;
        if(myInput == 'Z') return POINTS_FOR_LOSING;
    }
    if(opponentInput == 'B'){
        if(myInput == 'X') return POINTS_FOR_LOSING;
        if(myInput == 'Y') return POINTS_FOR_DRAW;
        if(myInput == 'Z') return POINTS_FOR_WINNING;
    }
    if(opponentInput == 'C'){
        if(myInput == 'X') return POINTS_FOR_WINNING;
        if(myInput == 'Y') return POINTS_FOR_LOSING;
        if(myInput == 'Z') return POINTS_FOR_DRAW;
    }
    return 0;
}

// Part 2
int GetTotalPointsForWin(char opponentInput, char wantedOutcome){
    // X - need to lose
    // Y - need to draw
    // Z - need to win

    int totalPoints = 0;
    if(wantedOutcome == 'X'){
        totalPoints = POINTS_FOR_LOSING;
        if(opponentInput == 'A') return POINTS_FOR_Z + totalPoints;
        if(opponentInput == 'B') return POINTS_FOR_X + totalPoints;
        if(opponentInput == 'C') return POINTS_FOR_Y + totalPoints;
    }
    if(wantedOutcome == 'Y'){
        totalPoints = POINTS_FOR_DRAW;
        if(opponentInput == 'A') return POINTS_FOR_X + totalPoints;
        if(opponentInput == 'B') return POINTS_FOR_Y + totalPoints;
        if(opponentInput == 'C') return POINTS_FOR_Z + totalPoints;
    }
    if(wantedOutcome == 'Z'){
        totalPoints = POINTS_FOR_WINNING;
        if(opponentInput == 'A') return POINTS_FOR_Y + totalPoints;
        if(opponentInput == 'B') return POINTS_FOR_Z + totalPoints;
        if(opponentInput == 'C') return POINTS_FOR_X + totalPoints;
    }
    return 0;
}

int main() {
    std::vector<std::string> input = ReadStrings(FILE_PATH);

    int totalPoints = 0;
    for(int i = 0; i < input.size(); ++i){
        totalPoints += GetPointsForLetter(input[i][2]) + GetPointsForResult(input[i][0], input[i][2]);
    }
    PRINT(1, totalPoints);

    totalPoints = 0;
    for(int i = 0; i < input.size(); ++i){
        totalPoints += GetTotalPointsForWin(input[i][0], input[i][2]);
    }
    PRINT(2, totalPoints);

}
