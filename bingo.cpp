#include <iostream>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <Windows.h>
int scorePlayerOne = 0, scorePlayerTwo = 0;
using namespace std;
int score(int board[25][25], int dimension)
{
	int counter = 0;
	for (int i = 0; i < dimension; i++)
	{
		int rowSum = 0, colSum = 0;
		for (int j = 0; j < dimension; j++)
		{
			rowSum += board[i][j];
			colSum += board[j][i];
		}
		if (rowSum == 0)
		{
			counter++;
		}
		if (colSum == 0)
		{
			counter++;
		}
	}
	int diagSum1 = 0, diagSum2 = 0;
	for (int i = 0; i < dimension; i++)
	{
		diagSum1 += board[i][i];
		diagSum2 += board[i][dimension - i - 1];
	}
	if (diagSum1 == 0)
	{
		counter++;
	}
	if (diagSum2 == 0)
	{
		counter++;
	}
	return counter;
}
void loadingScreen()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tLoading......";
	for (int i = 0; i < 25; i++)
	{
		cout << (char)219;
		Sleep(150);
	}
	cout << "\t\t\t\t\t\t\t\t\tENJOY OUR GAME";
	Sleep(150);
}
// Function to decide who will have the first turn in the game
int toss()
{
	return rand() % 2;
}

// Function to generate random number (within the limits of the board, for instance, 1-25 for a 5x5 Board) to put in the player's board

int generateRandomNumber(int area)
{
	return (rand() % area) + 1;
}

// Function to check if a number is already present in the given player's board

bool isNumberUnique(int board[25][25], int number, int row, int column, int dimension)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			if (board[i][j] == number)
			{
				return false; // Number is not unique, i.e., it is already present in the given player's board
			}
		}
	}
	for (int i = 0; i < column; i++)
	{
		if (board[row][i] == number)
		{
			return false; // Number is not unique, i.e., it is already present in the given player's board
		}
	}
	return true; // Number is unique ,that is ,number is not already present in the given player's board
}

// Function to generate a complete Bingo board for a given player

void generateBingoBoard(int board[25][25], int dimension, int area)
{
	for (int i = 0; i < dimension; ++i)
	{
		for (int j = 0; j < dimension; ++j)
		{
			int number;
			do
			{
				number = generateRandomNumber(area); // generates a new random number within the limits
			} while (!isNumberUnique(board, number, i, j, dimension)); // Checks if the nymber is uniquw
			board[i][j] = number; // assigns the new randomly generated number, if it is unique, to the given player's board
		}
	}
}
// Function to print the Bingo Board of the given player
void printBoard(int board[25][25], string playerName, int dimension)
{
	cout << "Bingo Board for " << playerName << ":\n";
	for (int i = 0; i < dimension; i++) // Controls the row number of the Bingo Board being print
	{
		for (int j = 0; j < dimension; j++) // Prints the elements of the given row of the Bingo Board of the respecive player 
		{
			cout << board[i][j] << "\t";
			if (j < dimension - 1)
			{
				cout << "|"; // Prints a vertical line after each element of the column
			}
		}
		cout << endl;
		if (i < dimension - 1)
		{
			for (int k = 0; k < dimension - 1; k++) // Prints a horizontal line at the end of each row
			{
				cout << "---------";
			}
			cout << endl;
		}
	}
	cout << endl;
}
// Function to take a number from the player (on his turn) that he wants to eliminate
int input(int board[25][25], int area, string player, int dimension)
{
	int num;
	bool numberFound = false;
	do
	{
		cout << player << " enter a number please: ";
		while (!(cin >> num) || num <= 0 || num > area) // To check if the number is out of the limits
		{
			cin.clear(); // Clear error flag
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');/ // Discard invalid input
			while (cin.get() != '\n'); // To check if the user entered an invalid data type
			cout << "Invalid input. Please enter again : ";
		}
		numberFound = false;
		// To check if the number has already been eliminated
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				if (board[i][j] == num)
				{
					numberFound = true; // Number hasn't been eliminated. Therefore, valid input!
					break;
				}
			}
		}
		if (!numberFound) // Number already eliminated

		{
			cout << "number already used. Try again." << endl;
		}
	} while (!numberFound);
	return num; // Number passed all the checks
}

// Function to eliminate the number (entered by the users on their respective turns) from the Bingo Board's of both the players

void removeNumber(int board1[25][25], int board2[25][25], int num, int dimension)
{
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			if (board1[i][j] == num)
			{
				board1[i][j] = 0; // Eliminate from Player 1 Bingo Board
			}
			if (board2[i][j] == num)
			{
				board2[i][j] = 0; // Eliminate from Player 2 Bingo Board
			}
		}
	}
}
// Function to count the number of lines (rows, columns and diagonals) eliminated in the given player's board

