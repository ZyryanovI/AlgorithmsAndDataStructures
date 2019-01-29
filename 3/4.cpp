#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>

const int INF = 100000;

struct edgeInfo {
	int capacity;
	int flow;
	edgeInfo(int c, int f){
		capacity = c;
		flow = f;
	}
};



class CMatrixGraph{
public:
	CMatrixGraph(int _verticesCount) :
		v(_verticesCount)
	{
		g.resize(_verticesCount);
		dist.assign(_verticesCount, INF);
		for (int i = 0; i < g.size(); i++)
		{
			edgeInfo tmp(0, 0);
			g[i].assign(_verticesCount, tmp);
		}
	}
	void AddEdge(int from, int to, int capacity, int flow)
	{
		g[from][to].capacity += capacity;
		g[from][to].flow = flow;
	}

	int VerticesCount() const { return v; }

	edgeInfo GetEdge(int start, int end)
	{
		return g[start][end];
	}

	void changeFlow(int from, int to, int flow)
	{
		g[from][to].flow += flow;
	}

	std::vector<int> dist;
private:
	std::vector < std::vector <edgeInfo> >  g;
	int v;
};




bool BFS(CMatrixGraph &graph, int s, int t)
{
	graph.dist.assign(graph.VerticesCount(), INF);
	graph.dist[s] = 0;
	std::queue< int > q;
	q.push(s);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = 0; i < graph.VerticesCount(); i++)
		{
			edgeInfo v = graph.GetEdge(u, i);
			if (v.capacity <= 0) continue;
			if (v.flow < v.capacity && graph.dist[i] == INF)
			{
				graph.dist[i] = graph.dist[u] + 1;
				q.push(i);
			}
		}
	}
	return graph.dist[t] != INF;
}

int dfs(CMatrixGraph &graph, std::vector<int> &ptr, int v, int flow)
{
	if (flow == 0)	return 0;
	if (v == 0) return flow;
	for (ptr[v]; ptr[v] < ptr.size(); ptr[v]++) {
		int u = ptr[v];
		edgeInfo tmp = graph.GetEdge(v, u);
		if (tmp.capacity > 0)
		{
			if (graph.dist[u] == graph.dist[v] + 1)
			{
				int pushed = dfs(graph, ptr, u, std::min(flow, tmp.capacity - tmp.flow));
				if (pushed != 0) {
					graph.changeFlow(v, u, pushed);
					graph.changeFlow(u, v, -pushed);
					return pushed;
				}
			}
		}
	}
	return 0;
}

void dfs_original(CMatrixGraph &graph, std::vector<int> &razrez, int v, std::vector<bool> &used)
{
	used[v] = true;
	for (int i = 0; i < graph.VerticesCount(); ++i)
	{
		edgeInfo tmp = graph.GetEdge(v, i);
		if (!used[i] && tmp.capacity - tmp.flow > 0)
		{
			razrez.push_back(i);
			dfs_original(graph, razrez, i, used);
		}
	}
}

int findMaxFlow(CMatrixGraph &graph)
{
	int s = 1, t = 0;
	int MaxFlow = 0;
	std::vector<int> ptr;
	int pushed = 0;
	int flow = 0;
	bool flag = BFS(graph, s, t);
	while (BFS(graph, s, t))
	{
		ptr.assign(graph.VerticesCount(), 0);
		flow = dfs(graph, ptr, s, INF);
		while (flow > 0)
		{
			MaxFlow += flow;
			flow = dfs(graph, ptr, s, INF);
		}
	}
	return MaxFlow;
}

