// Описание методов класса Node.

#include "stdafx.h"
#include "Node.h"

using namespace std;

void Node::divide()// Функцияя разделяющая полный узел (2Т-1 элементов) пополам  на 2 новых относительно элемента в середине (Т-ый элемент) и перенос срединного элемента в родительский узел ( создается новый корневой узел если исходный так же был корневым).
{
	Node *lNode, *rNode;
	int key;

	if (parent == NULL)// Если узел является корневым.
	{
		lNode = new Node;
		rNode = new Node;
		if (this->subTree.size() == 0) // Если корневой узел не содержит поддеревьев.
		{
			for (int i = 0; i < T - 1; i++)
			{
				lNode->keys.push_back(this->keys[i]);
				rNode->keys.insert(rNode->keys.begin(), this->keys[2*T - 2 - i]);
			}
		}
		else
		{
			for (int i = 0; i < T - 1; i++)
			{
				lNode->subTree.push_back(this->subTree[i]);
				this->subTree[i]->parent = lNode;
				lNode->keys.push_back(this->keys[i]);
				rNode->subTree.insert(rNode->subTree.begin(), this->subTree[2 * T - 1 - i]);
				this->subTree[2 * T - 1 - i]->parent = rNode;
				rNode->keys.insert(rNode->keys.begin(), this->keys[2 * T - 2 - i]);
			}

			lNode->subTree.push_back(this->subTree[T - 1]);
			this->subTree[T - 1]->parent = lNode;
			rNode->subTree.insert(rNode->subTree.begin(), this->subTree[T]);
			this->subTree[T]->parent = rNode;
		}

		lNode->parent = this;
		rNode->parent = this;

		key = this->keys[T - 1];
		this->subTree.resize(0);
		this->subTree.push_back(lNode);
		this->subTree.push_back(rNode);
		this->keys.resize(0);
		this->keys.push_back(key);
	}
	else
	{
		if (this->subTree.size() == 0)// Если узел является листом.
		{
			rNode = new Node;
			vector<int>::iterator it;
			vector<Node*>::iterator itN;

			for (int i = 0; i < T - 1; i++) // Копируем правую часть исходного узла в новый узел.
			{
				rNode->keys.insert(rNode->keys.begin(), this->keys[2 * T - 2 - i]);
			}

			key = this->keys[T - 1]; // Присваиваем значению key значение серединного ключа.

			this->keys.resize(T - 1); // Обрезаем исходный узел оставляя лишь левую часть.

			it = this->parent->keys.begin();
			itN = this->parent->subTree.begin();

			while (it != this->parent->keys.end()) // Находим место в родительском узле исходного узла место куда вставить серединный элемент и указатели на левый и правый узел.
			{
				if (*it < key) break;
				++it;
				++itN;
			}

			rNode->parent = this->parent;
			this->parent->keys.insert(it, key);
			this->parent->subTree.insert(itN + 1, rNode);

			
		}
		else // Узел не корневой и не лист.
		{

			rNode = new Node;
			vector<int>::iterator it;
			vector<Node*>::iterator itN;

			for (int i = 0; i < T - 1; i++) // Копируем правую часть исходного узла в новый узел.
			{
				rNode->subTree.insert(rNode->subTree.begin(), this->subTree[2 * T - 2 - i]);
				rNode->keys.insert(rNode->keys.begin(), this->keys[2 * T - 1 - i]);
			}
			rNode->subTree.insert(rNode->subTree.begin(), this->subTree[T]);

			key = this->keys[T - 1]; // Присваиваем значению key значение серединного узла.

			this->subTree.resize(T); // Обрезаем исходный узел оставляя лишь левую часть.
			this->keys.resize(T - 1);

			it = this->parent->keys.begin();
			itN = this->parent->subTree.begin();

			while (it != this->parent->keys.end()) // Находим место в родительском узле исходного узла место куда вставить серединный элемент и указатели на левый и правый узел.
			{
				if (*it < key) break;
				++it;
				++itN;
			}

			rNode->parent = this->parent;

			this->parent->keys.insert(it , key);
			this->parent->subTree.insert(itN + 1 , rNode);
		}
	}
}

