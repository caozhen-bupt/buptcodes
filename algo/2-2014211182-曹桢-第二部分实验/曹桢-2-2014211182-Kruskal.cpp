/*
 *Coder：曹桢 
 *--------------------------------------------------------------
 *题目描述：输入无向图的邻接矩阵，使用Kruskal求该图的最小代价生成树
 *算法描述：Kruskal：   1、将图中所有边按权值从小到大排序；
 *						2、并查集：取权值最小的边，加入图中，判断是否形成了回路，若无，则保留此边，否则去掉该边，重取权值较小的边；
 *						3、反复过程 2，直到全部顶点均连通为止。
 */


/*包含头文件*/

#include<iostream>
#include<algorithm>
#include<queue>

/*命名空间*/ 
using namespace std;

/*宏定义*/

const int MAXNUM = 20;//最大顶点数 
const int MAXCOST = 50;//最大权值 

/*类型定义*/

typedef int InfoType;
typedef int VRType;
typedef char VertexType;
typedef struct ArcCell
{
	VRType adj;
	InfoType *info;
}ArcCell, Adjmatrix[MAXNUM][MAXNUM];

/*图*/ 

class Graph
{
	public:
		
		Graph()//构造函数 
		{
			createGraph();
		}
		
		Graph(const Graph &t)//拷贝构造函数 
		{
			*this = t;
		}
		
		~Graph(){}//析构函数 
		
		/*深度优先搜索，用于判断是否为连通图*/
		
		void DFS(int i)
		{
			visited[i] = 1;
			for(int j = 0; j < vexnum; j++)
			{
				if(arcs[i][j].adj != 0)
				{
					if(!visited[j]) DFS(j);
				}
			}
		}
		
		void DFSTraverse()
		{
			static int connect = 0;
			for(int i = 0; i < vexnum; i++)
			{
				visited[i] = 0;
			}
			for(int j = 0; j < vexnum; j++)
			{
				if(!visited[j])
				{
					DFS(j);
					connect++;
				} 
			}
			if(connect > 1)
			{
				cout<<"INPUT ERROR"<<endl;
				exit(3);
			}
		}
		
		
		void createGraph()//用邻接矩阵建立一个图 
		{
			cout << "Please input the number of vertex (more than 1 and no more than " << MAXNUM << ") :";
			cin >> vexnum;
			if(vexnum > MAXNUM || vexnum <= 1)//顶点数超过
			{
				cout << "INPUT ERROR"<<endl;
				exit(1);
			}
			cout << "Please input the name of each vertex:";
			for(int i = 0; i < vexnum; i++)
			{
				cin >> vexs[i];
				visited[i] = 0;
			} 
			cout << "Please input the adjacent matrix of this net (the cost is no more than " << MAXCOST << " and "<< '0' << "stands for no connection) :" <<endl;
			for(int i = 0; i < vexnum; i++)
			{
				for(int j = 0; j < vexnum; j++)
				{
					cin >> arcs[i][j].adj;
					if(arcs[i][j].adj != 0) arcnum++;
				}
			}
			for(int i = 0; i < vexnum; i++)
			{
				for(int j = 0; j < vexnum; j++)
				{
					if(arcs[i][j].adj != arcs[j][i].adj)//不是无向图 
					{
						cout<<"INPUT ERROR"<<endl;
						exit(2);
					}
				}
			}
			DFSTraverse();
			arcnum = arcnum/2;
			
		}
		
		
		/*Kruskal算法*/ 
		
		int find(int x)//并查集找x所属集合（树）的根节点 
		{
			return p[x] == x ? x : p[x] = find(p[x]);
		}
		
		void Kruskal()
		{
			int k;
			for(int i = 0, k=0; i < vexnum; i++)
			{
				for(int j = i; j < vexnum; j++)
				{
					if(arcs[i][j].adj != 0){
						ed[k].u = i;
						ed[k].v = j;
						ed[k].w = arcs[i][j].adj;
						k++;
					}
				}
			}
			for(int i = 0; i < vexnum; i++) p[i] = i;
			sort(ed, ed+arcnum);//把边按权值从小到大排序 
			cout<<"The minimal spanning tree found by Kruskal is:"<<endl;
			for(int i = 0; i < arcnum; i++)
			{
				int x = find(ed[i].u);
				int y = find(ed[i].v);
				if(x != y)//x和y不在同一集合 
				{
					cout << '(' << vexs[ed[i].u] << ',' << vexs[ed[i].v] << ',' << arcs[ed[i].u][ed[i].v].adj << ')' << endl;
					p[x] = y;
				}
			}
			cout<<endl;
		}
			
	private:
		VertexType vexs[MAXNUM];		//顶点 
		int vexnum, arcnum;				//顶点数， 边数 
		Adjmatrix arcs, ar1, ar2;		//邻接矩阵 
		int visited[MAXNUM];			//标记位 
		struct edge{					//边 
			int u, v, w;				//u，v为边的顶点，w为边的权值 
			bool operator < (const edge & rhs) const{//重载运算符，是边按权值排序 
				return w < rhs.w;
			}
		}ed[MAXNUM*MAXNUM];
		int p[MAXNUM];
};


/*主函数*/ 

int main()
{
	Graph G;
	G.Kruskal();
	return 0;
}

