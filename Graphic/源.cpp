#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
typedef enum { DG, DN, UDG, UDN } GraphKind;//有向图，有向网，无向图，无向网
#define MAX 3000
#define INFINITY 999999

typedef struct Arccell {
	int weight;//权值，无权图是0/1，有权图是权值
}AdjMatrix[MAX][MAX];

typedef struct MGraph {
	int vex[MAX];//顶点
	AdjMatrix arcs;//邻接矩阵
	int vexnum, arcnum;//当前已有的节点数和弧数
	GraphKind kind;//图类型
};

/*typedef struct Path {
	int cost;
	int path[MAX];
};*/

typedef struct Path
{
	int cost[MAX];//用于记录到第多少号节点的代价，比如cost[3]就是从出发点到3的代价
	int pathlist[MAX];//用于记录走过的路径，从1开始记录,0是起点
	int step;//用于记录走过的步数
	//int totalCost;//用于记录所有步走下来的总代价
	bool isTraveled[MAX];//用于记录这个节点是否在已知路径里面，比如isTraveled[3]=true代表3号节点已经出现在了pathlist当中

	Path():step(0)
	{
		pathlist[0] = 1;
		cost[1] = 0;
		isTraveled[1] = true;
		//totalCost = 0;
	}
};

int LCM(int a, int b)
{
	int max;
	if (a > b)
	{
		max = a;
	}
	else
	{
		max = b;
	}

	while (1)
	{
		if (max % a == 0 && max % b == 0)
		{
			return max;
		}
		else
		{
			max++;
		}
	}
}

void CreateGraph(MGraph& G)
{
	int n, m;
	cin >> n >> m;

	G.kind = UDG;
	G.vexnum = n;

	for (int i = 1; i <= G.vexnum; i++)//把1-n号点装到顶点数组里
	{
		G.vex[i] = i;
	}

	for (int a = 1; a <= G.vexnum; a++)//遍历邻接矩阵，建立联系
	{
		for (int b = 1; b <= G.vexnum; b++)
		{
			if (a == b || pow((b-a),2) > pow(m,2) )
			{
				G.arcs[a][b].weight = 0;
			}
			else
			{
				G.arcs[a][b].weight = LCM(a, b);
			}
			
		}
	}
}

void flushPath(MGraph& g, Path& path)//刷新一次路径
{
	int current = path.pathlist[path.step];//当前走到哪个节点了

	for (int i = 1; i <= g.vexnum; i++)//查找所有当前节点往前走一步能到达的地方
	{
		if (g.arcs[current][i].weight + path.cost[current] < path.cost[i] && g.arcs[current][i].weight != 0)//如果从当前节点去这个点的路径比已知的代价小
		{
			path.cost[i] = g.arcs[current][i].weight + path.cost[current];//那就把到这个节点的代价刷新为当前路径的代价
		}
	}
	
	int mincost = INFINITY;//到所有节点中代价最小的值
	int minnode = 0;//以及这个值对应的节点
	for (int i = 1; i <= g.vexnum; i++)//查找没去过的点里面代价最小的
	{
		if (path.cost[i] < mincost && path.cost[i] != 0 && path.isTraveled[i] == false)
		{
			mincost = path.cost[i];
			minnode = i;
		}
	}
	if (minnode != 0)
	{
		path.pathlist[path.step + 1] = minnode;
		path.isTraveled[minnode] = true;
		path.step++;
	}
	else
	{
		path.isTraveled[current] = true;
		path.step++;
	}
	
}

void shortPath(MGraph& g)
{
	static Path mypath;

	for (int i = 2; i <= g.vexnum; i++)
	{
		mypath.cost[i] = INFINITY;
		mypath.isTraveled[i] = false;
	}

	while (mypath.pathlist[mypath.step] != g.vexnum)//只要这个路径最后没到终点，就刷新路径
	{
		flushPath(g, mypath);
	}
	cout << mypath.cost[g.vexnum];
	
}

int testmain()
{
	static MGraph G;
	CreateGraph(G);
	/*for (int i = 1; i <= G.vexnum; i++)
	{
		for (int j = 1; j <= G.vexnum; j++)
		{
			cout << setw(3)<<G.arcs[i][j].weight<<" ";
		}
		cout << endl;
	}*/
	shortPath(G);
	system("pause");

	return 0;
}

int main()
{
	testmain();
	return 0;
}



