#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#define coeff 63 //подумать над коэффицентом

struct Node
{
	bool deleted=false;
	std::string str;
	int key; //?
	
	Node()
	{
	}
	Node(std::string new_str): str(new_str), deleted(false)
	{}
	~Node()
	{}

	Node operator=(Node &node)
	{
		this->deleted = node.deleted;
		this->str = node.str;
		this->key = node.key;
	}
};

class Hash_Table {
private:
	std::vector<Node *> buffer;
	int real_size = 0;
	int buffer_size = 8;
	int difference;
	void Change_Table() /////////////
	{
		real_size = 0;
		buffer_size *= 2;
		std::vector<Node *> cur(buffer_size/2);
		for (int i = 0; i < cur.size(); ++i)
		{
			cur[i] = buffer[i];
		}
		buffer.clear();
		buffer.resize(buffer_size);
		for (int i = 0; i <cur.size(); ++i)
		{
			if ((cur[i])&&(!cur[i]->deleted))
			{
					Add(cur[i]->str);
			}
		}
	}

	int Quadratic_Sampling(int hashed, int i)
	{
		return (hashed + i) % buffer_size; //так по заданию написано, что немного странно
	}

public:

	Hash_Table(): difference(0)
	{
		buffer.resize(8);
		for (int i = 0; i < buffer_size; ++i)
		{
			buffer[i] = nullptr;
		}
	}
	Hash_Table(int size): buffer_size(size), difference(0)
	{
		buffer.resize(buffer_size);
		for (int i = 0; i < buffer_size; ++i)
		{
			buffer[i] = nullptr;
		}
	}
	~Hash_Table() 
	{
	}

	bool Chek_Difference()
	{
		return 0.75*buffer_size <= real_size + 1;
	}

	int To_Hash(std::string str)
	{
		int resoult = 0;
		for (int i = 0; i < str.size(); ++i)
		{
			resoult = (resoult + str[i] * coeff) % buffer_size;
		}
		return resoult;
	}

	//---------------------------------------------

	bool Find(std::string str)  
	{
		int hashed;
		hashed = To_Hash(str);
		for (int i = 0; (i < buffer_size) && (buffer[hashed]); ++i)
		{

			if (!(buffer[hashed]->deleted)) 
			{
				if ((buffer[hashed]->str.compare(str)) == 0)
				{
					return true;
				}
			}
			hashed = Quadratic_Sampling(hashed, i);
		}

		return false;
	}

	//--------------------------------

	bool Add(std::string str)
	{
		if (Find(str))
		{
			return false;
		}
		else {
			if (Chek_Difference())
			{
				Change_Table();
			}

			int hashed;
			hashed = To_Hash(str);

			for (int i = 0; i < buffer_size; ++i)
			{
				if (!buffer[hashed])
				{
					++real_size;
				//	Node cur_n(str);
				//	buffer[hashed] = &cur_n; //
					buffer[hashed]= new Node(str);
					return true;
				}
				else
				{
					if (buffer[hashed]->deleted)
					{
						++real_size;
						buffer[hashed]->deleted = false;
						buffer[hashed]->str = str;
						return true;
					}
				}
				hashed = Quadratic_Sampling(hashed, i);
			}
			return false;
		}
	}

	//-------------------------------------

	bool Delete(std::string str)
	{
		if (!Find(str))
		{
			return false;
		}
		else
		{
			int hashed;
			hashed = To_Hash(str);

			for (int i = 0; i < buffer_size; ++i)
			{
				if (!buffer[hashed]->deleted)
				{
					if (buffer[hashed]->str.compare(str) == 0)
					{
						--real_size;
						buffer[hashed]->deleted = true;
						return true;
					}
				}

				hashed = Quadratic_Sampling(hashed, i);
			}

		}
		return false;
	}


};





int main()
{
	std::string str;
	char sym;
	Hash_Table h_table;
	while (std::cin>>sym)
	{
		std::cin >> str;

		if (sym == '+')
		{
			bool zn = h_table.Add(str); 
			if (zn)
			{
				std::cout << "OK" << std::endl;
			}
			else
			{
				std::cout << "FAIL" << std::endl;
			}
		}

		if (sym == '?')
		{
			bool zn = h_table.Find(str); 
			if (zn)
			{
				std::cout << "OK" << std::endl;
			}
			else
			{
				std::cout << "FAIL" << std::endl;
			}
		}

		if (sym == '-')
		{
			bool zn = h_table.Delete(str); 
			if (zn)
			{
				std::cout << "OK" << std::endl;
			}
			else
			{
				std::cout << "FAIL" << std::endl;
			}
		}

	}

	return 0;
}
