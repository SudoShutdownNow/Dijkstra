#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
typedef enum { DG, DN, UDG, UDN } GraphKind;//����ͼ��������������ͼ��������
#define MAX 3000
#define INFINITY 999999

typedef struct Arccell {
	int weight;//Ȩֵ����Ȩͼ��0/1����Ȩͼ��Ȩֵ
}AdjMatrix[MAX][MAX];

typedef struct MGraph {
	int vex[MAX];//����
	AdjMatrix arcs;//�ڽӾ���
	int vexnum, arcnum;//��ǰ���еĽڵ����ͻ���
	GraphKind kind;//ͼ����
};

/*typedef struct Path {
	int cost;
	int path[MAX];
};*/

typedef struct Path
{
	int cost[MAX];//���ڼ�¼���ڶ��ٺŽڵ�Ĵ��ۣ�����cost[3]���Ǵӳ����㵽3�Ĵ���
	int pathlist[MAX];//���ڼ�¼�߹���·������1��ʼ��¼,0�����
	int step;//���ڼ�¼�߹��Ĳ���
	//int totalCost;//���ڼ�¼���в����������ܴ���
	bool isTraveled[MAX];//���ڼ�¼����ڵ��Ƿ�����֪·�����棬����isTraveled[3]=true����3�Žڵ��Ѿ���������pathlist����

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

	for (int i = 1; i <= G.vexnum; i++)//��1-n�ŵ�װ������������
	{
		G.vex[i] = i;
	}

	for (int a = 1; a <= G.vexnum; a++)//�����ڽӾ��󣬽�����ϵ
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

void flushPath(MGraph& g, Path& path)//ˢ��һ��·��
{
	int current = path.pathlist[path.step];//��ǰ�ߵ��ĸ��ڵ���

	for (int i = 1; i <= g.vexnum; i++)//�������е�ǰ�ڵ���ǰ��һ���ܵ���ĵط�
	{
		if (g.arcs[current][i].weight + path.cost[current] < path.cost[i] && g.arcs[current][i].weight != 0)//����ӵ�ǰ�ڵ�ȥ������·������֪�Ĵ���С
		{
			path.cost[i] = g.arcs[current][i].weight + path.cost[current];//�ǾͰѵ�����ڵ�Ĵ���ˢ��Ϊ��ǰ·���Ĵ���
		}
	}
	
	int mincost = INFINITY;//�����нڵ��д�����С��ֵ
	int minnode = 0;//�Լ����ֵ��Ӧ�Ľڵ�
	for (int i = 1; i <= g.vexnum; i++)//����ûȥ���ĵ����������С��
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

	while (mypath.pathlist[mypath.step] != g.vexnum)//ֻҪ���·�����û���յ㣬��ˢ��·��
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



