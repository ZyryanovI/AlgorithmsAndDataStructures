#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>


const int INF = 2147483647;
const unsigned long long int GOAL = 1147797409030816545;

const unsigned long long int ReMasks[] = { 0xFFFFFFFFFFFFFFF0, 0xFFFFFFFFFFFFFF0F, 0xFFFFFFFFFFFFF0FF, 0xFFFFFFFFFFFF0FFF, 0xFFFFFFFFFFF0FFFF, 0xFFFFFFFFFF0FFFFF, 0xFFFFFFFFF0FFFFFF, 0xFFFFFFFF0FFFFFFF, 0xFFFFFFF0FFFFFFFF, 0xFFFFFF0FFFFFFFFF, 0xFFFFF0FFFFFFFFFF, 0xFFFF0FFFFFFFFFFF, 0xFFF0FFFFFFFFFFFF, 0xFF0FFFFFFFFFFFFF, 0xF0FFFFFFFFFFFFFF, 0x0FFFFFFFFFFFFFFF };

const unsigned long long int Masks[] = { 0x000000000000000F, 0x00000000000000F0, 0x0000000000000F00,0x000000000000F000, 0x00000000000F0000, 0x0000000000F00000,0x000000000F000000, 0x00000000F0000000, 0x0000000F00000000,0x000000F000000000, 0x00000F0000000000, 0x0000F00000000000,0x000F000000000000, 0x00F0000000000000, 0x0F00000000000000,0xF000000000000000 };

//------------------------------------------------------------------------------------

class Position {
public:
	Position()
	{
		data = 0;
	}

	Position(const Position & pos) //
	{
		data = pos.data; 
		null_pos = pos.null_pos; 
		depth = pos.depth;
		heuristic = pos.heuristic;
	}

	bool Is_Done()
	{
		return data == GOAL;
	}

	void Set_Pos(int place, unsigned char val)
	{
		data = (data & ReMasks[place]) | ((unsigned long long int)val << (place << 2));
	}

	unsigned char Get_Pos(int place) const
	{
		return (unsigned char)((data & Masks[place]) >> (place << 2));
	}

	Position Up() const
	{
		Position result(*this);

		int trg = null_pos - 4;
		unsigned char c = Get_Pos(trg);
		int cur_heu = result.Get_Heuristic();
		cur_heu -= 10 * (abs(trg % 4 - (c - 1) % 4) + abs(trg / 4 - (c - 1) / 4));
		result.Set_Heuristic(cur_heu);

		result.Set_Pos(trg, 0);
		result.Set_Pos(null_pos, c);

		cur_heu = result.Get_Heuristic();
		cur_heu += 10 * (abs(null_pos % 4 - (c - 1) % 4) + abs(null_pos / 4 - (c - 1) / 4));
		result.Set_Heuristic(cur_heu);
		result.Set_Null_Pos(trg);
		long long int cur_depth = result.Get_Depth();
		++cur_depth;
		result.Set_Depth(cur_depth);

		return result;
	}

	Position Down() const
	{
		Position result(*this);

		int trg = null_pos + 4;
		unsigned char c = Get_Pos(trg);
		int cur_heu = result.Get_Heuristic();
		cur_heu -= 10 * (abs(trg % 4 - (c - 1) % 4) + abs(trg / 4 - (c - 1) / 4));
		result.Set_Heuristic(cur_heu);

		result.Set_Pos(trg, 0);
		result.Set_Pos(null_pos, c);

		cur_heu = result.Get_Heuristic();
		cur_heu += 10 * (abs(null_pos % 4 - (c - 1) % 4) + abs(null_pos / 4 - (c - 1) / 4));
		result.Set_Heuristic(cur_heu);
		result.Set_Null_Pos(trg);
		long long int cur_depth = result.Get_Depth();
		++cur_depth;
		result.Set_Depth(cur_depth);

		return result;
	}

	Position Left() const
	{
		Position result(*this);

		int trg = null_pos - 1;
		unsigned char c = Get_Pos(trg);
		int cur_heu = result.Get_Heuristic();
		cur_heu -= 10 * (abs(trg % 4 - (c - 1) % 4) + abs(trg / 4 - (c - 1) / 4));
		result.Set_Heuristic(cur_heu);

		result.Set_Pos(trg, 0);
		result.Set_Pos(null_pos, c);

		cur_heu = result.Get_Heuristic();
		cur_heu += 10 * (abs(null_pos % 4 - (c - 1) % 4) + abs(null_pos / 4 - (c - 1) / 4));
		result.Set_Heuristic(cur_heu);
		result.Set_Null_Pos(trg);
		long long int cur_depth = result.Get_Depth();
		++cur_depth;
		result.Set_Depth(cur_depth);

		return result;
	}

