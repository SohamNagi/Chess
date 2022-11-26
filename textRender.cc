#include <iostream>
#include <string>
#include <vector>
using namespace std;

char** fenToBoard(string input){
    int row = 7;
    int col = 0;
    int i = 0;
    char** board = new char*[8];
    for (int h = 0; h < 8; h++){
        board[h] = new char[8];
        for (int w = 0; w < 8; w++){
            board[h][w] = ' ';
        }
    }
    while (input[i] != ' ') {
        char curr = input[i];
        if (curr == '/'){
            row--;
        } else if (isdigit(curr)) {
            col += curr;
        } else {
            board[row][col] = curr;
            col++;
        }
        i++;
    }
    char** out = board;
    return out;
}

void printBoard(char** Board){
    cout << "A B C D E F G H";
    for(int i = 0; i < 8; i ++){
        cout << i+1 << " ";
        for(int j = 0; j < 8; j++){
            char curr = Board[i][j];
            if (curr == ' '){
                if ((i+j) % 2 == 0){
                    cout << " ";
                } else {
                    cout << "_";
                }
            } else {
                cout << curr;
            }
        }
        cout << endl;
    }
}

int main(int argc, const char** argv) {
    string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    vector<char> board = fenToBoard(fen);
    for(char i: board){
        cout << i;
    }
    printBoard(fenToBoard(fen));
}
