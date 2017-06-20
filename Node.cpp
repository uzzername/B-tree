// �������� ������� ������ Node.

#include "stdafx.h"
#include "Node.h"

using namespace std;

void Node::divide()// �������� ����������� ������ ���� (2�-1 ���������) �������  �� 2 ����� ������������ �������� � �������� (�-�� �������) � ������� ���������� �������� � ������������ ���� ( ��������� ����� �������� ���� ���� �������� ��� �� ��� ��������).
{
	Node *lNode, *rNode;
	int key;

	if (parent == NULL)// ���� ���� �������� ��������.
	{
		lNode = new Node;
		rNode = new Node;
		if (this->subTree.size() == 0) // ���� �������� ���� �� �������� �����������.
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
		if (this->subTree.size() == 0)// ���� ���� �������� ������.
		{
			rNode = new Node;
			vector<int>::iterator it;
			vector<Node*>::iterator itN;

			for (int i = 0; i < T - 1; i++) // �������� ������ ����� ��������� ���� � ����� ����.
			{
				rNode->keys.insert(rNode->keys.begin(), this->keys[2 * T - 2 - i]);
			}

			key = this->keys[T - 1]; // ����������� �������� key �������� ����������� �����.

			this->keys.resize(T - 1); // �������� �������� ���� �������� ���� ����� �����.

			it = this->parent->keys.begin();
			itN = this->parent->subTree.begin();

			while (it != this->parent->keys.end()) // ������� ����� � ������������ ���� ��������� ���� ����� ���� �������� ���������� ������� � ��������� �� ����� � ������ ����.
			{
				if (*it < key) break;
				++it;
				++itN;
			}

			rNode->parent = this->parent;
			this->parent->keys.insert(it, key);
			this->parent->subTree.insert(itN + 1, rNode);

			
		}
		else // ���� �� �������� � �� ����.
		{

			rNode = new Node;
			vector<int>::iterator it;
			vector<Node*>::iterator itN;

			for (int i = 0; i < T - 1; i++) // �������� ������ ����� ��������� ���� � ����� ����.
			{
				rNode->subTree.insert(rNode->subTree.begin(), this->subTree[2 * T - 2 - i]);
				rNode->keys.insert(rNode->keys.begin(), this->keys[2 * T - 1 - i]);
			}
			rNode->subTree.insert(rNode->subTree.begin(), this->subTree[T]);

			key = this->keys[T - 1]; // ����������� �������� key �������� ����������� ����.

			this->subTree.resize(T); // �������� �������� ���� �������� ���� ����� �����.
			this->keys.resize(T - 1);

			it = this->parent->keys.begin();
			itN = this->parent->subTree.begin();

			while (it != this->parent->keys.end()) // ������� ����� � ������������ ���� ��������� ���� ����� ���� �������� ���������� ������� � ��������� �� ����� � ������ ����.
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

Node* Node::balance() // ����������� ������� ������������ ����.
{
	vector<int>::iterator it;
	if (this->parent != NULL) // ���� ���� �� ��������.
	{
		it = this->parent->keys.begin();
		for (vector<Node*>::iterator itN = this->parent->subTree.begin(); itN != this->parent->subTree.end(); ++itN) // ������� ������������ ���� ����������� � ������� ���������� � ���������� �� �������� ������� ����.
		{
			if (*itN == this) // ����� ��������.
			{
				if (itN + 1 != this->parent->subTree.end() && (*(itN + 1))->keys.size() > T - 1) // ���� ����� ������ ����� ����� �-1 ���������. 
				{
					this->keys.push_back(*it);
					*it = (*(itN + 1))->keys[0];
					this->subTree.push_back((*(itN + 1))->subTree[0]);
					(*(itN + 1))->remove(*((*(itN + 1))->keys.begin()));
					(*(itN + 1))->subTree.erase((*(itN + 1))->subTree.begin());
				}
				else
				{
					if (itN != this->parent->subTree.begin() && (*(itN - 1))->keys.size() > T - 1) //���� ����� ����� ����� ����� � - 1 ���������.
					{
						this->keys.insert(this->keys.begin() ,*it);
						*it = *(*(itN - 1))->keys.end();
						this->subTree.insert(this->subTree.begin() ,*(*(itN - 1))->subTree.end());
						(*(itN - 1))->remove(*((*(itN - 1))->keys.end()));
						(*(itN - 1))->subTree.erase((*(itN - 1))->subTree.end());
					}
					else // ������������ ������ ����� T-1 ������.
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

// �������� ������

bool Node::addKey(int key)// ����������� ������� ���������� �������� � �-������.
{
	if (this->keys.size() == 2 * T - 1)// ���� ������� ������� ��� ������� ���� �� ����������� � ������� �������������� ��� ��� ��������, ���� ��� �� ��������� ����( ���� �������� �� ���������� ��� ������ ����).
	{
		this->divide();
		if (this->parent != NULL) return this->parent->addKey(key);
		else return this->addKey(key);
	}
	else // ���� ���� �� ������
	{
		if (this->subTree.size() == 0) // �������� �� ������� ���������. �������� ���� � ������ ���������� - ������� ���� ���� ��� ���������� �����.
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
		else // ��� ��������� ���� � �������� ����������, ������� �������������� ��� ��������� ���� ����� ������� ������ � ������ ����� ������� �� ����� ��������.
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


void  Node::remove(int key) // ����������� ������� �������� ����� �� �-������.
{
	vector<int>::iterator it;
	vector<Node*>::iterator itN;

	if (this->subTree.size() == 0)// ���� ���� �������� ������.
	{
		if (this->keys.size() > T - 1 || this->parent == NULL)// ���� ����� ����� ����� T-1 ��� ���� ��������.
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
		else // ����� ����� �-1 � ���� �� ��������.
		{
			it = this->parent->keys.begin();

			for (itN = this->parent->subTree.begin(); itN != this->parent->subTree.end(); itN++) // ������� ������������ ���� � ������� ������� ��������� ����.
			{
				if (*itN == this) // ����� �������� ����.
				{
					for (vector<int>::iterator it1 = this->keys.begin(); it1 != this->keys.end(); it1++) //������� �������� ���� � ������� ����� ��� ��������.
					{
						if (*it1 == key)
						{
							if ( (itN+1) != this->parent->subTree.end() && (*(itN + 1))->keys.size() > T - 1) // ���� �������� ������ ���� ����� ����� T-1.
							{
								this->keys.erase(it1);
								this->keys.push_back(*it);
								*it = (*(itN + 1))->keys[0];
								(*(itN + 1))->keys.erase((*(itN + 1))->keys.begin());
								return;
							}
							else
							{
								if (itN != this->parent->subTree.begin() && (*(itN - 1))->keys.size() > T - 1) // ���� �������� ����� ���� ����� ����� T-1.
								{
									this->keys.erase(it1);
									this->keys.insert(this->keys.begin(), *(it - 1));
									*(it - 1) = *((*(itN - 1))->keys.end());
									(*(itN - 1))->keys.erase((*(itN - 1))->keys.end());
									return;
								}
								else // �������� ����� ������ T-1.
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
	else // ���� �� ����.
	{
		it = this->keys.begin();
		for (itN = this->subTree.begin(); itN != this->subTree.end(); itN++)
		{
			if (it != this->keys.end() && *it == key)
			{
				if ((*itN)->keys.size() > T - 1)
				{
					*it = *((*itN)->keys.end() - 1); // ���� �������� ������ ����� ���������� ��������
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
						if (this->parent == NULL) // ���� ���� ��������.
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
						else // ���� �� ��������.
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


bool Node::search(int key) // ����������� ����� ����� � B-������.
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