Node* Node::balance() // Рекурсивная функция балансировки узла.
{
	vector<int>::iterator it;
	if (this->parent != NULL) // Если узел не корневой.
	{
		it = this->parent->keys.begin();
		for (vector<Node*>::iterator itN = this->parent->subTree.begin(); itN != this->parent->subTree.end(); ++itN) // Обходит родительский узел поддеревьев в поисках интератора с указателем на принятый фнкцией узел.
		{
			if (*itN == this) // Нашли итератор.
			{
				if (itN + 1 != this->parent->subTree.end() && (*(itN + 1))->keys.size() > T - 1) // Если сосед справа имеет более Т-1 элементов. 
				{
					this->keys.push_back(*it);
					*it = (*(itN + 1))->keys[0];
					this->subTree.push_back((*(itN + 1))->subTree[0]);
					(*(itN + 1))->remove(*((*(itN + 1))->keys.begin()));
					(*(itN + 1))->subTree.erase((*(itN + 1))->subTree.begin());
				}
				else
				{
					if (itN != this->parent->subTree.begin() && (*(itN - 1))->keys.size() > T - 1) //Если сосед слева имеет более Т - 1 элементов.
					{
						this->keys.insert(this->keys.begin() ,*it);
						*it = *(*(itN - 1))->keys.end();
						this->subTree.insert(this->subTree.begin() ,*(*(itN - 1))->subTree.end());
						(*(itN - 1))->remove(*((*(itN - 1))->keys.end()));
						(*(itN - 1))->subTree.erase((*(itN - 1))->subTree.end());
					}
					else // Существующие соседи имеют T-1 ключей.
					{
						if (this->parent->keys.size() != 1)
						{
							if (itN != this->parent->subTree.begin())
							{
								this->keys.insert(this->keys.begin(), *(it - 1));
								this->keys.insert(this->keys.begin(), (*itN - 1)->keys.begin(), (*itN - 1)->keys.end());
								this->subTree.insert(this->subTree.begin(), (*itN - 1)->subTree.begin(), (*itN - 1)->subTree.end());
								this->parent->keys.erase(it - 1);
								(*(itN - 1))->~Node();
								this->parent->subTree.erase(itN - 1);
								if (this->parent->keys.size() < T - 1) this->parent->balance();
							}
							else
							{
								this->keys.push_back(*(it));
								this->keys.insert(this->keys.end(), (*itN + 1)->keys.begin(), (*itN + 1)->keys.end());
								this->subTree.insert(this->subTree.end(), (*itN + 1)->subTree.begin(), (*itN + 1)->subTree.end());
								this->parent->keys.erase(it);
								(*(itN + 1))->~Node();
								this->parent->subTree.erase(itN + 1);
								if (this->parent->keys.size() < T - 1) this->parent->balance();
							}
						}
						else
						{
							this->parent->balance();
						}
					}
				}
				break;
			}
			it++;
		}
	}
	else
	{
		if (this->keys.size() == 1)
		{
			this->keys.insert(this->keys.begin(), (this->subTree[0])->keys.begin(), (this->subTree[0])->keys.end());
			this->keys.insert(this->keys.end(), (this->subTree[1])->keys.begin(), (this->subTree[1])->keys.end());
			if ((this->subTree[0])->subTree.size() != 0) this->subTree.insert(this->subTree.end(), (this->subTree[0])->subTree.begin(), (this->subTree[0])->subTree.end());
			if ((this->subTree[1])->subTree.size() != 0) this->subTree.insert(this->subTree.end(), (this->subTree[1])->subTree.begin(), (this->subTree[1])->subTree.end());
			this->subTree[0]->~Node();
			this->subTree[1]->~Node();
			this->subTree.erase(this->subTree.begin());
			this->subTree.erase(this->subTree.begin());
		}
	}
	return this;
}

// Открытые методы

