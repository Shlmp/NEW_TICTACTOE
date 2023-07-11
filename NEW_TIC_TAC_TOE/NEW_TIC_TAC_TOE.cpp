//Tic-Tac-Toe
//Playing Tic Tac Toe with an AI
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <locale.h>

using namespace std;

//Global Constants
const char X = 'X';
const char O = 'O';
const char TIE = 'T';
const char EMPTY = ' ';
const char NO_ONE = 'N';

//Prototype Functions
char winner(const vector<char>* const pBoard);
void displayBoard(const vector<char>* const pBoard);
bool isLegal(int move, const vector<char>* const pBoard);
int humanMove(const vector<char>* const pBoard);

void instructions();
char askYesNo(string question);
char humanSymbol();
char opponent(char symbol);
int askNumber(string question, int high, int low = 0);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char human, char computer);


//Function main
int main() {
	setlocale(LC_ALL, "spanish");

	const int NUM_SQUARES = 9;
	int move;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	char player = humanSymbol();
	char computer = opponent(player);
	char turn = X;

	//displayBoard(board);

	while (winner(&board) == NO_ONE) {

		if (turn == player) {
			move = humanMove(&board);
			board[move] = player;
		}
		else {
			move = computerMove(board, computer);
			board[move] = computer;
		}

		turn = opponent(turn);
		displayBoard(&board);
	}

	announceWinner(winner(&board), player, computer);

}

//Return the piece winner a tie or noBody
char winner(const vector<char>* const pBoard)
{
	//This are the posibilities to win.
	const int WINNING_POS[8][3] = { {0, 1, 2},
									{3, 4, 5},
									{6, 7, 8},
									{0, 3, 6},
									{1, 4, 7},
									{2, 5, 8},
									{2, 4, 6},
									{0, 4, 8} };

	const int TOTAL_ROWS = 8;

	//Return the winner
	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if (((*pBoard)[WINNING_POS[row][0]] != EMPTY) &&
			((*pBoard)[WINNING_POS[row][0]] == (*pBoard)[WINNING_POS[row][1]]) &&
			((*pBoard)[WINNING_POS[row][1]] == (*pBoard)[WINNING_POS[row][2]]))
		{
			return (*pBoard)[WINNING_POS[row][0]];
		}

	}

	//Return a Tie
	if (count(pBoard->begin(), pBoard->end(), EMPTY) == 0) {
		return TIE;
	}

	//Return that no one is the winner yet
	return NO_ONE;
}

void instructions() {
	cout << "\n¡Bienvenido al juego de Gato!\n";
	cout << "Donde te enfrentarás a un digno oponente\n";
	cout << "Debes elegir un número 0 - 8 para definir una posición en el tablero: \n";
	cout << " 0 | 1 | 2 \n";
	cout << " 3 | 4 | 5 \n";
	cout << " 6 | 7 | 8 \n";

	cout << "Prepárate la batalla está a punto de comenzar.\n\n";
}

char askYesNo(string question) {
	char answer;
	do {
		cout << question << "(y/n)";
		cin >> answer;
	} while (answer != 'y' && answer != 'n');
	return answer;
}

int askNumber(string question, int high, int low) {
	int number;
	do {
		cout << question << "(" << low << " - " << high << ")";
		cin >> number;
	} while (number > high || number < low);

	return number;
}


char humanSymbol() {
	char go_first = askYesNo("¿Quieres empezar?");

	if (go_first == 'y')
	{
		cout << "Buena elección, la necesitarás\n";
		return X;
	}
	else {
		cout << "Admiro tu valentía, yo empezaré entonces\n";
		return O;
	}
}

char opponent(char symbol) {
	if (symbol == X) {
		return O;
	}
	else
	{
		return X;
	}
}


void displayBoard(const vector<char>* const pBoard) {
	cout << "\n\t" << (*pBoard)[0] << " | " << (*pBoard)[1] << " | " << (*pBoard)[2];
	cout << "\n\t" << (*pBoard)[3] << " | " << (*pBoard)[4] << " | " << (*pBoard)[5];
	cout << "\n\t" << (*pBoard)[6] << " | " << (*pBoard)[7] << " | " << (*pBoard)[8];
	cout << "\n";
}




inline bool isLegal(int move, const vector<char>* pBoard) {

	bool isLegal = false;


	if ((*pBoard)[move] == EMPTY)
	{
		isLegal = true;
	}

	return isLegal;


	//return (board[move] == EMPTY);
}


int humanMove(const vector<char>* const pBoard) {
	int move = askNumber("¿Elige una posición del tablero?", (pBoard->size() - 1));

	while (!isLegal(move, pBoard)) {
		cout << "\nEsa posición ya está ocupada humano tonto.\n";
		move = askNumber("¿Elige una posición del tablero?", (pBoard->size() - 1));
	}

	cout << "Bien..\n";
	return move;
}


int computerMove(vector<char> board, char computer) {
	int move = 0;
	bool foundSpace = false;


	while (!foundSpace && move < board.size()) {

		if (isLegal(move, &board)) {


			board[move] = computer;

			foundSpace = winner(&board) == computer;

			if (winner(&board) == computer) {
				foundSpace = true;
			}

			board[move] = EMPTY;
		}

		if (!foundSpace) {
			++move;
		}
	}


	if (!foundSpace) {
		move = 0;
		char human = opponent(computer);
		while (!foundSpace && move < board.size()) {

			if (isLegal(move, &board)) {


				board[move] = human;

				foundSpace = winner(&board) == human;

				board[move] = EMPTY;
			}

			if (!foundSpace) {
				++move;
			}
		}

	}


	if (!foundSpace) {
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVE[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

		while (!foundSpace && i < board.size()) {

			move = BEST_MOVE[i];
			if (isLegal(move, &board)) {
				foundSpace = true;
			}

			++i;
		}
	}

	cout << "\nUsaré la posición " << move << "." << endl;
	return move;
}

void announceWinner(char winner, char human, char computer) {
	if (winner == computer) {
		cout << "\nEl ganador es: " << winner << endl;
		cout << "\n Soy el ganador!! Probando una vez más que las computadoras somos mejores que ustedes en todo sentido.\n";
	}
	else if (winner == human) {
		cout << "\nEl ganador es: " << winner << endl;
		cout << "\nNo es posible!! Hiciste trampa humano!!";
	}
	else {
		cout << "\n ES UN EMPATE\n";
		cout << "\nQue suerte tienes, celébralo es lo mejor que lograrás.\n";
	}
}