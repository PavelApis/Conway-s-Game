#include <iostream>

using namespace std;

//константы задающие размеры поля
const unsigned int WIDTH = 17;
const unsigned int HEIGHT = 17;

char field[HEIGHT][WIDTH]{}; // массив символов соответствующий полю

//функция, очищающая массив поля и записывающая символ @ в граничные элементы поля. Все клетки будут жить в элементах массива от 1 до HEIGHT/WIDTH - 2
void createEmptyField() {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1)
				field[y][x] = '@';
			else field[y][x] = ' ';
		}
	}
}

//Функция принимающая числа x и y в качестве координаты и создающая клетки, соответсвутющие координатам поля, клеткам присуждается символ '0'.
void createCell(int x, int y) {
	if (x > 0 && x < WIDTH - 1 && HEIGHT - 1 - y > 0 && HEIGHT - 1 - y < HEIGHT)
		field[HEIGHT - 1 - y][x] = '0';
	else cout << "Wrong coordinates\n";
}

//Вывод поля на экран
void print() {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			cout << field[y][x];
			if (x == WIDTH - 1)
				cout << '\n';
		}
	}
}

//Функция вводящая все клетки, которые будут жить в поел после старта игры
void inputStartingCells() {
	int x, y;
	while (cin) {
		print();
		cout << "Enter the coordinates of cells (x, y) x from 1 to " << WIDTH - 2 << " y from 1 to " << HEIGHT - 2 << ".\n";

		while (true) {
			cin >> x >> y;
			if (std::cin.fail()) {
				cout << "Wrong value, try again!\n";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
			else if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT - 1) {
				createCell(x, y);
				break;
			}

			else {
				cout << "Wrong number, try again!\n";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
		}

		cout << "Do you want to create a new cell? y/n\n";
		char answer;
		while (true) {
			cin >> answer;
			if (std::cin.fail()) {
				cout << "Wrong value, try again!\n";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
			else if (answer == 'y' || answer == 'n') break;
			else {
				cout << "Wrong value, try again!\n";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
		}
		system("CLS");
		if (answer == 'n') break;
	}
}

//Функция определяющая клетки, которые должны родится в этом поколении.(условием этого является количество соседей, равное 3ем)
//Рождающимся клеткам дается метка 'n', так как они не являются соседями клеток из прошлого поколения
void createNewBornCells() {
	for (int i = 1; i < HEIGHT - 1; ++i) {
		for (int j = 1; j < WIDTH - 1; ++j) {
			if (field[i][j] != '0') {
				int numberOfNeighbors = 0;
				if (field[i - 1][j - 1] == '0') ++numberOfNeighbors;
				if (field[i][j - 1] == '0') ++numberOfNeighbors;
				if (field[i + 1][j - 1] == '0') ++numberOfNeighbors;
				if (field[i - 1][j] == '0') ++numberOfNeighbors;
				if (field[i + 1][j] == '0') ++numberOfNeighbors;
				if (field[i - 1][j + 1] == '0') ++numberOfNeighbors;
				if (field[i][j + 1] == '0') ++numberOfNeighbors;
				if (field[i + 1][j + 1] == '0') ++numberOfNeighbors;

				if (numberOfNeighbors == 3) field[i][j] = 'n';
			}
		}
	}
}

//Функция определяющая клетки, которые должны умереть в этом поколении (Условием этого является количество соседей не равное 2ум или 3ем)
//Умирающим клеткам дается метка 'd', чтобы очистить их, как пройдет поколение 
void dyingCells() {
	for (int i = 1; i < HEIGHT - 1; ++i) {
		for (int j = 1; j < WIDTH - 1; ++j) {

			if (field[i][j] == '0' || field[i][j] == 'd') {
				int numberOfNeighbors = 0;

				if (field[i - 1][j - 1] == '0' || field[i - 1][j - 1] == 'd') ++numberOfNeighbors;
				if (field[i][j - 1] == '0' || field[i][j - 1] == 'd') ++numberOfNeighbors;
				if (field[i + 1][j - 1] == '0' || field[i + 1][j - 1] == 'd') ++numberOfNeighbors;
				if (field[i - 1][j] == '0' || field[i - 1][j] == 'd') ++numberOfNeighbors;
				if (field[i + 1][j] == '0' || field[i + 1][j] == 'd') ++numberOfNeighbors;
				if (field[i - 1][j + 1] == '0' || field[i - 1][j + 1] == 'd') ++numberOfNeighbors;
				if (field[i][j + 1] == '0' || field[i][j + 1] == 'd') ++numberOfNeighbors;
				if (field[i + 1][j + 1] == '0' || field[i + 1][j + 1] == 'd') ++numberOfNeighbors;

				if (numberOfNeighbors != 3 && numberOfNeighbors != 2) field[i][j] = 'd';
			}
		}
	}
}

//Функция поколения, определяет родившиеся и умирающие клетки, далее превращает клетки с меткой 'n' в обычные клетки '0' и и стирает клетки 'd'
void generation() {
	bool changes = 0;
	createNewBornCells();
	dyingCells();
	for (int i = 1; i < HEIGHT - 1; ++i)
	{
		for (int j = 1; j < WIDTH - 1; ++j)
		{
			if (field[i][j] == 'n')
			{
				field[i][j] = '0';
				changes = 1;
			}
			if (field[i][j] == 'd')
			{
				field[i][j] = ' ';
				changes = 1;
			}
		}
	}
}

//Контроль перехода к следующему поколению, для этого требуется ввести 'n', для перезапуска игры требуется ввести 'r', также выхода из игры, для этого требуется ввести 'e'
bool control() {
	char stick;
	cout << "Enter a \"n\" for next generation;\nEnter a \"r\" for restart the programm;\nEnter a \"e\" for close the programm;\n ";

	while (true) {
		cin >> stick;
		if (std::cin.fail()) {
			cout << "Wrong value, try again!\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else if (stick == 'n' || stick == 'e' || stick == 'r') {
			break;
			cin.clear();
		
		}
		else {
			cout << "Wrong value, try again!\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
	}

	if (stick == 'n') return 1;
	else if (stick == 'r') {
		system("CLS");
		createEmptyField();
		inputStartingCells();
		return 1;
	}
	else if (stick == 'e') return 0;
}

//Игра: создаем пустое поле, вводим координаты начальных клеток, переходим к следующим поколениям вводя 'n', как понадобится, для закрытия игры требуется нажать 'e';
int main()
{
	createEmptyField();
	inputStartingCells();
	bool game = 1;
	while (game) {
		print();
		generation();
		game = control();
		system("CLS");
	}
}