bool Node::addKey(int key)// Рекурсивная функция добавления элемента в В-дерево.
{
	if (this->keys.size() == 2 * T - 1)// Если функция вызвана для полного узла он разбивается и функция перевызывается для его родителя, если это не кореневой узел( если корневой то вызывается для самого себя).
	{
		this->divide();
		if (this->parent != NULL) return this->parent->addKey(key);
		else return this->addKey(key);
	}
	else // Если узел не полный
	{
		if (this->subTree.size() == 0) // Проверка на пустоту поддерева. Неполный узел с пустым поддеревом - искомый нами лист для добавления ключа.
		{
			for (vector<int>::iterator it = this->keys.begin(); it != this->keys.end() ; ++it)
			{
				if (this->keys.size() == 0)
				{
					this->keys.push_back(key);
					return true;
				}
				if ((*it) == key) return false;
				if ((*it) < key)
				{
					this->keys.insert(it, key);
					return true;
				}
			}
			this->keys.push_back(key);
			return true;
		}
		else // Для неполного узла с непустым поддеревом, функция перевызывается для дочернего узла между ключами больше и меньше ключа который мы хотим добавить.
		{
			vector<Node*>::iterator itN = this->subTree.begin();
			for (vector<int>::iterator it = this->keys.begin() ; it != this->keys.end(); it++)
			{
				if (*it == key) return false;
				if (*it < key)
				{
					return (*itN)->addKey(key);
				}
				itN++;
			}
			return (*(this->subTree.end() - 1))->addKey(key);
		}
	}
}


void  Node::remove(int key) // Рекурсивная функция удаления ключа из В-дерева.
{
	vector<int>::iterator it;
	vector<Node*>::iterator itN;

	if (this->subTree.size() == 0)// Если узел является листом.
	{
		if (this->keys.size() > T - 1 || this->parent == NULL)// Если длина листа более T-1 или лист корневой.
		{
			for (vector<int>::iterator it = this->keys.begin(); it != this->keys.end(); it++)
			{
				if (*it == key)
				{
					this->keys.erase(it);
					break;
				}
			}
			
		}
		else // Длина листа Т-1 и лист не корневой.
		{
			it = this->parent->keys.begin();

			for (itN = this->parent->subTree.begin(); itN != this->parent->subTree.end(); itN++) // Обходим родительский узел в поисках позиции исходного узла.
			{
				if (*itN == this) // Нашли исходный узел.
				{
					for (vector<int>::iterator it1 = this->keys.begin(); it1 != this->keys.end(); it1++) //Обходим исходный узел в поисках ключа для удаления.
					{
						if (*it1 == key)
						{
							if ( (itN+1) != this->parent->subTree.end() && (*(itN + 1))->keys.size() > T - 1) // Если соседний справа узел длины более T-1.
							{
								this->keys.erase(it1);
								this->keys.push_back(*it);
								*it = (*(itN + 1))->keys[0];
								(*(itN + 1))->keys.erase((*(itN + 1))->keys.begin());
								return;
							}
							else
							{
								if (itN != this->parent->subTree.begin() && (*(itN - 1))->keys.size() > T - 1) // Если соседний слева узел длины более T-1.
								{
									this->keys.erase(it1);
									this->keys.insert(this->keys.begin(), *(it - 1));
									*(it - 1) = *((*(itN - 1))->keys.end());
									(*(itN - 1))->keys.erase((*(itN - 1))->keys.end());
									return;
								}
								else // Соседние листы длиной T-1.
								{
									if (this->parent->parent == NULL && this->parent->keys.size() == 1)
									{
										this->parent->balance()->remove(key);
									}
									else
									{
										this->keys.erase(it1);
										if ((itN + 1) != this->parent->subTree.end())
										{
											this->keys.push_back(*it);
											this->parent->keys.erase(it);
											this->keys.insert(this->keys.end(), (*(itN + 1))->keys.begin(), (*(itN + 1))->keys.end());
											(*(itN + 1))->~Node();
											this->parent->subTree.erase(itN + 1);
										}
										else
										{
											this->keys.insert(this->keys.begin(), *(it - 1));
											this->parent->keys.erase(it - 1);
											this->keys.insert(this->keys.begin(), (*(itN - 1))->keys.begin(), (*(itN - 1))->keys.end());
											(*(itN - 1))->~Node();
											this->parent->subTree.erase(itN - 1);
										}
										if (this->parent->keys.size() < T - 1 && this->parent->parent != NULL) this->parent->balance();
									}
									return;
								}
							}
							break;
						}
					}	
				}
				if (it != this->parent->keys.end()) it++;
			}
		}
	}
	else // Узел не лист.
	{
		it = this->keys.begin();
		for (itN = this->subTree.begin(); itN != this->subTree.end(); itN++)
		{
			if (it != this->keys.end() && *it == key)
			{
				if ((*itN)->keys.size() > T - 1)
				{
					*it = *((*itN)->keys.end() - 1); // тута возможно просто через переменную передать
					(*itN)->remove(*((*itN)->keys.end() - 1));
					return;
				}
				else
				{
					if ((*(itN + 1))->keys.size() > T - 1)
					{
						*it = *((*(itN+1))->keys.begin());
						(*(itN+1))->remove(*(*(itN+1))->keys.begin());
						return;
					}
					else
					{
						if (this->parent == NULL) // Если узел корневой.
						{
							if (this->keys.size() == 1)
							{
								this->balance();
								this->remove(key);
							}
							else
							{
								(*itN)->keys.push_back(key);
								(*itN)->keys.insert((*itN)->keys.end(), (*(itN+1))->keys.begin() , (*(itN + 1))->keys.end());
								if ((*(itN+1))->subTree.size() != 0 ) (*itN)->subTree.insert((*itN)->subTree.end(), (*(itN + 1))->subTree.begin(), (*(itN + 1))->subTree.end());
								(*(itN + 1))->~Node();
								this->subTree.erase(itN + 1);
								this->keys.erase(it);
								(*(itN))->remove(key);
							}
						}
						else // Узел не корневой.
						{
							(*itN)->keys.push_back(key);
							(*itN)->keys.insert((*itN)->keys.end(), (*(itN + 1))->keys.begin(), (*(itN + 1))->keys.end());
							if ((*(itN + 1))->subTree.size() != 0) (*itN)->subTree.insert((*itN)->subTree.end(), (*(itN + 1))->subTree.begin(), (*(itN + 1))->subTree.end());
							(*(itN + 1))->~Node();
							this->subTree.erase(itN + 1);
							this->keys.erase(it);
							(*(itN))->remove(key);
							if (this->keys.size() < T - 1) this->balance();
						}
					}
				}
				return;
			}
			else if (it != this->keys.end() && *it < key)
			{
				(*itN)->remove(key);
				return;
			}
			if (it != this->keys.end()) it++;
		}
		(*(this->subTree.end() - 1))->remove(key);
	}
}


