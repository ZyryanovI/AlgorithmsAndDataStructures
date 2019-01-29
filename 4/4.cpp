#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>


struct Node {

	Node(const std::string& new_value)
	{
		value = new_value;
		priority = rand();
		left = nullptr;
		right = nullptr;
		tree_size = 1;
	}

	void Fix()
	{
		tree_size = 1;
		if (left != nullptr)
		{
			tree_size += left->tree_size;
		}
		if (right != nullptr)
		{
			tree_size += right->tree_size;
		}
	}

	int tree_size;
	int priority;
	std::string value;

	Node* left;
	Node* right;

};


class Cartesian_Tree_By_Implicit_Key {
public:
	Cartesian_Tree_By_Implicit_Key()
	{
		root = nullptr;
	}
	~Cartesian_Tree_By_Implicit_Key()
	{
		Clear();
	}

	void Clear()
	{
		Clear(root);
		root = nullptr;
	}

	void Insert(int position,const std::string& value)
	{
		Node* current = new Node(value);
		// Split tree by position and merge new node
		//with right tree then merge result with left tree
		std::pair<Node*, Node*> anser = split(root, position);
		Node* right = merge(current, anser.second);
		root = merge(anser.first, right);
	}

	void Remove(int position)
	{
		// Split required node from both sides and merge two other trees
		std::pair<Node*, Node*> anser1 = split(root, position);
		std::pair<Node*, Node*> anser2 = split(anser1.second, 1);
		delete anser2.first;
		root = merge(anser1.first, anser2.second);
	}

	std::string Get(int position)
	{
		// Going down the tree
		int l;
		Node* node = root;
		while (true)
		{
			int l;
			if (node->left != nullptr)
			{
				l = node->left->tree_size;
			}
			else {
				l = 0;
			}
			if (l == position)
			{
				break;
			}
			if (position < l)
			{
				node = node->left;
			}
			else {
				position -= l + 1;
				node = node->right;
			}
		}
		return node->value;
	}

private:
	Node* root;
	void Clear(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		else
		{
			Clear(node->left);
			Clear(node->right);
			delete node;
		}
	}

	std::pair<Node*, Node*> split(Node* node, int position)
	{
		if (node == nullptr)
		{
			return std::pair<Node*, Node*>(nullptr, nullptr);
		}
		int l;
		if (node->left != nullptr)
		{
			l = node->left->tree_size;
		}
		else {
			l = 0;
		}
		if (l >= position)
		{
			std::pair<Node*, Node*> anser = split(node->left, position);
			node->left = anser.second;
			node->Fix();
			return std::make_pair(anser.first, node);
		}
		else {
			std::pair<Node*, Node*> anser = split(node->right, position - l - 1);
			node->right = anser.first;
			node->Fix();
			return std::make_pair(node, anser.second);
		}
	}

	Node* merge(Node* node1, Node* node2)
	{
		if (node2 == nullptr)
		{
			return node1;
		}
		if (node1 == nullptr)
		{
			return node2;
		}
		if (node1->priority > node2->priority)
		{
			node1->right = merge(node1->right, node2);
			node1->Fix();
			return node1;
		}
		else {
			node2->left = merge(node1, node2->left);
			node2->Fix();
			return node2;
		}
	}
};



int main()
{
	int n;
	std::cin >> n;
	Cartesian_Tree_By_Implicit_Key string_array;

	for (int i = 0; i < n; ++i)
	{
		char cmd;
		std::cin >> cmd;
		switch (cmd)
		{
		case '+':{
			int position = 0;
			std::string val = "";
			std::cin >> position >> val;
			string_array.Insert(position, val);
			break;
		}
		case '?':{
			int position = 0;
			std::cin >> position;
			std::cout << string_array.Get(position) << std::endl;
			break;
		}
		default: {
			int position;
			std::cin >> position;
			string_array.Remove(position);
			break;
		}
		}
	}


	return 0;
}