// If the number of lines (rows, columns and diagonals) eliminated is equal to the value to the dimension

// Then the function returns true
bool checkWinner(int board[25][25], int dimension)
{
	int counter = 0; // Initializes the counter to zero so that it starts from zero after each turn (of both the players)
	// Check for a winning condition in the rows, columns, and diagonals
	for (int i = 0; i < dimension; i++)
	{
		int rowSum = 0; // Initializes the sum of a given row to zero after every iteration
		int colSum = 0; // Initializes the sum of a given column to zero after every iteration
		for (int j = 0; j < dimension; j++)
		{
			rowSum += board[i][j]; // Takes the sum of each element of a given row
			colSum += board[j][i]; // Takes the sum of each element of a given column
		}
		if (rowSum == 0)
		{
			counter++; // Adds one to the counter if the a complete row has been eliminated in a given player's board
		}
		if (colSum == 0)
		{
			counter++; // Adds one to the counter if the complete column has been eliminated in a given player's board

		}
	}
	// Check diagonals
	int diagSum1 = 0; // Initializes the counter to zero so that it starts from zero after each turn (of both the players)
	int diagSum2 = 0; // Initializes the counter to zero so that it starts from zero after each turn (of both the players)
	for (int i = 0; i < dimension; i++)
	{
		diagSum1 += board[i][i]; // Takes the sum of each element of a given principle diagonal
		diagSum2 += board[i][dimension - i - 1]; // Takes the sum of each element of a given anti diagonal
	}
	if (diagSum1 == 0)
	{
		counter++; // Adds one to the counter if the complete principle diagonal has been eliminated in a given player's board
	}
	if (diagSum2 == 0)
	{
		counter++; // Adds one to the counter if the complete anti diagonal has been eliminated in a given player's board
	}
	if (counter >= 5)
	{
		return true; // Returns TRUE if the number of lines (rows, columns and diagonals) eliminated IS EQUAL to the value to the dimension
	}
	return false; // Returns FALSE if the number of lines (rows, columns and diagonals) eliminated is NOT equal to the value to the dimension
}
void announceWinner(int board1[25][25], int board2[25][25], string s1, string s2, int dimension)
{
	if (checkWinner(board1, dimension)) // checks if player 1 has won
	{
		system("cls"); // clear screen
		cout << endl << s1 << "Won!" << endl << endl;
		printBoard(board1, s1, dimension); // Display player 1 Bingo Board
		return;
	}
	if (checkWinner(board2, dimension)) // checks if player 2 has won
	{
		system("cls"); // clear screen
		cout << endl << s2 << "Won!" << endl << endl;
		printBoard(board2, s2, dimension); // Display player 2 Bingo Board
		return;
	}
}

