// main.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Node.h"


#define DEBUG 1

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	int choice = 0, key = 0;
	Node rootNode;


	while (1)
	{
		while (1)// Цикл с пользовательским интерфейсом.
		{
			cout << "\n\nМеню:\n";
			cout << "-0-Выход из программы\n";
			cout << "-1-Добавление ключа в B-дерево\n";
			cout << "-2-Удаление ключа из B-дерева\n";
			cout << "-3-Поиск ключа в В-дереве\n";
			cout << "-4-Вывод B-дерева\n";
			cout << "Выберите действие из списка меню: ";
			cin >> choice;
			if (choice <= 4 && choice >= 0) break;
			cout << "Сделайте выбор из предполагаемого диапазона:\n";
		}

		switch (choice)
		{
		case 0: return 0;

		case 1:
			cout << "\nВведите целочисленный ключ который будет добавлен в B-дерево: ";
			cin >> key;
			if (rootNode.addKey(key)) cout << "\nКлюч успешно добавлен в B-дерево\n";
			else cout << "\nТакой ключ уже существует в В-дереве\n";
			break;

		case 2:
			cout << "\nВведите целочисленный ключ который будет удален из B-дерева: ";
			cin >> key;
			rootNode.remove(key);
			cout << "\nКлюч удален из B-дерева\n";
			break;

		case 3:
			cout << "\nВведите целочисленный ключ для поиска в B-дереве: ";
			cin >> key;
			if (rootNode.search(key)) cout << "\nТакой ключ существует в B-дереве\n";
			else cout << "\nТакого ключа не существует в В-дереве\n";
			break;

		case 4:
			ofstream fout;
			fout.open("B-tree.gv");
			rootNode.output(fout, &rootNode);
			cout << "\nДерево выведено в файл B-tree.gv в формате DOT.\n";
			break;
		}
	}
}
