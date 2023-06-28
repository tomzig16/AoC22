#include "HelperFunctions.h"
#include <string>

#define FILE_PATH "/Users/tomaszi/dev/Other/AoC22/Day7/day7input.txt"

struct File {
    std::string name;
    int size;
};

struct Folder {
    std::string name;
    std::vector<File*> files;
    std::vector<Folder*> folders;
    Folder* parent = nullptr;
    long long totalSize = 0;

    Folder* GetFolderWithName(std::string nameToFind) {
        for(Folder* f : folders) {
            if(f->name == nameToFind){
                return f;
            }
        }
        return nullptr;
    }
    
    File* GetFileWithName(std::string nameToFind) {
        for(File* f : files) {
            if(f->name == nameToFind){
                return f;
            }
        }
        return nullptr;
    }
    
    void UpdateFolderTotalSizes(int sizeToAdd) {
        totalSize += sizeToAdd;
        if(parent != nullptr)
            parent->UpdateFolderTotalSizes(sizeToAdd);
    }

    void CreateNewFolder(std::string folderName){
        if(GetFolderWithName(folderName) == nullptr) {
            // Create only new folders, with unique name
            Folder* f = new Folder();
            f->name = folderName;
            f->parent = this;
            folders.push_back(f);
        }
        else {
            // std::cout << lineNumber << " - Folder with the same name of " << lineTokens[1] << " already exists inside " << currentlyOpenFolder->name << "\n";
        }
    }

    void AddNewFile(const std::string& fileName, int size) {
        if(GetFileWithName(fileName) == nullptr) {
            // Create only new files, with unique name
            File* f = new File();
            f->name = fileName;
            f->size = size;
            files.push_back(f);
            UpdateFolderTotalSizes(size);
        }
        else {
            // std::cout << lineNumber << " - Folder with the same name of " << lineTokens[1] << " already exists inside " << currentlyOpenFolder->name << "\n";
        }
    }

    void GetPart1Result(long long & result, int maxSize) {
        for(auto f : folders) {
            f->GetPart1Result(result, maxSize);
        }
        if(totalSize <= maxSize) result += totalSize;
        else {
            result += 0;
        }
    }

    void GetPart2FittingFolders(std::vector<Folder*> &resultList, long requiredSize) {
        for(auto f : folders) {
            f->GetPart2FittingFolders(resultList, requiredSize);
        }
        if(totalSize >= requiredSize) {
            resultList.push_back(this);
        }
    }

};
Folder root;

void ExecuteCommand(std::string command, Folder** currentFolder) {
    auto line = SplitString(command, " ");
    std::string commandName = line[1]; // line[0] is "$"

    if(commandName == "ls"){
        // We read next couple of lines without doing any real action here
    }
    else if(commandName == "cd") {
        std::string commandParam = line[2];
        if(commandParam == "/"){
            *currentFolder = &root;
        }
        else if(commandParam == ".."){
            *currentFolder = (*currentFolder)->parent;
        }
        else {
            Folder* folderToMove = (*currentFolder)->GetFolderWithName(commandParam);
            if(folderToMove != nullptr){
                *currentFolder = folderToMove;
            }
            else {
                std::cout << "Encountered null folder?" << std::endl;
            }
        }
    }
    else {
        std::cout << "Unknown command encountered" << std::endl;
    }
}


int main() {
    std::vector<std::string> input = ReadStrings(FILE_PATH);
    root.name = "/";

    Folder* currentlyOpenFolder = &root;
    int lineNumber = 1;
    for(std::string line : input){
        lineNumber++;
        if(line[0] == '$'){
            ExecuteCommand(line, &currentlyOpenFolder);
        }
        else {
            std::vector<std::string> lineTokens = SplitString(line, " ");
            if(lineTokens[0] == "dir") {
                currentlyOpenFolder->CreateNewFolder(lineTokens[1]);
            }
            else {
                currentlyOpenFolder->AddNewFile(lineTokens[1], StringToInt(lineTokens[0]));
            }
        }
    }

    long long finalResult = 0;
    root.GetPart1Result(finalResult, 100000);
    PRINT(1, finalResult);

    long long requiredSize = 30000000 - (70000000 - root.totalSize);

    std::vector<Folder*> allFolders;
    root.GetPart2FittingFolders(allFolders, requiredSize);
    allFolders.push_back(&root);
    std::sort(allFolders.begin(), allFolders.end(), [](Folder* a, Folder* b){ return a->totalSize < b->totalSize; });
    PRINT(2, allFolders[0]);
    // Most likely will change to a better solution where we just track of smallest accepted number while also
    // iterating through all folders inside Folder struct
    
}
