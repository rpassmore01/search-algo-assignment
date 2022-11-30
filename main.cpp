#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

bool validPos(int x, int y, int xSize, int ySize){
    if(x < 0 || y < 0 || x+1 > xSize || y+1 > ySize){
        return false;
    }
    return true;
}

bool findWord(char arr[][5], string word, int start, int x, int y, vector<vector<int>> usedPos){
    if(start == word.size()){
        return true;
    }
    vector<vector<int>> possiblePositions;
    if(validPos(x-1,y-1,5,5)){
        possiblePositions.push_back({x-1,y-1});
    }
    if(validPos(x-1,y,5,5)){
        possiblePositions.push_back({x-1,y});
    }
    if(validPos(x-1,y+1,5,5)){
        possiblePositions.push_back({x-1,y+1});
    }
    if(validPos(x,y-1,5,5)){
        possiblePositions.push_back({x,y-1});
    }
    if(validPos(x,y+1,5,5)){
        possiblePositions.push_back({x,y+1});
    }
    if(validPos(x+1,y-1,5,5)){
        possiblePositions.push_back({x+1,y-1});
    }
    if(validPos(x+1,y,5,5)){
        possiblePositions.push_back({x+1,y});
    }
    if(validPos(x+1,y+1,5,5)){
        possiblePositions.push_back({x+1,y+1});
    }
    for (int i = 0; i < possiblePositions.size(); i++){
        int tmpX = possiblePositions[i][0];
        int tmpY = possiblePositions[i][1];
        if(arr[tmpY][tmpX] == word[start]){
            cout << tmpX << tmpY << endl;
            return findWord(arr, word, start + 1, tmpX, tmpY, usedPos);
        }
    }
    return false;
}

bool searchWord(char arr[][5], string word, int start){
    if(start == 0){
        vector<vector<int>> startingLetters;
        vector<vector<int>> usedPos;
        for (int y = 0; y < 5; y++){
            for (int x = 0; x < 5; x++){
                if(arr[y][x] == word[start]){
                    startingLetters.push_back({y, x});
                }
            }
        }
        for (int i = 0; i < startingLetters.size(); i++){
            if(findWord(arr, word, start + 1, startingLetters[i][1], startingLetters[i][0], usedPos)){
                return true;
            }
        }
    }
    return false;
}

int main(){
    char charArr[5][5];
    const string alphabet {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    srand(time(NULL));
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            charArr[i][j] = alphabet[rand() % 23];
        }
    }

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            cout << charArr[i][j];
        }
        cout << endl;
    }

    string tmpInput;
    cout << "Enter a word you would like to find in the grid: ";
    cin >> tmpInput;

    cout << searchWord(charArr, tmpInput, 0);
}