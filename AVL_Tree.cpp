#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

template<typename Key_TT, typename Data_TT>
struct AVLNode {
	Key_TT key;
	Data_TT data;
	AVLNode *parent;
	AVLNode *left=nullptr;
	AVLNode *right=nullptr;
	int height=1;
	//кол-во элементов в поддеревьях чтобы порядковую статистику искать:
	int right_size=0; 
	int left_size=0;

	AVLNode()
	{}
	AVLNode(Key_TT new_key, Data_TT new_data, AVLNode *new_parent)
	{
		key = new_key;
		data = new_data;
		parent = new_parent;
	}

	~AVLNode()
	{}
	
	void correct_height() 
	{
		int height_left;
		int height_right;
		if (!left)
		{
			height_left = 0;
		}
		else
		{
			height_left = left->height;
		}
		if (!right)
		{
			height_right = 0;
		}
		else
		{
			height_right = right->height;
		}

		height = std::max(height_right, height_left) + 1;

		if (!right)
		{
			right_size = 0;
		}
		else
		{
			right_size = right->left_size + right->right_size + 1;
		}

		if (!left)
		{
			left_size = 0;
		}
		else
		{
			left_size = left->right_size + left->left_size + 1;
		}
	}

	int show_difference()
	{
		if (!right) {
			if (!left)
			{
				return 0;
			}
			else {
				return (-1)*(left->height);
			}
		}
		else {
			if (!left)
			{
				return right->height;
			}
			else {
				return right->height - left->height;
			}
		}
	}

};

////////////////////////////////////////////////////////////////////////////////////

template<typename Key_T,typename Data_T>
class AVLTree {
private:
	AVLNode<Key_T, Data_T> *root=nullptr;

	void Deleting(AVLNode<Key_T, Data_T> *node)
	{
		if (node == nullptr)
		{
			return;
		}
		Deleting(node->left);
		Deleting(node->right);
		delete node;
	}

public:
	AVLTree()
	{}

	~AVLTree()
	{
		Deleting(root);
	}
	
	//------------------------------------------------------------------


	//---------------------------------------------------------------------

	void AddElem(Key_T key)
	{
		AVLNode<Key_T, Data_T> *parent_for_node = nullptr;
		AVLNode<Key_T, Data_T> *node = root;

		while (node)
		{
			parent_for_node = node;
			if (key < node->key)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}

		AVLNode<Key_T, Data_T> *cur_node = new AVLNode<Key_T, Data_T>(key, key, parent_for_node); ///
		if (!parent_for_node)
		{
			root = cur_node;
		}
		else
		{
			if (key < parent_for_node->key)
			{
				parent_for_node->left = cur_node;
			}
			else
			{
				parent_for_node->right = cur_node;
			}
		}

		node = parent_for_node;
		while (node)
		{
			ToBalance(node);
			node = node->parent;
		}

		ToBalance(root);
	}

	//-----------------------------------------------------

	void DeleteNode(AVLNode<Key_T, Data_T> *&node) //
	{
		AVLNode<Key_T, Data_T> *right = node->right; 
		AVLNode<Key_T, Data_T> *left = node->left;
		AVLNode<Key_T, Data_T> *parent_for_node = node->parent;
		if ((node == root) && (node->left == nullptr) && (node->right == nullptr))
		{
			delete node;
			root = nullptr;
			return;
		}
		delete node;

		if (!left)
		{
			node = right;
			if (right)
			{
				right->parent = parent_for_node;
			}
		}
		else
		{
			if (!right)
			{
				node = left;
				left->parent = parent_for_node;
			}
			else
			{
				AVLNode<Key_T, Data_T> * cur_node;
				cur_node = right;
				while (cur_node->left)
				{
					cur_node = cur_node->left;
				}

				if (right == cur_node)     
				{
					node = cur_node;
					node->left = left;
					node->parent = parent_for_node;
					left->parent = node;
					ToBalance(node);
				}
				else
				{
					node = cur_node;
					node->parent->left = node->right; 
					if (node->right)
					{
						node->right->parent = node->parent;
					}

					
					cur_node = node->parent;
					
					node->left = left;
					left->parent = node;
					node->parent = parent_for_node;
					node->right = right;
					right->parent = node;

					while (cur_node != parent_for_node)
					{

						ToBalance(cur_node);
						cur_node = cur_node->parent;
					}

				}

			}
		}

	}

	//-----------------------------------------------------
	bool DeleteElem(Key_T key)
	{
		AVLNode<Key_T, Data_T> *parent_for_node = nullptr;
		AVLNode<Key_T, Data_T> *node = root;

		while ((key != node->key) && (node))
		{

			parent_for_node = node;
			if (node->key > key)
			{
				node=node->left;
			}
			else
			{
				node=node->right;
			}
		}

	

		if (!node)
		{
			return false;
		}

		if (!parent_for_node)
		{
			DeleteNode(root);
		}
		else
		{
			if (parent_for_node->key > key)
			{
				DeleteNode(parent_for_node->left);
			}
			else
			{
				DeleteNode(parent_for_node->right);
			}
		}

		node = parent_for_node; 

		while (node)
		{
		
			ToBalance(node);
			node = node->parent;
		}
		ToBalance(root);
		return true;
	}

