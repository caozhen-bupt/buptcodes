#include <iostream>
#include <cstring>
using namespace std;

class Traveling{
private:
	friend int TSP(int**,int*,int,int); 
	void backTrack(int i);
	int city;
	int* x;//当前旅行策略
	int* bestx;//最优旅行策略
	int** a; 
	int cc;//当前代价
	int bestc;//存放最小代价值
	int NoEdge;//不连通的标志，这里设为-1
};

void Traveling::backTrack(int i)
{
	if(i == city){ 
		if(a[x[city-1]][x[city]] != NoEdge && a[x[city]][1] != NoEdge && (cc + a[x[city-1]][x[city]] + a[x[city]][1] < bestc || bestc == NoEdge))
		{
			bestc = cc + a[x[city-1]][x[city]] + a[x[city]][1];
			for(int j = 1; j <= city; j++)
				bestx[j] = x[j];
		}	
	}else{
		for(int j=1;j<=city;j++)
			if(a[x[i-1]][x[j]] != NoEdge && (cc +a[x[i-1]][x[i]]<bestc || bestc==NoEdge))
			{
				swap(x[i], x[j]);
				cc += a[x[i - 1]][x[i]];
				backTrack(i + 1);
				cc -= a[x[i - 1]][x[i]];
				swap(x[i], x[j]);
			}
	}
}   

int TSP(int** a,int* bestPath,int city,int NoEdge)
{
	Traveling Y;
	Y.x = new int[city + 1];
	for(int i = 1; i <= city; i++)
		Y.x[i] = i;
	Y.a = a;
	Y.city = city;
	Y.bestc = NoEdge; 
	Y.bestx = bestPath;
	Y.cc = 0;
	Y.NoEdge = NoEdge;
	Y.backTrack(2); 
	delete[] Y.x;
	return Y.bestc;
}

int main()
{
	int **map;
	int * bestpath;
	int n;
	cin >> n; 
	map = new int*[n];
	for(int i = 0; i < n; i++)
	{
		map[i] = new int[n];
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> map[i][j];
		}
	}
	bestpath = new int[n];
	memset(bestpath, 0, sizeof(bestpath));
	cout << "The min cost: " << TSP(map, bestpath, n-1,-1) << endl;
	return 0;
}
