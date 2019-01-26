/* Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N. 
Требуется построить бинарное дерево, заданное наивным порядком вставки. Т.е., 
при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root;
иначе в левое поддерево root. Выведите элементы в порядке in-order (слева направо).*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

template <typename MyNodeT>
struct MyNode
{
	MyNodeT key=0;
	MyNode *left=nullptr;
	MyNode *right=nullptr;
	MyNode *parent=nullptr;
	MyNode()
	{}
	MyNode(MyNodeT keys): key(keys), left(nullptr), right(nullptr), parent(nullptr)
	{}
	MyNode(MyNodeT keys, MyNode *par): key(keys), left(nullptr), right(nullptr), parent(par)
	{}
	~MyNode()
	{}
};

template <typename MyTreeT>
class MyTree {
private:
	MyNode<MyTreeT> *root=nullptr;
	MyNode<MyTreeT> *first_elem;
	MyNode<MyTreeT> *new_node;
public:
	MyTree(): root(nullptr)
	{}
	MyTree(std::vector<MyTreeT> &vect)
	{

		first_elem = new MyNode<MyTreeT>(vect[0]);
		root = first_elem;
		for (int i = 1; i < vect.size(); ++i)
		{
			new_node = new MyNode<MyTreeT>(vect[i]);
			AddElem(first_elem, new_node); 
		}
	}
	~MyTree()
	{
		DeletingTree(first_elem);

	}
	void AddElem(MyNode<MyTreeT> *current_node ,MyNode<MyTreeT> *new_node)
	{
		while (current_node != nullptr)
		{
			if (new_node->key < current_node->key)
			{
				if (current_node->left != nullptr)
				{
					current_node = current_node->left;
				}
				else {
					new_node->parent = current_node;
					current_node->left = new_node;
					break;
				}
			}
			else {
				
				if (new_node->key > current_node->key)
				{
					if (current_node->right != nullptr)
					{
						current_node = current_node->right;
					}
					else {
						new_node->parent = current_node;  
						current_node->right = new_node;
						break;
					}
				}
			}
		}
	}

	void DFSAndPrint(MyNode<MyTreeT> *current)
	{

		if (current == nullptr)
		{
			return;
		}
		DFSAndPrint(current->left);

		std::cout << current->key<<" ";

		DFSAndPrint(current->right);

	}

	void PrintTree()
	{
		MyNode<MyTreeT> *current = root;
		DFSAndPrint(current);
	}

	void DeletingTree(MyNode<MyTreeT> *for_delete)
	{
		if (for_delete != nullptr)
		{
			DeletingTree(for_delete->left);
			DeletingTree(for_delete->right);
			delete for_delete;
		}
	}

};


int main()
{
	int n = 0;
	std::cin >> n;
	std::vector<int> vect(n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> vect[i];
	}

	MyTree<int> tree(vect);

	tree.PrintTree();


	return 0;
}
