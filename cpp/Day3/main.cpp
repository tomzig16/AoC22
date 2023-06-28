#include "../HelperFunctions.h"
#include <string>

#define FILE_PATH "/Users/tomaszi/dev/Other/AoC22/Day3/day3input.txt"

int ConvertLetterToPoints(char letter) {
    int asciiOfLetter = letter;
    if(asciiOfLetter > 'a') { // 'a' is 97
        return (asciiOfLetter - 'a') + 1;
    }
    else { // Capitals (starts from 65)
        return (asciiOfLetter - 'A') + 27;
    }
}

int main() {
    std::vector<std::string> input = ReadStrings(FILE_PATH);
    
    long totalSum = 0;
    for(std::string l : input){
        int middle = l.size() / 2;
        for(int i = 0; i < middle; ++i){
            int duplicatePos = l.find(l[i], middle);
            if(duplicatePos >= 0){
                totalSum += ConvertLetterToPoints(l[duplicatePos]);
                break;
            }
        }
    }
    PRINT(1, totalSum);

    totalSum = 0;
    for(int i = 2; i < input.size(); i+=3){
        // std::string* smallestLine = &(input[i-2]);
        int smallestIndex = i-2;
        for(int j = i-1; j <= i; j++){
            // if(input[j].size() < smallestLine->size()){
            //     smallestLine = &(input[j]);
            // }
            if(input[smallestIndex].size() > input[j].size()){
                smallestIndex = j;
            }
        }

        for(int letter = 0; letter < input[smallestIndex].size(); letter++){
            bool numberExistsInAll = true;
            for(int k = i-2; k <= i; k++){
                if(smallestIndex == k) continue;
                if(input[k].find(input[smallestIndex][letter]) == -1){
                    numberExistsInAll = false;
                    break;
                }
            }
            if(numberExistsInAll){
                totalSum += ConvertLetterToPoints(input[smallestIndex][letter]);
                break;
            }
        }
    }
    PRINT(2, totalSum);
}