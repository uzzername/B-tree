// main.cpp: ���������� ����� ����� ��� ����������� ����������.
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
		while (1)// ���� � ���������������� �����������.
		{
			cout << "\n\n����:\n";
			cout << "-0-����� �� ���������\n";
			cout << "-1-���������� ����� � B-������\n";
			cout << "-2-�������� ����� �� B-������\n";
			cout << "-3-����� ����� � �-������\n";
			cout << "-4-����� B-������\n";
			cout << "�������� �������� �� ������ ����: ";
			cin >> choice;
			if (choice <= 4 && choice >= 0) break;
			cout << "�������� ����� �� ��������������� ���������:\n";
		}

		switch (choice)
		{
		case 0: return 0;

		case 1:
			cout << "\n������� ������������� ���� ������� ����� �������� � B-������: ";
			cin >> key;
			if (rootNode.addKey(key)) cout << "\n���� ������� �������� � B-������\n";
			else cout << "\n����� ���� ��� ���������� � �-������\n";
			break;

		case 2:
			cout << "\n������� ������������� ���� ������� ����� ������ �� B-������: ";
			cin >> key;
			rootNode.remove(key);
			cout << "\n���� ������ �� B-������\n";
			break;

		case 3:
			cout << "\n������� ������������� ���� ��� ������ � B-������: ";
			cin >> key;
			if (rootNode.search(key)) cout << "\n����� ���� ���������� � B-������\n";
			else cout << "\n������ ����� �� ���������� � �-������\n";
			break;

		case 4:
			ofstream fout;
			fout.open("B-tree.gv");
			rootNode.output(fout, &rootNode);
			cout << "\n������ �������� � ���� B-tree.gv � ������� DOT.\n";
			break;
		}
	}
}
