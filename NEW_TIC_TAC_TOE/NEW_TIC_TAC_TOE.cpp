#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <clocale>

using namespace std;

const int NUM_SQUARES = 9;
const char EMPTY = ' ';
const char X = 'X';
const char O = 'O';
const char NO_ONE = 'N';
const char TIE = 'T';
const vector<char> board(NUM_SQUARES, EMPTY);

void instructions();
char playerSymbol();
char opponent(char& player);
char askYesNo(string question);
char winner(const vector<char>& board);
int askNumber(string question, int high, int low);

int main()
{
    char player = playerSymbol();
    char computer = opponent(player);
    instructions();

    while (winner(board) == NO_ONE)
    {
        cout << "Player - " << player << "    AI - " << computer;
        char turn = X;
    }
}

void instructions()
{
    cout << "Welcome to Tic-Tac-Toe\nChoose a space between 0 - 8\n";
    //cout << "0 | 1 | 2\n";
    //cout << "3 | 4 | 5\n";
    //cout << "6 | 7 | 8\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[j];
            if (j < 2) cout << " |";
        }
        cout << endl;
    }
}

char playerSymbol()
{
    char goFirst = askYesNo("Do you want to have the first move?");
    if (goFirst == 'y')
    {
        return X;
    }
    else
    {
        return O;
    }
}

char opponent(char& player)
{
    if (player == X)
    {
        return O;
    }
    else
        return X;
}

char askYesNo(string question)
{
    char answer;

    do
    {
        cout << "\n" << question << "(y/n)\n";
        cin >> answer;
    } while (answer != 'y' && answer != 'n');
    //if (answer == 'y')
    //{
    //    return X;
    //}
    return answer;
}

char winner(const vector<char>& board)
{
    //Winning Positions
    const int WINNING_POS[8][3] = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 },  //Horizontal
                                    { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 },  //Vertical
                                    { 2, 4, 6 }, { 0, 4, 8 } };             //Diagonal
    const int TOTAL_ROWS = 8;

    //Return Winner
    for (int row = 0; row < TOTAL_ROWS; row++)
    {
        if ((board[WINNING_POS[row][0]] != EMPTY) &&
            (board[WINNING_POS[row][0]] == board[WINNING_POS[row][1]]) &&
            (board[WINNING_POS[row][1]] == board[WINNING_POS[row][2]]))     //Compares first position to second position and if == then check if second is == to third
        {
            return board[WINNING_POS[row][0]];
        }
    }

    //Return Tie
    if (count(board.begin(), board.end(), EMPTY) == 0)  return TIE;

    //Return if there is no winner
    return NO_ONE;
}

int askNumber(string question, int high, int low)
{
    string input;
    bool isValid = false;
    bool isRangeValid = false;
    int number = 0;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do
    {
        cout << question << "entre " << low << " y " << high << endl;
        getline(cin, input);

        for (char c : input)
        {
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
            else
            {
                isValid = true;
                break;
            }
        }

        if (!isValid)
        {
            cout << "Invalid option\n";
        }
        else
        {
            number = stoi(input);
            isRangeValid = number <= high && number >= low;
        }

        if (!isRangeValid && isValid)
        {
            cout << "Invalid option\n";
        }
    } while (!isValid || input.empty() || !isRangeValid);
    return number;
}