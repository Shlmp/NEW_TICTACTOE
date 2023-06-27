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
string askYesNo(string question);
char winner(const vector<char>& board);
int askNumber(string question, int high);
void displayBoard(vector<char>& board);
int playerMove(const vector<char>& board, char player);
bool isLegal(int move, const vector<char>& board);

int main()
{
    srand(time(NULL));
    char player = playerSymbol();
    char computer = opponent(player);
    instructions();
    //char turn = X;
    vector<char> boardCopy = board;

    while (winner(board) == NO_ONE)
    {
        cout << "Player - " << player << "    AI - " << computer << endl;
        if (/*turn == */player)
        {
            playerMove(boardCopy, player);
        }
        displayBoard(boardCopy);
    }
}

void instructions()
{
    //system("cls");
    cout << "Welcome to Tic-Tac-Toe\nChoose a space between 0 - 8\n";
    cout << "0 | 1 | 2\n";
    cout << "3 | 4 | 5\n";
    cout << "6 | 7 | 8\n";
    //for (int i = 0; i < 3; i++)
    //{
    //    for (int j = 0; j < 3; j++)
    //    {
    //        cout << board[j];
    //        if (j < 2) cout << " |";
    //    }
    //    cout << endl;
    //}
}

char playerSymbol()
{
    string goFirst = askYesNo("ODD or EVEN, What do you choose?");
    int min = 1;
    int max = 6;
    int die = rand() % (max - min + 1) + 1;
    if (goFirst == "EVEN")
    {
        if (die == 2 || die == 4 || die == 6)
        {
            cout << "CONGRATULATIONS!!   You rolled an even number: " << die << endl;
            return X;
        }
        else
        {
            cout << "HA LOSER!     You rolled an odd number: " << die << endl;
            return O;
        }
    }
    else
    {
        if (die == 1 || die == 3 || die == 5)
        {
            cout << "CONGRATULATIONS!!   You rolled an odd number: " << die << endl;
            return X;
        }
        else
        {
            cout << "HA LOSER!     You rolled an even number: " << die << endl;
            return O;
        }
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

string askYesNo(string question)
{
    string answer;

    do
    {
        cout << "\n" << question << endl;
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
    } while (answer != "ODD" && answer != "EVEN");
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

int askNumber(string question, int high)
{
    string input;
    bool isValid = false;
    bool isRangeValid = false;
    int number = 0;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do
    {
        cout << question << " between " << 0 << " & " << high << endl;
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
            isRangeValid = number <= high && number >= 0;
        }

        if (!isRangeValid && isValid)
        {
            cout << "Invalid option\n";
        }
    } while (!isValid || input.empty() || !isRangeValid);
    return number;
}

void displayBoard(vector<char>& board)
{
    cout << *(board.begin() + 0) << " | " << *(board.begin() + 1) << " | " << *(board.begin() + 2) << endl
        << *(board.begin() + 3) << " | " << *(board.begin() + 4) << " | " << *(board.begin() + 5) << endl
        << *(board.begin() + 6) << " | " << *(board.begin() + 7) << " | " << *(board.begin() + 8) << endl;
}

int playerMove(const vector<char>& board, char player)
{
    int move = askNumber("Choose the space you want to use", (board.size() - 1));

    while (!isLegal(move, board))
    {
        cout << "\nSpace already in use\n";
        move = askNumber("Choose the space you want to use", (board.size() - 1));
    }

    return move;
}

inline bool isLegal(int move, const vector<char>& board)
{
    return (board[move] == EMPTY);
}

int computerMove(vector<char> board, char computer)
{
    int move = 0;
    bool foundSpace = false;

    while (!foundSpace && move < board.size())
    {
        if (isLegal(move, board))
        {
            board[move] = computer;
            foundSpace = winner(board) == computer;
        }

        if (!foundSpace)
        {
            move++;
        }
    }

    if (!foundSpace)
    {
        move = 0;
        char human = opponent(computer);
        while (!foundSpace && move < board.size())
        {
            if (isLegal(move, board))
            {
                board[move] = human;
                foundSpace = winner(board) == human;
            }

            if (!foundSpace)
            {
                move++;
            }
        }
    }

    if (!foundSpace)
    {
        move = 0;
        unsigned int i = 0;
        //const int BEST_MOVE = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
    }
}