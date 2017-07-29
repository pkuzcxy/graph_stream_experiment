#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include<map>
#include<vector>
using namespace std;
struct edge
{
	int n;
	edge* next;
	int label;
	int weight;
};

class graph
{
private:
	int n;
	int max_d;
	int N;
public:
	vector<string> node;
	map<string, int> index;
	vector<edge*> g;
	graph();
	~graph() {
		vector<string>().swap(node);
		vector<edge*>().swap(g);
		index.clear();
	}
	void insert(string s1, string s2, int label, int weight);
	int query(string s1, string s2, int label);
	int	get_nodenum();
	int get_edgenum();
	int get_max_d();
	bool BFS(int begin, int end);

};

graph::graph()
{
	n = 0;
	max_d = 0;
	N = 0;
}
int graph::get_max_d()
{
	return max_d;
}
int graph::get_nodenum()
{
	return n;
}
int graph::get_edgenum()
{
	return N;
}
void graph::insert(string s1, string s2, int l, int w)
{
	int n1, n2;
	map<string, int>::iterator it;
	it = index.find(s1);
	if (it != index.end())
		n1 = it->second;
	else
	{
		node.push_back(s1);
		index[s1] = n;
		n1 = n;
		n++;
		edge *e = new edge;
		e->next = NULL;
		e->n = n1;
		e->weight = 0;
		e->label = 0;
		g.push_back(e);
	}
	it = index.find(s2);
	if (it != index.end())
		n2 = it->second;
	else
	{
		node.push_back(s2);
		index[s2] = n;
		n2 = n;
		n++;
		edge *e = new edge;
		e->next = NULL;
		e->n = n2;
		e->weight = 0;
		e->label = 0;
		g.push_back(e);
	}
	edge* e = g[n1];
	int length = 0;
	bool find = false;
	while (true)
	{
		//length++;
		if (e->n == n2&&e->label == l)
		{
			e->weight += w;
			find = true;
			break;
		}
		if (e->next == NULL)
			break;
		e = e->next;
		length++;
	}
	if (!find)
	{
		N++;
		edge* f = new edge;
		f->label = l;
		f->n = n2;
		f->weight = w;
		f->next = NULL;
		e->next = f;
		length++;
		if (length>max_d)
			max_d = length;
	}
}

int graph::query(string s1, string s2, int label)
{
	map<string, int>::iterator it;
	int n1, n2;
	it = index.find(s1);
	if (it != index.end())
		n1 = it->second;
	else return 0;
	it = index.find(s2);
	if (it != index.end())
		n2 = it->second;
	else return 0;
	edge* e = g[n1];
	while (e != NULL)
	{
		if (e->n == n2&&e->label == label)
			return e->weight;
		e = e->next;
	}
	if (e == NULL)
		return 0;
}


bool graph::BFS(int begin,int end)
{

	if (begin == end) return true;
	queue<int> Q;
	map<int, int> nodeStatus;
	Q.push(begin);
	bool access = false;
	while (!Q.empty() && !access)
	{
		int u = Q.front();
		Q.pop();
		nodeStatus.insert(make_pair(u, 1));
		edge * e = g[u];
		while (e->next != NULL)
		{
			e = e->next;
			if (e->n == end)
			{
				access = true;
				break;
			}
			if (nodeStatus.find(e->n)==nodeStatus.end())
			Q.push(e->n);
		}
	}
	return access;
}