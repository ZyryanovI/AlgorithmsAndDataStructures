#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>

class Position{ //x,y - позиции 0
public:

	Position()
	{
		x = 0;
		y = 0;
		steps = 0;
		pref = "";
	}

	Position(std::vector<std::vector<int>> new_table, int new_x, int new_y, int new_steps, std::string new_pref)
	{
		table = new_table;
		x = new_x;
		y = new_y;
		steps = new_steps;
		pref = new_pref;
	}

	~Position()
	{}

	int x;
	int y;
	int steps;
	std::vector<std::vector<int> > table;
	std::string pref;
};

bool Check_Invertions(std::vector<std::vector<int>> &table)
{
	int result = 0;
	int cur_pos;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			cur_pos = table[i][j];
			for (int i_ = i; i_ < 3; ++i_)
			{
				for (int j_ = 0; j_ < 3; ++j_)
				{
					if ((i_ <= i) && ((i_ != i) || (j_ < j)))
					{
						continue;
					}
					else {
						if ((cur_pos != 0) && (table[i_][j_] < cur_pos) && (table[i_][j_] != 0))
						{
							++result;
						}
					}
				}
			}
		}
	}

	if (result % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Find_heurictics(std::vector<std::vector<int>> &table)
{
	int heur = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (table[i][j] != 0)
			{
				heur += abs(i - (table[i][j] - 1) / 3) + abs(j - (table[i][j] - 1) % 3);
			}
		}
	}
	return heur;
}

void Solution(std::vector<std::vector<int>> &table)
{
	if (!Check_Invertions(table))
	{
		std::cout << "-1";
		return;
	}
	else
	{
		int start_x;
		int start_y;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (table[i][j] == 0)
				{
					start_x = i;
					start_y = j;
				}
			}
		}

		std::queue<Position> queue_for_bfs;
		//std::set<Position> queue_for_bfs;

		Position start(table, start_x, start_y, 0, "");

		queue_for_bfs.push(start);
		//queue_for_bfs.insert(start);

		while (!queue_for_bfs.empty())
		{
			Position cur_pos = queue_for_bfs.front();
			//Position cur_pos = *queue_for_bfs.begin();
			queue_for_bfs.pop();
			//queue_for_bfs.erase(queue_for_bfs.begin());
			
			
//			std::cout << cur_pos.x << "|" << cur_pos.y << std::endl;  //debug

			int heuristic = Find_heurictics(cur_pos.table);

//			std::cout << cur_pos.steps << std::endl;

			if ((heuristic == 0) && (cur_pos.steps < 31))
			{
				std::cout << cur_pos.steps << std::endl;
				std::cout << cur_pos.pref;
				return;
			}

			if (cur_pos.steps + heuristic > 31)
			{
				continue;
			}

			if ((cur_pos.x != 0)&& ((cur_pos.pref.size() == 0) || (cur_pos.pref[cur_pos.pref.size() - 1] != 'D'))) //чтобы не циклились
			{
				std::swap(cur_pos.table[cur_pos.x][cur_pos.y], cur_pos.table[cur_pos.x - 1][cur_pos.y]);
				Position pushing_pos(cur_pos.table, cur_pos.x - 1, cur_pos.y, cur_pos.steps + 1, cur_pos.pref + 'U');
				queue_for_bfs.push(pushing_pos);
				//queue_for_bfs.insert(pushing_pos);
				std::swap(cur_pos.table[cur_pos.x - 1][cur_pos.y], cur_pos.table[cur_pos.x][cur_pos.y]);
			}

			if ((cur_pos.x != 2) && ((cur_pos.pref.size() == 0) || (cur_pos.pref[cur_pos.pref.size() - 1] != 'U')))
			{
				std::swap(cur_pos.table[cur_pos.x][cur_pos.y], cur_pos.table[cur_pos.x + 1][cur_pos.y]);
				Position pushing_pos(cur_pos.table, cur_pos.x + 1, cur_pos.y, cur_pos.steps + 1, cur_pos.pref + 'D');
				queue_for_bfs.push(pushing_pos);
				//queue_for_bfs.insert(pushing_pos);
				std::swap(cur_pos.table[cur_pos.x + 1][cur_pos.y], cur_pos.table[cur_pos.x][cur_pos.y]);
			}

			if ((cur_pos.y != 0) && ((cur_pos.pref.size() == 0) || (cur_pos.pref[cur_pos.pref.size() - 1] != 'R')))
			{
				std::swap(cur_pos.table[cur_pos.x][cur_pos.y], cur_pos.table[cur_pos.x][cur_pos.y - 1]);
				Position pushing_pos(cur_pos.table, cur_pos.x, cur_pos.y - 1, cur_pos.steps + 1, cur_pos.pref + 'L');
				queue_for_bfs.push(pushing_pos);
				//queue_for_bfs.insert(pushing_pos);
				std::swap(cur_pos.table[cur_pos.x][cur_pos.y - 1], cur_pos.table[cur_pos.x][cur_pos.y]);
			}

			if ((cur_pos.y != 2) && ((cur_pos.pref.size() == 0) || (cur_pos.pref[cur_pos.pref.size() - 1] != 'L')))
			{
				std::swap(cur_pos.table[cur_pos.x][cur_pos.y], cur_pos.table[cur_pos.x][cur_pos.y+1]);
				Position pushing_pos(cur_pos.table, cur_pos.x, cur_pos.y+1, cur_pos.steps + 1, cur_pos.pref + 'R');
				queue_for_bfs.push(pushing_pos);
				//queue_for_bfs.insert(pushing_pos);
				std::swap(cur_pos.table[cur_pos.x][cur_pos.y+1], cur_pos.table[cur_pos.x][cur_pos.y]);
			}


		}

		std::cout << "31" << std::endl;
		std::cout << "";
		return;
	}
}


int main()
{
	std::vector<std::vector<int> > field(3, std::vector<int>(3));

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int position;
			std::cin >> position;
			field[i][j] = position;
		}
	}
	
	Solution(field);

	
	return 0;

}