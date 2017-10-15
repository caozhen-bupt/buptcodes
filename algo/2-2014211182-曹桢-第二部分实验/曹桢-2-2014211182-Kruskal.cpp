/*
 *Coder������ 
 *--------------------------------------------------------------
 *��Ŀ��������������ͼ���ڽӾ���ʹ��Kruskal���ͼ����С����������
 *�㷨������Kruskal��   1����ͼ�����б߰�Ȩֵ��С��������
 *						2�����鼯��ȡȨֵ��С�ıߣ�����ͼ�У��ж��Ƿ��γ��˻�·�����ޣ������˱ߣ�����ȥ���ñߣ���ȡȨֵ��С�ıߣ�
 *						3���������� 2��ֱ��ȫ���������ͨΪֹ��
 */


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
	G.Kruskal();
	return 0;
}

