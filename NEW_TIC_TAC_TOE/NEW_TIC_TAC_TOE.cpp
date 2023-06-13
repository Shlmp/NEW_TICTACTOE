#include <iostream>
#include <vector>

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
char winner();

int main()
{
    char player = playerSymbol();
    char computer = opponent(player);
    instructions();

    while (winner() == NO_ONE)
    {
        cout << "Player - " << player << "    AI - " << computer;
        char turn = X;
    }
}

void instructions()
{
    cout << "Welcome to Tic-Tac-Toe\nChoose a space between 0 - 8\n";
    cout << "0 | 1 | 2\n";
    cout << "3 | 4 | 5\n";
    cout << "6 | 7 | 8\n";
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

char winner(/*Tomar como referencia/copia el tablero (board) para identificar quien gana*/)
{
    //retornar al ganador (return X  -  return O  -  return NO_ONE  -  return TIE)
    //                     si gana x    si gana o    si no hay ganador  cuando hay empate
}