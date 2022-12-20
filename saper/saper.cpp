#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std; 

int easy[8][8]; //20 min
int medium[16][16]; // 40 min
int hard[30][16]; //99 min

void showBoardE()
{
	cout << " 1 2 3 4 5 6 7 8\n";
	for (int i = 0; i < 8; i++)
	{
		cout << i + 1 << " ";
		for (int j = 0; j < 8; j++)
		{
		}
		cout << endl;
	}
}

void showBoardM()
{
	cout << " 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\n";
	for (int i = 0; i < 16; i++)
	{
		cout << i + 1 << " ";
		for (int j = 0; j < 16; j++)
		{
		}
		cout << endl;
	}
}

void showBoardH()
{
	cout << " 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30\n";
	for (int i = 0; i < 30; i++)
	{
		cout << i + 1 << " ";
		for (int j=0;j<30;j++)
		{
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_CTYPE, "Polish");

	int in, inB;

	while (1)
	{
		system("cls");
		cout << "-------------\n";
		cout << "--- SAPER ---\n";
		cout << "-------------\n" << endl;

		cout << "1. Zagraj w nową grę\n";
		cout << "2. Wczytaj grę\n";
		cout << "3. Wyjdź\n" << endl;
		cin >> in;

		switch (in)
		{
		case 1:
		
			system("cls");
				cout << "Wybierz poziom trudności:\n";
				cout << "1. Łatwy - 8x8\n";
				cout << "2. Średni - 16x16\n";
				cout << "3. Trudny - 30 x 16\n";
				cout << "4. Powrót\n" << endl;
				cin >> inB;

				switch (inB)
				{
				case 1:

					showBoardE();
					system("pause");
					cout << endl;
					break;

				case 2:

					showBoardM();
					system("pause");
					cout << endl;
					break;

				case 3:
					
					showBoardH();
					system("pause");
					cout << endl;
					break;

				case 4:

					break;
				}
			break;

		case 2:
		

			break;
		
		case 3:

			return 0;
			break;
		}
	}
}