#include<iostream>
#include<fstream>

using namespace std;

#define easy 1
#define intermediate 2
#define hard 3
#define maxSide 30
#define maxMine 99
#define maxMove 801 //30 * 30 - 99

int SIDE; //rozmiar pola, każde to kwadrat, więc starczy jedna zmienna
int MINES;	//ilość min

//x = rząd, y = kolumna

//pokazuje akualną planszę gry
void showBoard(char myBoard[][maxSide])
{
	int i, j;

	printf(" ");

	for (i = 0; i < SIDE; i++)
		printf("% d ", i);

	printf("\n\n");

	for (i = 0; i < SIDE; i++)
	{
		printf("% d ", i);

		for (j = 0; j < SIDE; j++)
			printf("%c ", myBoard[i][j]);
		printf("\n");
	}
	return;
}

//losowo rozstawia miny na planszy
void assignMine(int mines[][2], char realBoard[][maxSide])
{
	bool mark[maxSide * maxSide];

	memset(mark, false, sizeof(mark));

	for (int i = 0; i < MINES; )
	{
		int random = rand() % (SIDE * SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		if (mark[random] == false)
		{
			mines[i][0] = x;
			mines[i][1] = y;

			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}

	return;
}

//sprawda, czy podane pole znajduje się na planszy
bool isPlace(int x, int y)
{
	return (x >= 0) && (x < SIDE) &&
		(y >= 0) && (y < SIDE);
}

//sprawdza, czy podane pole jest miną
bool isMine(int x, int y, char board[][maxSide])
{
	if (board[x][y] == '*')
		return (true);
	else
		return(false);
}

//pozwala wykonać ruch
void makeMove(int* x, int* y)
{
	printf("Wprowadź swój ruch (rząd, kolumna)\n");
	scanf_s("%d %d", x, y);
	return;
};

//funkcja licząca, ile komórek jest obok wybranej przez gracza
int howManyCeMinesNextTo(int x, int y, int mines[][2], char realBoard[][maxSide])
{
	int i;
	int count = 0;

	//komórka na północ
	if (isPlace(x - 1, y) == true)
	{
		if (isMine(x - 1, y, realBoard) == true)
			count++;
	}

	//komórka na północny-zachód
	if (isPlace(x - 1, y - 1) == true)
	{
		if (isMine(x - 1, y - 1, realBoard) == true)
			count++;
	}

	//komórka na północny-wschód
	if (isPlace(x - 1, y + 1) == true)
	{
		if (isMine(x - 1, y, realBoard) == true)
			count++;
	}

	//komórka na południe
	if (isPlace(x + 1, y) == true)
	{
		if (isMine(x + 1, y, realBoard) == true)
			count++;
	}

	//komórka na południowy-zachód
	if (isPlace(x + 1, y - 1) == true)
	{
		if (isMine(x + 1, y - 1, realBoard) == true)
			count++;
	}

	//komórka na południowy-wschód
	if (isPlace(x + 1, y + 1) == true)
	{
		if (isMine(x - 1, y, realBoard) == true)
			count++;
	}

	//komórka na zachód
	if (isPlace(x, y - 1) == true)
	{
		if (isMine(x, y - 1, realBoard) == true)
			count++;
	}

	//komórka na wschód
	if (isPlace(x, y + 1) == true)
	{
		if (isMine(x, y + 1, realBoard) == true)
			count++;
	}

	return(count);
}

//funkcja inicjalizująca grę, tworząc losowo generowaną planszę
//i zaznacza wszystkie pola na planszy jako niewiadome
void preGame(char realBorad[][maxSide], char myBoard[][maxSide])
{
	srand(time(NULL));

	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			myBoard[i][j] = realBorad[i][j] = '-';
		}
	}

	return;
}