	//-----------------------------------------------------

	void LeftRotation(AVLNode<Key_T, Data_T> *&node)
	{


		AVLNode<Key_T, Data_T> * cur_1 = node->right;
		AVLNode<Key_T, Data_T> * cur_2 = node; 
		AVLNode<Key_T, Data_T> * cur_3 = node->right->left;

		node->right->parent = node->parent;

		if (!cur_1->parent)
		{
			root = cur_1;
		}
		else
		{
			if (cur_1->parent->left == cur_2) //
			{
				cur_1->parent->left = cur_1;
			}
			else
			{
				cur_1->parent->right = cur_1; //
			}
		}

		cur_2->parent = cur_1;
		cur_1->left = cur_2;

		if (cur_3) 
		{
			cur_3->parent = cur_2;
			cur_2->right = cur_3;
		}
		else
		{
			cur_2->right = nullptr; 
		}

		cur_2->correct_height();
		cur_1->correct_height();
	}

	//------------------------------------------------

	void RightRotation(AVLNode<Key_T, Data_T> *&node)
	{
		if ( node->left==nullptr) //DEBAG
		{
			while (true)
			{
				//std::cout << "kakim voobshe obrazom eto proishodit" << std::endl;
			}
			return;
		}

		AVLNode<Key_T, Data_T> * cur_2 = node->left;
		AVLNode<Key_T, Data_T> * cur_1 = node;
		AVLNode<Key_T, Data_T> * cur_3 = node->left->right;

		node->left->parent = node->parent;
		if (!cur_2->parent)
		{
			root = cur_2;
		}
		else
		{
			if (cur_2->parent->left == cur_1) //
			{
				cur_2->parent->left = cur_2;
			}
			else
			{
				cur_2->parent->right = cur_2; //
			}
		}

		cur_1->parent = cur_2;
		cur_2->right = cur_1; 
		if (cur_3)
		{
			cur_3->parent = cur_1; 
			cur_1->left = cur_3;
		}
		else
		{
			cur_1->left = nullptr;
		}

		cur_1->correct_height(); 
		cur_2->correct_height();
	}
	//--------------------------------------------------

	void BigRightRotation(AVLNode<Key_T, Data_T> * &node)
	{
		LeftRotation(node->left);
		RightRotation(node);
	}

	//--------------------------------------------------

	void BigLeftRotation(AVLNode<Key_T, Data_T> *&node)
	{
		RightRotation(node->right);
		LeftRotation(node);
	}

	//-------------------------------------------------

	void ToBalance(AVLNode<Key_T, Data_T> *&node) //м.ь. просто *
	{
		if (node==nullptr)
		{
			return;
		}
		else
		{
			node->correct_height();
			if (node->show_difference() == 2 && node->right->show_difference()== -1)
			{
				BigLeftRotation(node);
				return;
			}
			if (node->show_difference() == 2)
			{
				LeftRotation(node);
				return;
			}
			if (node->show_difference() == (-2) && node->left->show_difference() == 1)
			{
				BigRightRotation(node);
				return;
			}
			if (node->show_difference() == (-2))
			{
				RightRotation(node);
			}
		}
	} 

	//----------------------------------------------

	//объяснение к алгоритму поиска порядковой статистики:
	Data_T FindOrderStat(int need_place)
	{
		AVLNode<Key_T, Data_T> * cur_node = root; //начинаем с корня

		if (cur_node == nullptr)
		{
			while (true)
			{
				std::cout << "sozdateli zadaniy ochen ne pravy" << std::endl;
			}
		}

		while (cur_node->left_size != need_place) //т.к. в любом узле все элементы в левом поддереве меньше, а считаем мы порядковую статистику с 0, то если неообходимая порядковая статистика равна кол-во элементов в левом поддереве - мы победили
		{
			if (cur_node->left_size >= need_place) //если высота поддерева больше, чем статистика, просто идем на лево и ищем там
			{
				cur_node = cur_node->left;
			}
			else //если высота левого поддерева меньше, чем статистика, тогда она в правом поддереве, тогда идем в правое поддерево, при этом ищем относительно правого поддерева, значит вычитаем высоту левого поддерева
			{
				need_place -= cur_node->left_size;
				--need_place;
				cur_node=cur_node->right;
			}
		}
		return cur_node->data;
	}



};

/////////////////////////////////////////////////////////////

int main()
{
	int n;
	std::cin >> n;
	
	AVLTree<int, int> tree;
	int key;
	int ordinal_stat;
	for (int i = 0; i < n; ++i)
	{
		std::cin >> key;
		std::cin >> ordinal_stat;

		if (key > 0)
		{
			tree.AddElem(key);
		}
		else {
			if (key < 0)
			{
				key *= (-1);
				tree.DeleteElem(key);
			}
			else {
				std::cout << "If there is such test, conditions of the problem are wrong";
			}
		}

		int stat = tree.FindOrderStat(ordinal_stat);
		std::cout << stat << " ";
	}

	return 0;
}
