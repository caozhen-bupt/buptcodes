

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
		
		
		
		/*Prim算法*/
		
		struct closeEdge//记录X到Y-X的边的辅助数组
		{
			VertexType adjvex;
			VRType lowcost;
		}closedge[MAXNUM];
		
		int minimum(struct closeEdge closedge[])//求代价最小的边，返回下标
		{
			int min, minsub, i;
			for(i = 1; i < vexnum; )
			{
				if(closedge[i].lowcost == 0)
				{
					i++;
				}
				else
				{
					break;
				}
			}
			if(i != vexnum && closedge[i].lowcost != 0)
			{
				min = closedge[i].lowcost;
				minsub = i;
			}
			else return -1;
			for(i = 1; i < vexnum; i++)
			{
				if(closedge[i].lowcost != 0 && closedge[i].lowcost < min)
				{
					min = closedge[i].lowcost;
					minsub = i;
				}
			}
			return minsub;
		}
		
		void Prim()
		{
			for(int i = 0; i < vexnum; i++)
			{
				visited[i] = 0;
			}
			closedge[0].lowcost = 0;
			for(int j = 1; j < vexnum; j++)
			{
				closedge[j].adjvex = vexs[0];
				closedge[j].lowcost = arcs[0][j].adj;
			}
			visited[0] = 1;
			cout<<"The minimal spanning tree found by Prim is:"<<endl;
			for(int i = 1; i < vexnum; i++)
			{
				int k = minimum(closedge);
				if( k == -1)  return;
				cout << '(' << closedge[k].adjvex << ',' << vexs[k] << ',' << closedge[k].lowcost << ')' << endl;
				visited[k] = 1;
				closedge[k].lowcost = 0;
				for(int j = 0; j < vexnum; j++)
				{
					if(visited[j] == 1) continue;
					if(arcs[k][j].adj != 0 && (arcs[k][j].adj < closedge[j].lowcost || closedge[j].lowcost == 0))
					{
						closedge[j].adjvex = vexs[k];
						closedge[j].lowcost = arcs[k][j].adj;
					}
				}
			}
			cout<<endl;
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
		
		
		/*破圈法*/ 
		
		void findDegree()//找各顶点的度p[i] 
		{
			for(int i = 0; i < vexnum; i++)
			{
				visited[i] = 0;
				p[i] = 0;
			}
			for(int i = 0; i < vexnum; i++)
			{
				for(int j = 0; j < vexnum; j++)
				{
					if(ar2[i][j].adj != 0)
					{
						p[i]++;
					}
				}
			}
		}
		
		void findBiggest(int &subi, int &subj)//找回路中权值最大的边， subi和subj存储该边的下标 
		{
			int max = 0;
			for(int i = 0; i < vexnum; i++)
			{
				for(int j = i; j < vexnum; j++)
				{
					if(max < ar2[i][j].adj)
					{
						max = ar2[i][j].adj;
						subi = i;
						subj = j;
					}
				}
			}
		}
		
		void BreakCircle()//ar1存储删去最大权值边后的邻接矩阵；ar2存储删除找到的度为1的顶点后的邻接矩阵 
		{
			int k, count = 0;
			queue<int> q;
			cout<<"The edges we remove in the BreakCircle are:"<<endl;
			for(int i = 0; i < vexnum; i++)
			{
				for(int j = 0; j < vexnum; j++)
				{
					ar1[i][j].adj = arcs[i][j].adj;
				}
			}
			
			while(1){
				for(int i = 0; i < vexnum; i++)
				{
					for(int j = 0; j < vexnum; j++)
					{
						ar2[i][j].adj = ar1[i][j].adj;
					}
				}
				findDegree();
				for(int i = 0; i < vexnum; i++)
				{
					if(p[i] == 1 && visited[i] == 0)
					{
						q.push(i);
						visited[i] = 1;
						count++;
					}
				}
				while(!q.empty())
				{
					int i = q.front();
					q.pop();
					for(int j = 0; j < vexnum; j++)
					{
						if(ar1[i][j].adj != 0)
						{
							if(--p[j] == 1)
							{
								q.push(j);
								visited[j] = 1;
								count++;
							}
							ar2[i][j].adj = 0;
							ar2[j][i].adj = 0;
						}
					}
				}
				if(count <= vexnum)//有回路，删去回路中权值最大的边 
				{					
					int subi, subj;
					findBiggest(subi, subj);
					cout << '(' << vexs[subi] << ',' << vexs[subj] << ',' << ar1[subi][subj].adj << ')' << endl;
					ar1[subi][subj].adj = 0;
					ar1[subj][subi].adj = 0;
				}
				else//没有回路，结束 
				{
					break;
				}
			}
			cout << "Finished break the circle!" << endl;
			cout << "The minimal spanning tree found by BreakCircle is:" << endl;
			for(int i = 0; i < vexnum; i++)
			{
				for(int j = i; j < vexnum; j++)
				{
					if(ar1[i][j].adj != 0)
					{
						cout << '(' << vexs[i] << ',' << vexs[j] << ',' << ar1[i][j].adj << ')' << endl;
					}
				}
			}
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
	G.Prim();
	G.Kruskal();	
	G.BreakCircle();
	return 0;
}

