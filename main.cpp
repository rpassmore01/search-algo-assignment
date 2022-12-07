#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>

using namespace std;

//  A function to check if a position is valid on the board
bool validPos(int x, int y, int xSize, int ySize){
    if(x < 0 || y < 0 || x+1 > xSize || y+1 > ySize){
        return false;
    }
    return true;
}

//  A recursive function that searches a 2d array for a word
bool findWord(char arr[][5], string word, int start, int x, int y, vector<vector<int>> *usedPos){
    //  If the function is called on the last letter then the whole word has been found
    if(start == word.size()){
        usedPos->push_back({x,y});
        return true;
    }
    //  Vector to store all possible positions
    vector<vector<int>> possiblePositions;

    //  Check all 8 squares that surround the square to see if it is a valid position
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

    //  Loop through all possible positions
    for (int i = 0; i < possiblePositions.size(); i++){
        int tmpX = possiblePositions[i][0];
        int tmpY = possiblePositions[i][1];
        //  Check if current possible position's letter is the letter we are looking for
        if(arr[tmpY][tmpX] == word[start]){
            arr[y][x] = ' ';
            usedPos->push_back({x,y});
            //  Recurivley check around the current possible position to complete the word
            if(findWord(arr, word, start + 1, tmpX, tmpY, usedPos)) return true;
            // If the current possible position was not correct reset the used poitions and word arr
            else {
                usedPos->pop_back();
                arr[tmpY][tmpX] = word[start];
            }
        }
    }
    return false;
}

bool searchWord(char arr[][5], string word, int start, vector<vector<int>> *usedPos){
    if(start == 0){
        //  Find all the positions of the first letter in the word, in the array
        vector<vector<int>> startingLetters;
        for (int y = 0; y < 5; y++){
            for (int x = 0; x < 5; x++){
                if(arr[y][x] == word[start]){
                    startingLetters.push_back({y, x});
                }
            }
        }
        // Loop through all of the possible word starting locations
        for (int i = 0; i < startingLetters.size(); i++){
            //  Setup a temp array to store the initial setup of the array
            //  Required because we set used positions to ' '
            char tmpArr[5][5];
            for(int i=0; i < 5; i++){
                for(int j = 0; j < 5; j++) {
                    tmpArr[i][j] = arr[i][j];
                }           
            }
            //  Recursivly check if word stems from the current starting letter
            if(findWord(arr, word, start + 1, startingLetters[i][1], startingLetters[i][0], usedPos)){
                //  Reset default array
                for(int i=0; i < 5; i++){
                    for(int j = 0; j < 5; j++) {
                        arr[i][j] = tmpArr[i][j];
                    }           
                }
                return true;
            }
            //Reset used positions and defualt array
            usedPos->clear();
            for(int i=0; i < 5; i++){
                for(int j = 0; j < 5; j++) {
                    arr[i][j] = tmpArr[i][j];
                }         
            }
        }
    }
    return false;
}

int main(){
    char charArr[5][5];
    const string alphabet {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    vector<vector<int>> usedPositions;
    string playAgainInput = "G";

    srand(time(NULL));

    //  Loop while player hasn't quit the game
    while(playAgainInput != "Q"){
        //  Generate new board
        if(playAgainInput == "G"){
            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 5; j++){
                    charArr[i][j] = alphabet[rand() % 23];
                }
            }
        }

        //  Print out board
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                cout << charArr[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n";

        if(playAgainInput != "F"){
            //  Get user input for word they want to get
            string tmpInput;
            cout << "Enter a word you would like to find in the grid: ";
            cin >> tmpInput;
            for(auto &c: tmpInput) c = toupper(c);

            //  Check if word guessed by user is in the 2d array
            if(searchWord(charArr, tmpInput, 0, &usedPositions)){
                cout << "\n" << "Word Found!!" << "\n" << endl;
                //  Print out 2d array with the letters used colored green
                for (int i = 0; i < 5; i++){
                    for (int j = 0; j < 5; j++){
                        vector<int> key = {j,i};
                        if(count(usedPositions.begin(), usedPositions.end(),key)){
                            cout << "\033[32m" << charArr[i][j] << "\033[0m" << " ";
                        }   
                        else {
                            cout << charArr[i][j] << " ";
                        }
                    }
                    cout << endl;
                }
            }
            else {
                cout << "\n" "Word not found :(" << "\n" << endl;
            }
        }
        else {
            ifstream ifs("words_alpha.txt");
            string line;
            while(ifs >> line){
                for(int i = 0; i < line.size(); i++){
                    line[i] = toupper(line[i]);
                } 
                if(searchWord(charArr, line, 0, &usedPositions) && line.size() > 3) cout << line << endl;
            }
        }

        //  Get user input for what they want to do next
        cout << "\n" << "Play again [p], Generate new board [g], Find all words in the array longer than 3 letters [F] or Quit [q]: ";
        cin >> playAgainInput;
        for(auto &c: playAgainInput) c = toupper(c);
        usedPositions.clear();
        cout <<"\n\n";
    }

}