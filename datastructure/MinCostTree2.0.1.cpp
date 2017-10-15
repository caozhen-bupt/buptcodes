

/*����ͷ�ļ�*/

#include<iostream>
#include<algorithm>
#include<queue>

/*�����ռ�*/ 
using namespace std;

/*�궨��*/

const int MAXNUM = 20;//��󶥵��� 
const int MAXCOST = 50;//���Ȩֵ 

/*���Ͷ���*/

typedef int InfoType;
typedef int VRType;
typedef char VertexType;
typedef struct ArcCell
{
	VRType adj;
	InfoType *info;
}ArcCell, Adjmatrix[MAXNUM][MAXNUM];

/*ͼ*/ 

class Graph
{
	public:
		
		Graph()//���캯�� 
		{
			createGraph();
		}
		
		Graph(const Graph &t)//�������캯�� 
		{
			*this = t;
		}
		
		~Graph(){}//�������� 
		
		/*������������������ж��Ƿ�Ϊ��ͨͼ*/
		
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
		
		
		void createGraph()//���ڽӾ�����һ��ͼ 
		{
			cout << "Please input the number of vertex (more than 1 and no more than " << MAXNUM << ") :";
			cin >> vexnum;
			if(vexnum > MAXNUM || vexnum <= 1)//����������
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
					if(arcs[i][j].adj != arcs[j][i].adj)//��������ͼ 
					{
						cout<<"INPUT ERROR"<<endl;
						exit(2);
					}
				}
			}
			DFSTraverse();
			arcnum = arcnum/2;
			
		}
		
		
		
		/*Prim�㷨*/
		
		struct closeEdge//��¼X��Y-X�ıߵĸ�������
		{
			VertexType adjvex;
			VRType lowcost;
		}closedge[MAXNUM];
		
		int minimum(struct closeEdge closedge[])//�������С�ıߣ������±�
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
		
		/*Kruskal�㷨*/ 
		
		int find(int x)//���鼯��x�������ϣ������ĸ��ڵ� 
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
			sort(ed, ed+arcnum);//�ѱ߰�Ȩֵ��С�������� 
			cout<<"The minimal spanning tree found by Kruskal is:"<<endl;
			for(int i = 0; i < arcnum; i++)
			{
				int x = find(ed[i].u);
				int y = find(ed[i].v);
				if(x != y)//x��y����ͬһ���� 
				{
					cout << '(' << vexs[ed[i].u] << ',' << vexs[ed[i].v] << ',' << arcs[ed[i].u][ed[i].v].adj << ')' << endl;
					p[x] = y;
				}
			}
			cout<<endl;
		}
		
		
		/*��Ȧ��*/ 
		
		void findDegree()//�Ҹ�����Ķ�p[i] 
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
		
		void findBiggest(int &subi, int &subj)//�һ�·��Ȩֵ���ıߣ� subi��subj�洢�ñߵ��±� 
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
		
		void BreakCircle()//ar1�洢ɾȥ���Ȩֵ�ߺ���ڽӾ���ar2�洢ɾ���ҵ��Ķ�Ϊ1�Ķ������ڽӾ��� 
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
				if(count <= vexnum)//�л�·��ɾȥ��·��Ȩֵ���ı� 
				{					
					int subi, subj;
					findBiggest(subi, subj);
					cout << '(' << vexs[subi] << ',' << vexs[subj] << ',' << ar1[subi][subj].adj << ')' << endl;
					ar1[subi][subj].adj = 0;
					ar1[subj][subi].adj = 0;
				}
				else//û�л�·������ 
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
		VertexType vexs[MAXNUM];		//���� 
		int vexnum, arcnum;				//�������� ���� 
		Adjmatrix arcs, ar1, ar2;		//�ڽӾ��� 
		int visited[MAXNUM];			//���λ 
		struct edge{					//�� 
			int u, v, w;				//u��vΪ�ߵĶ��㣬wΪ�ߵ�Ȩֵ 
			bool operator < (const edge & rhs) const{//������������Ǳ߰�Ȩֵ���� 
				return w < rhs.w;
			}
		}ed[MAXNUM*MAXNUM];
		int p[MAXNUM];
};


/*������*/ 

int main()
{
	Graph G;
	G.Prim();
	G.Kruskal();	
	G.BreakCircle();
	return 0;
}