	Position Right() const
	{
		Position result(*this);
		
		int trg = null_pos + 1;
		unsigned char c = Get_Pos(trg);
		int cur_heu = result.Get_Heuristic();
		cur_heu -= 10 * (abs(trg % 4 - (c - 1) % 4) + abs(trg / 4 - (c - 1) / 4));
		result.Set_Heuristic(cur_heu);

		result.Set_Pos(trg, 0);
		result.Set_Pos(null_pos, c);

		cur_heu = result.Get_Heuristic();
		cur_heu += 10 * (abs(null_pos % 4 - (c - 1) % 4) + abs(null_pos / 4 - (c - 1) / 4));
		result.Set_Heuristic(cur_heu);
		result.Set_Null_Pos(trg);
		long long int cur_depth = result.Get_Depth();
		++cur_depth;
		result.Set_Depth(cur_depth);

		return result;
	}

	unsigned long long int Get_Data() const
	{
		return data;
	}

	void Set_Data(unsigned long long int new_data)
	{
		data = new_data;
	}

	void Set_Depth(long long new_depth)
	{
		depth = new_depth;
	}

	long long int Get_Depth() const
	{
		return depth;
	}

	int Get_Heuristic() const
	{
		return heuristic;
	}

	void Set_Heuristic(int new_heuristic)
	{
		heuristic = new_heuristic;
	}

	bool Check_Solution() const //+
	{
		int inversions = 0;
		for (int i = 0; i < 16; ++i)
		{
			for (int j = i + 1; j < 16; ++j)
			{
				if ((Get_Pos(i) != 0) && (Get_Pos(j) != 0))
				{
					if (Get_Pos(i) > Get_Pos(j))
					{
						//std::cout << Get_Pos(i) << "|" << Get_Pos(j) << std::endl;
						++inversions;
					}
				}
			}
		}
		//std::cout << inversions << std::endl; //debug
		return (inversions % 2 == 0) == (null_pos / 4 % 2 == 1);
	}

	int Find_heuristic() const//+
	{
		int heuristic = 0;
		for (int i = 0; i < 16; ++i)
		{
			if (Get_Pos(i) == 0)
			{
				continue;
			}
			heuristic += 10*(abs(i / 4 - (Get_Pos(i) - 1) / 4) + abs(i % 4 - (Get_Pos(i) - 1) % 4));
		}


		return heuristic;
	}

	Position &operator=(const Position &pos) //+
	{
		data = pos.data;
		null_pos = pos.null_pos;
		depth = pos.depth;
		heuristic = pos.heuristic;
		return *this;
	}

	friend bool operator<(const Position& pos1, const Position& pos2) ///////////////////
	{
		return true;
	}


	int Get_Null_Pos() const
	{
		return null_pos;
	}

	void Set_Null_Pos(int new_null_pos)
	{
		null_pos = new_null_pos;
	}


private:

	int null_pos;
	unsigned long long int data;

	long long int depth;

	int heuristic;
	
};

//--------------------------------------------------------------------------





//-------------------------------------------------------------------------------

class My_Priority_Queue {
public:
	My_Priority_Queue()
	{
		buffer_size = 16;
		size = 0;
		buffer = new std::pair<int, Position>[buffer_size];
	}
	~My_Priority_Queue()
	{
		delete[] buffer;
	}

	void Emplace(std::pair<int, Position> value)
	{
		if (size + 1 > buffer_size)
		{
			std::pair<int, Position> *tmp = new std::pair<int, Position>[buffer_size * 2];
			for (int i = 0; i < buffer_size; ++i)
			{
				tmp[i] = buffer[i];
			}
			delete[] buffer;
			buffer = tmp;
			buffer_size *= 2;
		}
		buffer[size] = value;
		++size;
		Sift_Up(size - 1);
	}

	std::pair<int, Position> Pop()
	{
		std::pair<int, Position> max = buffer[0];
		buffer[0] = buffer[size - 1];
		--size;
		if (size)
		{
			Sift_Down(0);
		}
		return max;
	}

private:
	int buffer_size;
	int size;
	std::pair<int, Position> *buffer;

	void Sift_Up(int index)
	{
		while ((index) && (buffer[index] < buffer[(index - 1) / 2]))
		{
			std::pair<int, Position> tmp = buffer[index];
			buffer[index] = buffer[(index - 1) / 2];
			buffer[(index - 1) / 2] = tmp;
			index = (index - 1) / 2;
		}

	}

