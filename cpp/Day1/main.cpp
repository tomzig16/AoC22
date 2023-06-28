#include "../HelperFunctions.h"
#include <string>

#define FILE_PATH "/Users/tomaszi/dev/Other/AoC22/Day1/day1input.txt"

void InsertNewTopValue(uint value, uint* topThree, int nOfTop = 3){
    for(int i = 0; i < nOfTop; ++i){
        if(topThree[i] == 0){
            topThree[i] = value;
            return;
        }
    }
    
    for(int i = 0; i < nOfTop; ++i){
        if(topThree[i] < value){
            for(int j = nOfTop - 1; j > i; --j){
                topThree[j] = topThree[j-1];
            }
            topThree[i] = value;
            return;
        }
    }
}

int main(){
    std::vector<std::string> input = ReadStrings(FILE_PATH);
    
    // Part 1
    uint maxCarry = 0;
    uint currentCarry = 0;
    for(int i = 0; i < input.size(); ++i){
        if(input[i] == ""){
            if(currentCarry == 0)
                continue;
            else{
                if(maxCarry < currentCarry){
                    maxCarry = currentCarry;
                }
            }
            currentCarry = 0;
        }
        else{
            uint inputAsInt = StringToInt(input[i]);
            currentCarry += inputAsInt;
        }
    }
    PRINT(1, maxCarry);
    
    // Part 2
    uint topThree[3] = {0, 0, 0};
    currentCarry = 0;
    for(int i = 0; i < input.size(); ++i){
        if(input[i] == ""){
            if(currentCarry == 0)
                continue;
            else{
                InsertNewTopValue(currentCarry, topThree);
            }
            currentCarry = 0;
        }
        else{
            uint inputAsInt = StringToInt(input[i]);
            currentCarry += inputAsInt;
        }
    }
    PRINT(2, topThree[0] + topThree[1] + topThree[2]);
}