//głowne menu
void showGameMenu()
{
	int in, inB; //input
	while (1)
	{
		system("cls");
		cout << "-------------\n";
		cout << "--- SAPER ---\n";
		cout << "-------------\n\n";

		cout << "1. Zagraj w nową grę\n";
		cout << "2. Wyjdź\n\n";

		cin >> in;

		switch (in)
		{
		case 1:

			//wybieranie trudności
			printf("\nWybierz poziom trudności:\n");
			printf("1. Łatwy - 8x8\n");
			printf("2. Średni - 16x16\n");
			printf("3. Trudny - 30 x 16\n");
			printf("4. Powrót\n\n");

			scanf_s("%d", &inB);

			if (inB == easy)
			{
				system("cls");
				SIDE = 8;
				MINES = 20;
			}

			if (inB == intermediate)
			{
				system("cls");
				SIDE = 16;
				MINES = 40;
			}

			if (inB == hard)
			{
				system("cls");
				SIDE = 30;
				MINES = 99;
			}
			return;

			break;

		case 2:

			exit(0);
			break;
		}
	}
}

//przesuwa minę w wolne miejsce
void moveMine(int x, int y, char board[][maxSide])
{
	for (int i = 0; i, SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] != '*')
			{
				board[i][j] = '*';
				board[x][y] = '-';
				return;
			}
		}
	}
}

//gra w sapera - funkcja rekurencyjna
bool playGameUntil(char myBoard[][maxSide], char realBoard[][maxSide], int mines[][2], int x, int y, int* movesLeft)
{
	if (myBoard[x][y] != '-')
		return(false);

	int i, j;

	//odsłonięcie pola z miną
	if (realBoard[x][y] == '*')
	{
		myBoard[x][y] = '*';

		for (i = 0; i < MINES; i++)
			myBoard[mines[i][0]][mines[i][1]] = '*';

		system("cls");
		showBoard(myBoard);
		printf("\nPrzegrałeś!\n");
		return(true);
	}

	else
	{
		//oblicza ilość min obok odsłoniętego pola, i wyświetla na planszy
		int count = howManyCeMinesNextTo(x, y, mines, realBoard);
		(*movesLeft)--;

		myBoard[x][y] = count + '0';

		if (!count)
		{
			//komórka na północ
			if (isPlace(x - 1, y) == true)
			{
				if (isMine(x - 1, y, realBoard) == false)
					playGameUntil(myBoard, realBoard, mines, x - 1, y, movesLeft);
			}

			//komórka na pólnocny-zachód
			if (isPlace(x - 1, y - 1) == true)
			{
				if (isMine(x - 1, y - 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mines, x - 1, y - 1, movesLeft);
			}

			//komórka na pólnocny-wschód
			if (isPlace(x - 1, y + 1) == true)
			{
				if (isMine(x - 1, y + 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mines, x - 1, y + 1, movesLeft);
			}

			//komórka na południe
			if (isPlace(x + 1, y) == true)
			{
				if (isMine(x + 1, y, realBoard) == false)
					playGameUntil(myBoard, realBoard, mines, x + 1, y, movesLeft);
			}

			//komórka na południowy-zachód
			if (isPlace(x - 1, y - 1) == true)
			{
				if (isMine(x + 1, y - 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mines, x + 1, y - 1, movesLeft);
			}

			//komórka na południowy-wschód
			if (isPlace(x + 1, y + 1) == true)
			{
				if (isMine(x + 1, y + 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mines, x + 1, y + 1, movesLeft);
			}

			//komórka na zachód
			if (isPlace(x, y - 1) == true)
			{
				if (isMine(x, y - 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mines, x, y - 1, movesLeft);
			}

			//komórka na wschód
			if (isPlace(x, y + 1) == true)
			{
				if (isMine(x, y + 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mines, x, y + 1, movesLeft);
			}
		}

		return(false);
	}
}

void playGame()
{
	bool gameOver = false;

	char realBoard[maxSide][maxSide], myBoard[maxSide][maxSide];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[maxMine][2];

	preGame(realBoard, myBoard);

	assignMine(mines, realBoard);

	//gra się do momentu wygranej/odkrycia miny
	
	int currentMoveCount = 0;
	while (gameOver == false)
	{
		system("cls");
		printf("Aktualny stan planszy: \n");
		showBoard(myBoard);
		makeMove(&x, &y);

		currentMoveCount++;

		gameOver = playGameUntil(myBoard, realBoard, mines, x, y, &movesLeft);

		if ((gameOver == false) && (movesLeft == 0))
		{
			cout << "Wygrałeś!\n";
			gameOver = true;
		}
	}
	return;

}

int main()
{
	setlocale(LC_CTYPE, "Polish");

	showGameMenu();

	playGame();

	return(0);
}