	void Sift_Down(int index)
	{
		int max = index;
		if ((index * 2 + 1 < size) && (buffer[index * 2 + 1] < buffer[max]))
		{
			max = index * 2 + 1;
		}
		if ((index * 2 + 2 < size) && (buffer[index * 2 + 2] < buffer[max]))
		{
			max = index * 2 + 2;
		}
		if (max != index)
		{
			std::pair<int, Position> tmp = buffer[index];
			buffer[index] = buffer[max];
			buffer[max] = tmp;
			Sift_Down(max);

		}

	}


};


//-----------------------------------------------------------------------

//

void AStart(const Position &pos, std::vector<char> &anser)
{
	My_Priority_Queue priority_queue;
	priority_queue.Emplace(std::make_pair(0, pos));

	std::unordered_map<unsigned long long int, std::pair<char, unsigned long long int> > parents;

	parents.emplace(pos.Get_Data(), std::make_pair(0, 0)); ///////

	
	while (true)
	{
		
		Position v;
		Position cur_pos;
		v = priority_queue.Pop().second;

		if (v.Get_Null_Pos() >= 4)
		{
			cur_pos = v.Up();

			if (parents.find(cur_pos.Get_Data()) == parents.end())
			{
				parents.emplace(cur_pos.Get_Data(), std::make_pair('D', v.Get_Data()));

				if (cur_pos.Get_Data() == GOAL)
				{
					break;
				}

				priority_queue.Emplace(std::make_pair(cur_pos.Get_Depth() + cur_pos.Get_Heuristic(), cur_pos));
			}

		}

		if (v.Get_Null_Pos() <= 11)
		{
			cur_pos = v.Down();

			if (parents.find(cur_pos.Get_Data()) == parents.end())
			{
				parents.emplace(cur_pos.Get_Data(), std::make_pair('U', v.Get_Data()));

				if (cur_pos.Get_Data() == GOAL)
				{
					break;
				}

				priority_queue.Emplace(std::make_pair(cur_pos.Get_Depth() + cur_pos.Get_Heuristic(), cur_pos));
			}

		}

		if (v.Get_Null_Pos()%4 != 3)
		{
			cur_pos = v.Right();

			if (parents.find(cur_pos.Get_Data()) == parents.end())
			{
				parents.emplace(cur_pos.Get_Data(), std::make_pair('L', v.Get_Data()));

				if (cur_pos.Get_Data() == GOAL)
				{
					break;
				}

				priority_queue.Emplace(std::make_pair(cur_pos.Get_Depth() + cur_pos.Get_Heuristic(), cur_pos));
			}

		}

		if (v.Get_Null_Pos()%4 != 0)
		{
			cur_pos = v.Left();

			if (parents.find(cur_pos.Get_Data()) == parents.end())
			{
				parents.emplace(cur_pos.Get_Data(), std::make_pair('R', v.Get_Data()));

				if (cur_pos.Get_Data() == GOAL)
				{
					break;
				}

				priority_queue.Emplace(std::make_pair(cur_pos.Get_Depth() + cur_pos.Get_Heuristic(), cur_pos));
			}

		}


	}

	unsigned long long int u = GOAL;
	std::pair<char, unsigned long long int> cur_move;
	while (u != pos.Get_Data()) //////////////
	{

		cur_move = parents[u];
		anser.push_back(cur_move.first);  //тут подумать
		u = cur_move.second;
	}

}


//*************************************************

void Solution(std::vector<int> &field)
{
	Position cur_pos;
	for (int i = 0; i < 16; ++i)
	{
		if (field[i] == 0)
		{
			cur_pos.Set_Null_Pos(i);
		}
		cur_pos.Set_Pos(i, (unsigned char)field[i]);
	}

	cur_pos.Set_Depth(0);
	cur_pos.Set_Heuristic(cur_pos.Find_heuristic());
	std::vector<char> anser;

	if (cur_pos.Is_Done())
	{
		std::cout << "0";
		return;
	}
	if (cur_pos.Check_Solution())
	{
		AStart(cur_pos, anser);
		std::cout << anser.size() << std::endl;
		for (int i = anser.size()-1; i >= 0; --i) //
		{
			std::cout << anser[i];
		}
	}
	else {
		std::cout << "-1";
	}


}



//***************************************************************

int main() //+
{
	std::vector<int> field(16);

	for (int i = 0; i < 16; ++i)
	{
		int position;
		std::cin >> position;
		field[i] = position;
	}


	Solution(field);



	return 0;

}



