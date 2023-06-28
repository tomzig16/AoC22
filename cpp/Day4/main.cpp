#include "../HelperFunctions.h"
#include <string>

#define FILE_PATH "/Users/tomaszi/dev/Other/AoC22/Day4/day4input.txt"

struct Range {
    int lowerBracket;
    int higherBracket;
};

Range GetRangeBasedOnSegment(std::string segment) {
    Range result;
    int dashPos = segment.find('-');
    result.lowerBracket = StringToInt(segment.substr(0, dashPos));
    result.higherBracket = StringToInt(segment.substr(dashPos + 1, segment.size() - dashPos - 1));
    return result;
}

int main() {
    std::vector<std::string> inputs = ReadStrings(FILE_PATH);

    int result = 0;
    for(int i = 0; i < inputs.size(); ++i) {
        int commaIndex = inputs[i].find(',');
        std::string firstRangeAsStrings = inputs[i].substr(0, commaIndex);
        std::string secondRangeAsStrings = inputs[i].substr(commaIndex + 1, inputs[i].size() - commaIndex - 1);
        Range firstRange, secondRange;
        firstRange = GetRangeBasedOnSegment(firstRangeAsStrings);
        secondRange = GetRangeBasedOnSegment(secondRangeAsStrings);

        if(firstRange.lowerBracket >= secondRange.lowerBracket && 
            firstRange.higherBracket <= secondRange.higherBracket){
                result++;
        }
        else if(secondRange.lowerBracket >= firstRange.lowerBracket && 
            secondRange.higherBracket <= firstRange.higherBracket){
                result++;
        }
    }
    PRINT(1, result);

    result = 0;
    for(int i = 0; i < inputs.size(); ++i) {
        int commaIndex = inputs[i].find(',');
        std::string firstRangeAsStrings = inputs[i].substr(0, commaIndex);
        std::string secondRangeAsStrings = inputs[i].substr(commaIndex + 1, inputs[i].size() - commaIndex - 1);
        Range firstRange, secondRange;
        firstRange = GetRangeBasedOnSegment(firstRangeAsStrings);
        secondRange = GetRangeBasedOnSegment(secondRangeAsStrings);

        if(firstRange.lowerBracket >= secondRange.lowerBracket && 
            firstRange.lowerBracket <= secondRange.higherBracket){
                result++;
        }
        else if(secondRange.lowerBracket >= firstRange.lowerBracket && 
            secondRange.lowerBracket <= firstRange.higherBracket){
                result++;
        }
        else if(firstRange.higherBracket >= secondRange.lowerBracket && 
            firstRange.higherBracket <= secondRange.higherBracket){
                result++;
        }
        else if(secondRange.higherBracket >= firstRange.lowerBracket && 
            secondRange.higherBracket <= firstRange.higherBracket){
                result++;
        }
    }

    PRINT(2, result);
}