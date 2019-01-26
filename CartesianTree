#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <string>
#include <cstring>
#include <stack>

template<typename Key_T, typename Priority_T>
struct MyTreapNode {
	std::pair<Key_T, Priority_T> key_and_priority;
	MyTreapNode *parent;
	MyTreapNode *left;
	MyTreapNode *right;
	MyTreapNode(): parent(nullptr), left(nullptr), right(nullptr)
	{}
	MyTreapNode(std::pair<Key_T, Priority_T> para): key_and_priority(para), parent(nullptr), left(nullptr), right(nullptr)
	{}
	~MyTreapNode()
	{}
};

template<typename Key_TT, typename Priority_TT>
class MyTreap
{
private:
	MyTreapNode<Key_TT, Priority_TT> *root=nullptr;
	MyTreapNode<Key_TT, Priority_TT> *first_element;
	MyTreapNode<Key_TT, Priority_TT> *new_elem;
public:
	MyTreap(): root(nullptr)
	{}

	MyTreap(std::vector<std::pair<Key_TT, Priority_TT> > &vect)
	{
		first_element = new MyTreapNode<Key_TT, Priority_TT>(vect[0]);
		root = first_element;  
		for (int i = 1; i < vect.size(); ++i) ///
		{
			new_elem= new MyTreapNode<Key_TT, Priority_TT>(vect[i]);
			AddNewElem(new_elem);  
		}
	}

	~MyTreap()
	{
		DeletingTreap(root);
	}

	void Split(Key_TT key, MyTreapNode<Key_TT, Priority_TT> *current, MyTreapNode<Key_TT, Priority_TT>*& left, MyTreapNode<Key_TT, Priority_TT>*& right)
	{
		if (current == nullptr)
		{
			left = nullptr;
			right = nullptr;
			return;
		}
		if (current->key_and_priority.first <= key) 
		{
			Split(key, current->right, current->right, right);
			left = current;
			return;
		}

		Split(key, current->left, left, current->left);  
		right = current;

		return;
	}

	void AddNewElem(MyTreapNode<Key_TT, Priority_TT> *new_elem)
	{
		if (root == nullptr)
		{
			root = new_elem;
			return;
		}
		
		MyTreapNode<Key_TT, Priority_TT> *previous;
		MyTreapNode<Key_TT, Priority_TT> *cur;

		previous = root;
		cur = root;

		while ((cur!=nullptr)&&(cur->key_and_priority.second >= new_elem->key_and_priority.second))
		{
			previous = cur;
			if (new_elem->key_and_priority.first <= cur->key_and_priority.first)
			{
				cur = cur->left;
			}
			else
			{
				cur = cur->right;
			}
		}

		Split(new_elem->key_and_priority.first, cur, new_elem->left, new_elem->right);



		if (cur == root)
		{
			root = new_elem; 
		}
		else
		{
			if (new_elem->key_and_priority.first <= previous->key_and_priority.first) { ///���� ��� <
				previous->left = new_elem;
			}
			else
			{
				previous->right = new_elem;
			}
		}


	}

	void DeletingTreap(MyTreapNode<Key_TT, Priority_TT> *for_delete)
	{
		if (for_delete != nullptr) {
		
		}
		if (for_delete != nullptr)
		{
			DeletingTreap(for_delete->left);
			DeletingTreap(for_delete->right);
			delete for_delete;
		}
	}


	int GetMaxDepth(MyTreapNode<Key_TT, Priority_TT> *node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		std::stack<int> depth;
		std::stack<MyTreapNode<Key_TT, Priority_TT> *> st;
		int max_depth = 0;
		int current_depth = 0;

		while (true)
		{
			++current_depth;
			if (node->left != nullptr)
			{
				if (node->right != nullptr)
				{
					st.push(node->right);
					depth.push(current_depth);
				}
				node = node->left;
			}
			else
			{
				if (node->right != nullptr)
				{
					node = node->right;
				}
				else
				{
					if (current_depth > max_depth)
					{
						max_depth = current_depth;
					}
					if (st.empty())
					{
						break;
					}
					current_depth = depth.top();
					depth.pop();
					node = st.top();
					st.pop();
				}
			}

		}
		return max_depth;
	}

	int GetDepth()
	{
		return GetMaxDepth(root);
	}

