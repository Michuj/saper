#include<iostream>
#include<fstream>

using namespace std;

#define easy 0
#define intermediate 1
#define hard 2
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
void assignBomb(int mines[][2], char realBoard[][maxSide])
{
	bool mark[maxSide * maxSide];

	memset(mark, false, sizeof(mark));

	for (i = 0; i < MINES);
	{
		int random = rand() % (SIDE * SIDE);
		int x = random / SIDE;
		int y = random % side;
		if (mark[mark] == false)
		{
			mines[i][0] = x;
			mines[0][1] = y;

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

//pozwala zrobić ruch
void makeMove(int* x, int* y)
{
	printf("Wprowadź swój ruch (rząd, kolumna) ->  ");
	scanf_s("%d %d", x, y);
	return;
};

//funkcja licząca, ile komórek jest obok wybranej przez gracza
int howManyCells(int x, int y, int mines[][2], char realBoard[][maxSide])
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
}



//submenu do wybierania poziomu trudności 
void setDiff()
{
	int in; //input

	printf("\nWybierz poziom trudności:\n");
	printf("1. Łatwy - 8x8\n");
	printf("2. Średni - 16x16\n");
	printf("3. Trudny - 30 x 16\n");
	printf("4. Powrót\n\n");

	scanf_s("%d", &in);

	if (in == easy)
	{
		SIDE = 8;
		MINES = 20;
	}

	if (in == intermediate)
	{
		SIDE = 16;
		MINES = 40;
	}

	if (in == hard)
	{
		SIDE = 30;
		MINES = 99;
	}
	return;
}

//głowne menu
void showGameMenu()
{
	int in; //input
	while (1)
	{
		system("cls");
		cout << "-------------\n";
		cout << "--- SAPER ---\n";
		cout << "-------------\n\n";

		cout << "1. Zagraj w nową grę\n";
		//cout << "2. Wczytaj grę\n";
		cout << "2. Wyjdź\n\n";

		cin >> in;

		switch (in)
		{
		case 1:

			setDiff();

			break;

		case 2:

			exit(0);
			break;
		}
	}
}

int main()
{
	setlocale(LC_CTYPE, "Polish");

	showGameMenu();
}