int solve(std::string &s, std::string &s_template)
{
	int start_pos = 0;
	int question_count_t = 2;
	int question_count = 0;
	int question_amount = 0;
	for (int i = 0; i < s_template.length(); i++)
	{
		if (s_template[i] == '?')
		{
			question_count_t++;
			question_amount++;
		}
	}

	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '?') question_amount++;
	} //подсчет количества вопросов дл€ создани€ графа

	std::vector<std::pair<char, int>> s_pairs; //вектор из пар: символ - номер вершины(если вершина вопрос, то ей присваиваетс€ пор€дковый номер, иначе вершина не включаетс€ в граф)
	std::vector<std::pair<char, int>> s_template_pairs;
	s_pairs.resize(s.length());
	s_template_pairs.resize(s_template.length());

	for (int i = 0; i < s.length(); i++) //заполнение векторов
	{
		int temp;
		if (s[i] == '?')
		{
			temp = question_count_t++;
		}
		else if (s[i] == '1')
		{
			temp = 1;
		}
		else if (s[i] == '0') temp = 0;
		s_pairs[i] = std::make_pair(s[i], temp);
	}

	question_count_t = 2;
	for (int i = 0; i < s_template.length(); i++)
	{
		int temp;
		if (s_template[i] == '?')
		{
			temp = question_count_t++;
		}
		else if (s_template[i] == '1')
		{
			temp = 1;
		}
		else if (s_template[i] == '0') temp = 0;
		s_template_pairs[i] = std::make_pair(s_template[i], temp);
	}

	CMatrixGraph graph(question_amount + 2); //¬ершины графа: 0, 1 ? ?...(вопросы из template) ? ?...(вопросы из исходной строки)
	while (start_pos + s_template.length() <= s.length()) //создание графа
	{
		for (int i = start_pos, j = 0; i < start_pos + s_template.length() && j<s_template.length(); i++, j++)
		{
			if (s_template[j] == '?')
			{
				graph.AddEdge(s_template_pairs[j].second, s_pairs[i].second, 1, 0); //пр€мое ребро из вопроса шаблона
				graph.AddEdge(s_pairs[i].second, s_template_pairs[j].second, 1, 0); //обратное ребро в вопрос шаблона
			}
			else if (s[i] == '?')
			{
				graph.AddEdge(s_pairs[i].second, s_template_pairs[j].second, 1, 0);
				graph.AddEdge(s_template_pairs[j].second, s_pairs[i].second, 1, 0);
			}
		}
		start_pos++;
	}

	int ans = findMaxFlow(graph);

	std::vector<bool> used(graph.VerticesCount(), false);
	static std::vector<int> razrez;
	dfs_original(graph, razrez, 1, used); //ищем минимальный разрез (найденные вершины заполн€ем единицами в векторе пар)
	for (int i = 0; i < razrez.size(); i++)
	{
		for (int j = 0; j < s_pairs.size(); j++)
		{
			if (s_pairs[j].second == razrez[i])
			{
				s_pairs[j].first = '1';
				break;
			}
		}
		for (int j = 0; j < s_template_pairs.size(); j++)
		{
			if (s_template_pairs[j].second == razrez[i])
			{
				s_template_pairs[j].first = '1';
				break;
			}
		}
	}

	for (int j = 0; j < s_pairs.size(); j++)
	{
		if (s_pairs[j].first == '?')
		{
			s[j] = '0';
			continue;
		}
		s[j] = s_pairs[j].first;
	}
	for (int j = 0; j < s_template_pairs.size(); j++)
	{
		if (s_template_pairs[j].first == '?')
		{
			s_template[j] = '0';
			continue;
		}
		s_template[j] = s_template_pairs[j].first;
	}

	int diff = 0;
	for (int i = 0; i < s.size() - s_template.size() + 1; i++) { //считаем рассто€ние ’эмминга
		for (int j = 0; j < s_template.size(); j++) {
			char S = s[i + j];
			char P = s_template[j];
			if ((S == '1' && P == '0') || (S == '0' && P == '1')) {
				diff++;
			}
		}
	}
	return diff;
}

int main()
{
	std::string s, s_template;
	std::cin >> s >> s_template;
	int diff = solve(s, s_template);
	std::cout << diff << std::endl;
	std::cout << s << std::endl;
	std::cout << s_template;
	std::cout << std::endl;
	
}