	void DFSAndPrint(MyTreapNode<Key_TT, Priority_TT> *current) //print
	{

		if (current == nullptr)
		{
			return;
		}
		DFSAndPrint(current->left);

		std::cout <<"|"<< current->key_and_priority.first << " "<<current->key_and_priority.second<<"|";

		DFSAndPrint(current->right);

	}

	void PrintTree() //print
	{
		MyTreapNode<Key_TT, Priority_TT> *current = root;
		DFSAndPrint(current);
	}

	void BFSANdPrint(MyTreapNode<Key_TT, Priority_TT> *current)
	{
		std::queue<MyTreapNode<Key_TT, Priority_TT> *> q;
		q.push(current);
		while (!q.empty())
		{
			MyTreapNode<Key_TT, Priority_TT> * node = q.front();
			q.pop();
			std::cout<<"|"<< node->key_and_priority.first << " " << node->key_and_priority.second << "|"<<std::endl;
			if (node->left!=nullptr)
			{
				q.push(node->left);
			}
			if (node->right != nullptr)
			{
				q.push(node->right);
			}
		}
	}

	void PrintTree2()
	{
		BFSANdPrint(root);
	}
};



//-------------------------------------------------------------------------------------------------------------------------------------------------------//

template <typename MyNodeT>
struct MyNode
{
	MyNodeT key = 0;
	MyNode *left = nullptr;
	MyNode *right = nullptr;
	MyNode *parent = nullptr;
	MyNode()
	{}
	MyNode(MyNodeT keys) : key(keys), left(nullptr), right(nullptr), parent(nullptr)
	{}
	MyNode(MyNodeT keys, MyNode *par) : key(keys), left(nullptr), right(nullptr), parent(par)
	{}
	~MyNode()
	{}
};

template <typename MyTreeT>
class MyTree {
private:
	MyNode<MyTreeT> *root = nullptr;
	MyNode<MyTreeT> *first_elem;
	MyNode<MyTreeT> *new_node;
public:
	MyTree() : root(nullptr)
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
	void AddElem(MyNode<MyTreeT> *current_node, MyNode<MyTreeT> *new_node)
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

		std::cout << current->key << " ";

		DFSAndPrint(current->right);

	}

	void PrintTree()
	{
		MyNode<MyTreeT> *current = root;
		//DFSAndPrint(current);
		BFSANdPrint(current);
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


	int GetMaxDepth(MyNode<MyTreeT> *node)
	{
		if (node == nullptr)
		{
			return 0;
		}

		std::stack<int> depth;
		std::stack<MyNode<MyTreeT> *> st;
		int max_depth = 0;
		int current_depth = 0;

		while (true)
		{
			++current_depth;
			if (node->left != nullptr)
			{
				if (node->right != nullptr)
				{
					st.push(node->right);
					depth.push(current_depth);
				}
				node = node->left;
			}
			else
			{
				if (node->right != nullptr)
				{
					node = node->right;
				}
				else
				{
					if (current_depth > max_depth)
					{
						max_depth = current_depth;
					}
					if (st.empty())
					{
						break;
					}
					current_depth = depth.top();
					depth.pop();
					node = st.top();
					st.pop();
				}
			}

		}
		return max_depth;
	}

	int GetDepth()
	{
		return GetMaxDepth(root);
	}

	void BFSANdPrint(MyNode<MyTreeT> *current)
	{
		std::queue<MyNode<MyTreeT> *> q;
		q.push(current);
		while (!q.empty())
		{
			MyNode<MyTreeT> * node = q.front();
			q.pop();
			std::cout << "|" << node->key << " " << node->key << "|" << std::endl;
			if (node->left != nullptr)
			{
				q.push(node->left);
			}
			if (node->right != nullptr)
			{
				q.push(node->right);
			}
		}
	}

};

//-------------------------------------------------------------------------------------------------------------------------------------------------------//




int main()
{
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int> > vect(n);
	for (int i = 0; i < n; i++)
	{
		std::cin >> vect[i].first >> vect[i].second;
	}

	std::vector<int> vect2(n);
	for (int i = 0; i < n; ++i)
	{
		vect2[i] = vect[i].first;
	}

	MyTreap<int, int> treap(vect);
	MyTree<int> tree(vect2);

	std::cout << tree.GetDepth()-treap.GetDepth()<<std::endl;
	

	return 0;
}
