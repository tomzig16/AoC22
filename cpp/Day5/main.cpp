#include "../HelperFunctions.h"
#include <string>
#include <regex>

#define FILE_PATH "/Users/tomaszi/dev/Other/AoC22/Day5/day5input.txt"
#define N_OF_STACKS 9

struct ContainerStack {
    int nOfElements = 0;
    std::vector<char> containers;

    char PopContainer() {
        char poppedContainer = ' ';
        if(nOfElements > 0) {
            poppedContainer = containers[nOfElements-1];
            nOfElements--;
        }
        else {
            // Should not happen?
        }
        return poppedContainer;
    }

    void PushContainer(char containerSymbol) {
        if(containers.size() < nOfElements + 1){
            containers.push_back(containerSymbol);
        }
        else{
            containers[nOfElements] = containerSymbol;
        }
        nOfElements++;
    }
};

ContainerStack* ReadContainers(std::vector<std::string>& inputs, int containerNumberLine){
    ContainerStack *resultStack = new ContainerStack[N_OF_STACKS];
    for(int i = containerNumberLine-1; i >= 0; i--){
        for(int containerN = 0; containerN < N_OF_STACKS; containerN++){
            int inputColumn = (containerN * 4) + 1; // we get container data every 4th symbol starting from 1st (number 0 based)
            if(inputs[i][inputColumn] != ' '){
                resultStack[containerN].PushContainer(inputs[i][inputColumn]);
            }
        }
    }
    return resultStack;
}

void DoActionWithContainers(int nToMove, int idFrom, int idTo, ContainerStack* containers){
    for(int i = 0; i < nToMove; ++i){
        char poppedContainer = containers[idFrom].PopContainer();
        containers[idTo].PushContainer(poppedContainer);
    }
}

void DoActionWithMultipleContainers(const int nToMove, int idFrom, int idTo, ContainerStack* containers){
    char poppedContainers[nToMove];
    for(int i = 0; i < nToMove; ++i){
        poppedContainers[i] = containers[idFrom].PopContainer();
    }
    for(int i = nToMove - 1; i >= 0; --i){
        containers[idTo].PushContainer(poppedContainers[i]);
    }

}

void Part1(std::vector<std::string>& input)
{
    ContainerStack *containers;
    std::regex r("(\\d+)");

    bool startingContainersWereRead = false;
    for(int i = 0; i < input.size(); i++) {
        if(!startingContainersWereRead){
            if(input[i][0] == ' ' && input[i][1] == '1'){
                containers = ReadContainers(input, i);
                startingContainersWereRead = true;
                i++; // empty line
            }
        }
        else {
            auto words_begin = std::sregex_iterator(input[i].begin(), input[i].end(), r);
            auto words_end = std::sregex_iterator();

            std::smatch match = *words_begin;
            std::string match_str = match.str();
            int numberToMove = StringToInt(match_str);

            match = *(++words_begin);
            match_str = match.str();
            int fromIndex = StringToInt(match_str) - 1;

            match = *(++words_begin);
            match_str = match.str();
            int toIndex = StringToInt(match_str) - 1;
            
            DoActionWithContainers(numberToMove, fromIndex, toIndex, containers);
        }
    }

    std::string finalResult = "";
    for(int i = 0; i < N_OF_STACKS; ++i){
        finalResult += containers[i].PopContainer();
    }
    PRINT(1, finalResult);
}

void Part2(std::vector<std::string>& input) {
    ContainerStack *containers;
    std::regex r("(\\d+)");

    bool startingContainersWereRead = false;
    for(int i = 0; i < input.size(); i++) {
        if(!startingContainersWereRead){
            if(input[i][0] == ' ' && input[i][1] == '1'){
                containers = ReadContainers(input, i);
                startingContainersWereRead = true;
                i++; // empty line
            }
        }
        else {
            auto words_begin = std::sregex_iterator(input[i].begin(), input[i].end(), r);
            auto words_end = std::sregex_iterator();

            std::smatch match = *words_begin;
            std::string match_str = match.str();
            int numberToMove = StringToInt(match_str);

            match = *(++words_begin);
            match_str = match.str();
            int fromIndex = StringToInt(match_str) - 1;

            match = *(++words_begin);
            match_str = match.str();
            int toIndex = StringToInt(match_str) - 1;
            
            DoActionWithMultipleContainers(numberToMove, fromIndex, toIndex, containers);
        }
    }

    std::string finalResult = "";
    for(int i = 0; i < N_OF_STACKS; ++i){
        finalResult += containers[i].PopContainer();
    }
    PRINT(2, finalResult);
}


int main() {
    std::vector<std::string> input = ReadStrings(FILE_PATH);
    Part1(input);
    Part2(input);

}