bool Node::search(int key) // Рекурсивный поиск ключа в B-дереве.
{
	if (this->subTree.size() != 0)
	{
		for (unsigned int i = 0; i < this->keys.size(); i++)
		{
			if (this->keys[i] == key) return true;
			if (this->keys[i] < key) return this->subTree[i]->search(key);

		}
		return (this->subTree[this->keys.size()])->search(key);
	}
	else
	{
		for (unsigned int i = 0; i < this->keys.size(); i++) 
		{
			if (this->keys[i] == key) return true;
		}
		return false;
	}
}


void Node::output(ofstream &fout, Node* node)
{
	if (node->parent == NULL)
	{
		fout << "digraph Btree {" << endl;
		for (unsigned int i = 0; i < node->keys.size(); i++)
		{
			fout << "o" << node->keys[i];
		}
		fout << "o;" << endl;
		for (vector<Node*>::iterator itN = node->subTree.begin(); itN != node->subTree.end(); itN++)
		{
			(*itN)->output(fout, *itN);
		}
		fout << "}" << endl;
		fout.close();
	}
	else
	{
		if (node->subTree.size() == 0)
		{
			for (unsigned int i = 0; i < node->keys.size(); i++)
			{
				fout << "o" << node->keys[i];
			}
			fout << "o;" << endl;
			for (vector<int>::iterator it = node->parent->keys.begin(); it != node->parent->keys.end(); it++)
			{
				fout << "o" << *it;
			}
			fout << "o -> ";
			for (unsigned int i = 0; i < node->keys.size(); i++)
			{
				fout << "o" << node->keys[i];
			}
			fout << "o;" << endl;
		}
		else
		{
			for (unsigned int i = 0; i < node->keys.size(); i++)
			{
				fout << "o" << node->keys[i];
			}
			fout << "o;" << endl;
			for (vector<int>::iterator it = node->parent->keys.begin(); it != node->parent->keys.end(); it++)
			{
				fout << "o" << *it;
			}
			fout << "o -> ";
			for (unsigned int i = 0; i < node->keys.size(); i++)
			{
				fout << "o" << node->keys[i];
			}
			fout << "o;" << endl;
			for (vector<Node*>::iterator itN = node->subTree.begin(); itN != node->subTree.end(); itN++)
			{
				(*itN)->output(fout, *itN);
			}
		}
	}

}

