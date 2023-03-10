#include<iostream>
#include<fstream>

using namespace std;

#define EASY 1
#define INTERMEDIATE 2
#define HARD 3
#define MAXSIDE 30
#define MAXMINE 99
#define MAXMOVE 801 //30 * 30 - 99

int side; //rozmiar pola, każde to kwadrat, więc starczy jedna zmienna
int mines;	//ilość min

//x = rząd, y = kolumna

//pokazuje akualną planszę gry
void showBoard(char myBoard[][MAXSIDE])
{
	int i, j;

	printf(" ");

	for (i = 0; i < side; i++)
		printf("% d", i);

	printf("\n\n");

	for (i = 0; i < side; i++)
	{
		printf("% d ", i);

		for (j = 0; j < side; j++)
			printf("%c ", myBoard[i][j]);

		printf("\n");
	}
}

//losowo rozstawia miny na planszy
void assignMine(int mine[][2], char realBoard[][MAXSIDE])
{
	bool mark[MAXSIDE * MAXSIDE];

	memset(mark, false, sizeof(mark));

	for (int i = 0; i < mines; )
	{
		int random = rand() % (side * side);
		int x = random / side;
		int y = random % side;

		if (mark[random] == false)
		{
			mine[i][0] = x;
			mine[i][1] = y;

			realBoard[mine[i][0]][mine[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}
}

//sprawda, czy podane pole znajduje się na planszy
bool isPlace(int x, int y)
{
	return (x >= 0) && (x < side) && (y >= 0) && (y < side);
}

//sprawdza, czy podane pole jest miną
bool isMine(int x, int y, char board[][MAXSIDE])
{
	if (board[x][y] == '*')
		return (true);
	else
		return (false);
}

//pozwala wykonać ruch
void makeMove(int* x, int* y)
{
	printf("Wprowadź swój ruch (rząd, kolumna)\n");
	scanf_s("%d %d", x, y);
}

//funkcja licząca, ile min jest obok wybranej przez gracza
int howManyMinesNextTo(int x, int y, int mine[][2], char realBoard[][MAXSIDE])
{
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
		if (isMine(x - 1, y + 1, realBoard) == true)
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
		if (isMine(x + 1, y + 1, realBoard) == true)
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

//funkcja inicjalizująca grę, tworząc losowo generowaną planszę i zaznacza wszystkie pola na planszy jako niewiadome
void preGame(char realBorad[][MAXSIDE], char myBoard[][MAXSIDE])
{
	srand(time(NULL));

	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			myBoard[i][j] = realBorad[i][j] = '-';
		}
	}
}

//główne menu
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
			printf("3. Trudny - 30 x 30\n");
			printf("4. Powrót\n\n");

			scanf_s("%d", &inB);

			if (inB == EASY)
			{
				system("cls");
				side = 8;
				mines = 20;
			}

			if (inB == INTERMEDIATE)
			{
				system("cls");
				side = 16;
				mines = 40;
			}

			if (inB == HARD)
			{
				system("cls");
				side = 30;
				mines = 99;
			}

			if (inB == 4)
			{
				break;
			}

			return;
			break;

		case 2:

			exit(0);
			break;
		}
	}
}

//przesuwa minę w wolne miejsce (żeby nie przegrać w pierwszym ruchu)
void moveMine(int x, int y, char board[][MAXSIDE])
{
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
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
bool playGameUntil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], int mine[][2], int x, int y, int* movesLeft)
{
	if (myBoard[x][y] != '-')
		return(false);

	int i;

	//odsłonięcie pola z miną
	if (realBoard[x][y] == '*')
	{
		myBoard[x][y] = '*';

		for (i = 0; i < mines; i++)
			myBoard[mine[i][0]][mine[i][1]] = '*';

		system("cls");
		showBoard(myBoard);
		printf("\nPrzegrałeś!\n");

		return(true);
	}

	else
	{
		//oblicza ilość min obok odsłoniętego pola, i wyświetla na planszy
		int count = howManyMinesNextTo(x, y, mine, realBoard);
		(*movesLeft)--;

		myBoard[x][y] = count + '0';

		if (!count)
		{
			//komórka na północ
			if (isPlace(x - 1, y) == true)
			{
				if (isMine(x - 1, y, realBoard) == false)
					playGameUntil(myBoard, realBoard, mine, x - 1, y, movesLeft);
			}

			//komórka na pólnocny-zachód
			if (isPlace(x - 1, y - 1) == true)
			{
				if (isMine(x - 1, y - 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mine, x - 1, y - 1, movesLeft);
			}

			//komórka na pólnocny-wschód
			if (isPlace(x - 1, y + 1) == true)
			{
				if (isMine(x - 1, y + 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mine, x - 1, y + 1, movesLeft);
			}

			//komórka na południe
			if (isPlace(x + 1, y) == true)
			{
				if (isMine(x + 1, y, realBoard) == false)
					playGameUntil(myBoard, realBoard, mine, x + 1, y, movesLeft);
			}

			//komórka na południowy-zachód
			if (isPlace(x + 1, y - 1) == true)
			{
				if (isMine(x + 1, y - 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mine, x + 1, y - 1, movesLeft);
			}

			//komórka na południowy-wschód
			if (isPlace(x + 1, y + 1) == true)
			{
				if (isMine(x + 1, y + 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mine, x + 1, y + 1, movesLeft);
			}

			//komórka na zachód
			if (isPlace(x, y - 1) == true)
			{
				if (isMine(x, y - 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mine, x, y - 1, movesLeft);
			}

			//komórka na wschód
			if (isPlace(x, y + 1) == true)
			{
				if (isMine(x, y + 1, realBoard) == false)
					playGameUntil(myBoard, realBoard, mine, x, y + 1, movesLeft);
			}
		}

		return(false);
	}
}

//gra w sapera
void playGame()
{
	showGameMenu();

	bool gameOver = false;

	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];

	int movesLeft = side * side - mines, x, y;
	int mine[MAXMINE][2];

	preGame(realBoard, myBoard);

	assignMine(mine, realBoard);

	//gra się do momentu wygranej/odkrycia miny

	int currentMoveCount = 0;

	while (gameOver == false)
	{
		system("cls");
		printf("Aktualny stan planszy: \n");
		showBoard(myBoard);
		makeMove(&x, &y);

		//zapewnia, że pierwszy ruch jest bezpieczny
		if (currentMoveCount == 0)
		{
			if (isMine(x, y, realBoard) == true)
				moveMine(x, y, realBoard);
		}

		currentMoveCount++;

		gameOver = playGameUntil(myBoard, realBoard, mine, x, y, &movesLeft);

		if ((gameOver == false) && (movesLeft == 0))
		{
			cout << "Wygrałeś!\n";
			gameOver = true;
		}
	}
}

int main()
{
	setlocale(LC_CTYPE, "Polish");

	playGame();

	return(0);
}