int main()
{
	//Seed for random number generation
	srand(time(0));

	//Player Names
	string firstPlayer;
	string secondPlayer;
	string currentPlayer;

	//Dimensions of the Board
	int dimension = 0;
	int area = 0;

	//Variable to store number input by the user to be eliminated
	int num;

	//Arrays to store Player Boards
	int player1Board[25][25];
	int player2Board[25][25];

	//Unique Game ID
	int gameId = (rand() % 10000) + 1;

	// Toss to decide which players gets the first turn
	int turn = toss();

	//For Background and Text Color of the Console
	system("color 01");
	//For the Desired Operation of the User
	int option;

	
	cout << "\t\t\t\t\t\t ########  ####  ###    ##  ########  ########\n";
	cout << "\t\t\t\t\t\t ##    ##   ##   ## #   ##  ##        #      #\n";
	cout << "\t\t\t\t\t\t ########   ##   ##  #  ##  ##   ###  #      # \n";
	cout << "\t\t\t\t\t\t ##    ##   ##   ##   # ##  ##     #  #      #\n";
	cout << "\t\t\t\t\t\t ########  ####  ##    ###  ########  ########\n\n\n";
	// Display menu of the Bingo Game
	cout << "\t\t\t\t\t\t1. Enter 1 to Start A new Game : \n\n\n\t\t\t\t\t\t2. Enter 2 To Resume Previous Game :\n\n\n\t\t\t\t\t\t3. Enter 3 to See HighScores\n\n\n";
	cout << "\t\t\t\t\t\t4. Enter 4 To See The Tutorial\n\n\n\t\t\t\t\t\t5. Enter 5 to see Game History\n\n\n\t\t\t\t\t\t6. Enter 6 to Exit :" << endl;
	cout << "Enter Option";
	while (!(cin >> option) || option < 1 || option > 6)
	{
		cin.clear(); // Clear error flag
		/*Discard invalid input*/
		while (cin.get() != '\n'); // Checks if the data type of the input data is valid
		cout << "Invalid input. Please enter again : ";
	}

	//New Game
	if (option == 1)
	{
		system("cls"); // Clear Screen
		loadingScreen(); // Load Scree
		system("cls"); // Clear Scren

		// Seed for random number generation
		srand(time(0));

		// Variable for the dimensions of the Bingo Board. Each Bingo Board has dimensions: "dimension x dimension"
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter the dimension the bingo board (from 3-25): ";
		while (!(cin >> dimension) || dimension < 3 || dimension > 25)
		{
			cin.clear(); // Clear error flag
			// Discard invalid input
			while (cin.get() != '\n'); // Checks if the data type of the input data is valid
			cout << "Invalid input.Enter the dimension the bingo board (from 3-25):";
		}
		area = dimension * dimension;

		//Getting Player Names by the User
		cin.ignore();
		cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter the name of the first player: ";
		cin >> firstPlayer; // Gets the name of the first player
		cout << "\t\t\t\t\t\tEnter the name of the second player: ";
		cin >> secondPlayer; // Gets the name of the second player 

		// Generates Bingo Board for the two players and stores them in their respective 2D Arrays 
		generateBingoBoard(player1Board, dimension, area);
		generateBingoBoard(player2Board, dimension, area);

		while (true)
		{
		continueGame:
			system("cls"); // Clear Screen

			cout << "Game ID : " << gameId << endl;

			//First Player's Turn
			if (turn == 1)
			{
				currentPlayer = firstPlayer;

				//Prints Bingo Board of the First Player
				printBoard(player1Board, currentPlayer, dimension); // Prints Bingo Board of the first player

				//Takes the number to be eliminated from the First Player
				num = input(player1Board, area, currentPlayer, dimension);

				//Removes the entered number from boards of both the players
				removeNumber(player1Board, player2Board, num, dimension);

				//Stores the current score of the players
				scorePlayerOne = score(player1Board, dimension);
				scorePlayerTwo = score(player2Board, dimension);

				//Saving the Game
				fstream gameSave;
				//Opening the file for saving current progress
				gameSave.open("savedGame.txt", ios::out);
				//Writing in the opened file
				gameSave << gameId << " " << " " << turn << " " << firstPlayer << " " << secondPlayer << " " << scorePlayerOne << " " << scorePlayerTwo << " " << dimension << " " << area << endl;
				//Storing (writing) the player boards in the opened file
				//Storing (writing) the first player's board in the opened file
				for (int i = 0; i < dimension; i++)
				{
					for (int j = 0; j < dimension; j++)
					{
						gameSave << player1Board[i][j] << " ";
					}
					gameSave << endl;
				}
				//Storing (writing) the second player's board in the opened file
				for (int i = 0; i < dimension; i++)
				{
					for (int j = 0; j < dimension; j++)
					{
						gameSave << player2Board[i][j] << " ";
					}
					gameSave << endl;
				}
				//Closing the file
				gameSave.close();
			}
			//Second Player's Turn
			else
			{
				currentPlayer = secondPlayer;

				//Prints Bingo Board of the First Player
				printBoard(player2Board, currentPlayer, dimension); // Prints Bingo Board of the first player

				//Takes the number to be eliminated from the First Player
				num = input(player2Board, area, currentPlayer, dimension);

				//Removes the entered number from boards of both the players
				removeNumber(player1Board, player2Board, num, dimension);

				//Stores the current score of the players
				scorePlayerTwo = score(player2Board, dimension);
				scorePlayerOne = score(player1Board, dimension);

				//Saving the Game
				fstream gameSave;
				//Opening the file for saving current progress
				gameSave.open("savedGame.txt", ios::out);
				//Writing in the opened file
				gameSave << gameId << " " << " " << turn << " " << firstPlayer << " " << secondPlayer << " " << scorePlayerOne << " " << scorePlayerTwo << " " << dimension << " " << area << endl;
				//Storing (writing) the player boards in the opened file
				//Storing (writing) the first player's board in the opened file
				for (int i = 0; i < dimension; i++)
				{
					for (int j = 0; j < dimension; j++)
					{
						gameSave << player1Board[i][j] << " ";
					}
					gameSave << endl;
				}
				//Storing (writing) the second player's board in the opened file
				for (int i = 0; i < dimension; i++)
				{
					for (int j = 0; j < dimension; j++)
					{
						gameSave << player2Board[i][j] << " ";
					}
					gameSave << endl;
				}
				//Closing the File
				gameSave.close();
			}

			//To check if any player has won the game
			announceWinner(player1Board, player2Board, firstPlayer, secondPlayer, dimension);

			//If player one has won the game
			if (checkWinner(player1Board, dimension))
			{
				//Storing the Highest Score
				int highestScore;
				fstream highScore;
				//Opening the highest score file
				highScore.open("highScore.txt", ios::in);
				//Reading the Highest score previously stored
				highScore >> highestScore;
				//Closing the File
				highScore.close();
				//If player one has the highest score
				if (scorePlayerOne > highestScore)
				{
					//Opening the file to save highest score
					ofstream highscor("highScore.txt");
					//Writing the score of player one in it since it is the highest score
					highscor << scorePlayerOne;
					//closing the file
					highscor.close();
				}
				fstream input;
				//Opening the file to append information 
				input.open("gameHistory.txt", ios::app);
				//Retrieving information from the file
				input << gameId << endl;
				input << firstPlayer << " ";
				input << secondPlayer << endl;
				input << scorePlayerOne << " " << scorePlayerTwo << endl << endl;
				//Closing the file
				input.close();
				break;
			}

			//If player two has won the game
			if (checkWinner(player2Board, dimension))
			{
				//Storing the Highest Score
				int highestScore;
				fstream highScore;
				//Opening the highest score file
				highScore.open("highScore.txt", ios::in);
				//Reading the Highest score previously stored
				highScore >> highestScore;
				//closing the file
				highScore.close();
				//If player one has the highest score
				if (scorePlayerTwo > highestScore)
				{
					//Opening the file to save highest score
					ofstream highscor("highScore.txt");
					//Writing the score of player two in it since it is the highest score
					highscor << scorePlayerTwo;
					//closing the file
					highscor.close();
				}
				fstream input;
				//Opening the file to append information 
				input.open("gameHistory.txt", ios::app);
				//Retrieving information from the file
				input << gameId << endl;
				input << firstPlayer << " ";
				input << secondPlayer << endl;
				input << scorePlayerOne << " " << scorePlayerTwo << endl;
				cout << endl;
				//closing the file
				input.close();
				break;
			}
			//Updates the turn of the player
			turn = (turn == 0) ? 1 : 0;
		}
	}

	//To RESUME a previous game
	else if (option == 2)
	{
		fstream gameContinue;
		//Opening the file "savedGame.txt" to read from it
		gameContinue.open("savedGame.txt", ios::in);
		//To check if the file is open
		if (!gameContinue.is_open())
		{
			cout << "Error opening file." << endl;
			return 1;
		}
		//Retrieving information stored in the file "savedGame.txt"
		gameContinue >> gameId;
		gameContinue >> turn;
		gameContinue >> firstPlayer;
		gameContinue >> secondPlayer;
		gameContinue >> scorePlayerOne;
		gameContinue >> scorePlayerTwo;
		gameContinue >> dimension;
		gameContinue >> area;
		//Retrieving the first player's board
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				gameContinue >> player1Board[i][j];
			}
		}
		//Retrieving the second player's board
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				gameContinue >> player2Board[i][j];
			}
		}
		goto continueGame;
	}

	//To see the Highest Score
	else if (option == 3)
	{
		system("cls");
		int highestScore;
		fstream highScore;
		//Opening the file to read from it
		highScore.open("highScore.txt", ios::in);
		//Reading the highscore from it
		highScore >> highestScore;
		//Closing the file
		highScore.close();
		//Displaying the high score on the console
		cout << "The highest Score is " << highestScore << endl;
	}

	//To see Tutorial
	else if (option == 4)
	{
		system("cls");
		cout << "Tutorial" << endl;
		cout << "1) Enter the dimensions of the Bingo Board" << endl;
		cout << "2) Enter your name" << endl;
		cout << "3) Enter the number you want to eliminate at your respective turn" << endl;
		cout << "The first person to eliminate the number of lines equal to the value of dimension will win!" << endl;
	}

	//To see Game History
	else if (option == 5)
	{
		//Clearing the screen
		system("cls");

		fstream output;
		//Opening the file to read from it
		output.open("gameHistory.txt", ios::in);
		//While the file has not reached its end
		while (!output.eof())
		{
			int gameId, scoreOne, scoreTwo;
			string playerOne, playerTwo;
			//Reading from the file
			output >> gameId;
			output >> playerOne;
			output >> playerTwo;
			output >> scoreOne;
			output >> scoreTwo;
			if (!output.eof())
			{
				//Dsiplaying on the console
				cout << gameId << "\t";
				cout << playerOne << "\t";
				cout << scoreOne << "\t";
				cout << playerTwo << "\t";
				cout << scoreTwo << endl << endl;
			}
		}
		//Closing the file
		output.close();
	}
	//Exiting the Game
	else
	{
		cout << "You have exited the game!" << endl;
		cout << "Thank you for visiting our game." << endl;
		cout << "Have a Good Day!" << endl;
	}
	return 0;
}