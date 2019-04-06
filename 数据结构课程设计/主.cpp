# include<iostream>
using namespace std;
#include<string>
#include<fstream>
#define MaxInt 10000
#define MVNum 100
typedef int ArcType;
//定义定点信息的结构体
typedef struct
{
	string name;
}point;
typedef point VerTexType;
//图的邻接矩阵存储表示
typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int pointnum,sidenum;
}AMGraph;
//文件操作，读取txt中的地图信息到电脑中
void read(AMGraph &G)
{
	ifstream ifile1,ifile2,ifile3;
	ifile1.open("顶点个数.txt");
	if(!ifile1.is_open())
	{
		cout<<"error open  file!"<<endl;
	    exit(1);
	}
	while(!ifile1.eof())
		{
			ifile1>>G.pointnum;

	}
	ifile1.close();
	ifile2.open("顶点信息.txt");
	if(!ifile2.is_open())
	{
		cout<<"error open file!"<<endl;
		exit(1);
	}
	while(!ifile2.eof())
	{
		for(int i=0;i<G.pointnum;i++)
		{
			ifile2>>G.vexs[i].name;

		}
	}
	ifile2.close();
	ifile3.open("矩阵.txt");
	int **n=new int*[G.pointnum];
	if(!ifile3.is_open())
	{
		cout<<"error open file!"<<endl;
		exit(1);
	}
	while(!ifile3.eof())
	{
		for(int i=0;i<G.pointnum;i++)
		{
			n[i]=new int[G.pointnum];
			for(int j=0;j<G.pointnum;j++)
				{
					ifile3>>n[i][j];
					G.arcs[i][j]=n[i][j];
					/*cout<<"\t\t\t\t"<<G.arcs[i][j];*/
			    }
			cout<<endl;
		}
	}
	ifile3.close();
}
//输出储存的矩阵
void showArgh(AMGraph G)
{
	for(int i=0;i<G.pointnum;i++)		
			{for(int j=0;j<G.pointnum;j++)
					cout<<"\t\t\t"<<G.arcs[i][j];	
	cout<<endl;}
}
//图的初始化
void init(AMGraph &G)
{
	read(G);
}
//迪杰斯特拉算法从某个原点到其余点的最短路径，并输出经过的中转站；
void ShortestPath_DIJ(AMGraph G,int v0)
{
	int v,i,j,w,min;
	int n=G.pointnum;
	bool *S=new bool[n];//储存是否已经确定是最短路径长度的顶点
	int *D=new int[n];//储存到vi的最短路径长度
	int *Path=new int[n];//最短路径顶点的前一个顶点的序号
	int *adss=new int[n];//记录存储在S中存储所有顶点的序号
	
	//初始化所有顶点
	for(v=0;v<n;v++)
	{
		S[v]=false;
		D[v]=G.arcs[v0][v];
		if(D[v]<MaxInt)
			Path[v]=v0;//初始化所有能到达的点，直达的距离就是最短距离，前一个顶点都是起始点
		else     
			{
				Path[v]=-1;
				
		    }
	}
	S[v0]=true;
	D[v0]=0;
	adss[v0]=v0;
	for(i=1;i<n;i++)
	{
		min=MaxInt;
		for(w=0;w<n;w++)
			if(!S[w]&&D[w]<min)
			{
				v=w;
				min=D[w];
			}
		S[v]=true;
		adss[v]=v;
		//更新从v0到剩下还未访问的顶点的最短距离
		for(w=0;w<n;w++)
			if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
		{
			D[w]=D[v]+G.arcs[v][w];
			Path[w]=v;
		
		}
	}
	for(i=0;i<n;i++)
	{
		cout<<G.vexs[v0].name<<"到"<<G.vexs[adss[i]].name<<"的最短距离为："<<D[i];
		if(Path[i]==v0||Path[i]==-1)
		{
			cout<<endl;
			continue;
		}
		cout<<"需经过中转站"<<G.vexs[Path[i]].name<<endl;
		}
		cout<<endl;
				
	}


int main()
{
	AMGraph G;
	
	init(G);
	cout<<"                       **********************************                    **********************************"<<endl;
	cout<<"                       ********************************** 欢迎使用MT导航系统 **********************************"<<endl;
	cout<<"                       ********************************** ~~~~~~~~~~~~~~~~~~ **********************************"<<endl;
	cout<<endl;
	cout<<endl;
	int n;
	cout<<"                       **********************************      目的地信息     *********************************"<<endl;
	cout<<endl;
	cout<<endl;
	for(int i=0;i<G.pointnum;i++)
		cout<<"\t\t\t\t"<<i<<"."<<G.vexs[i].name;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	int m=0;
	string o;
	cout<<"                             ***************              1. 寻找最短路径                ***************"<<endl;
	cout<<"                             **************               2. 查看目的地矩阵               **************"<<endl;
	cout<<endl;
	cout<<endl;
	while(1)
	{
		cout<<"请输入你要选择的操作："<<endl;
	cin>>m;
	switch(m)
	{
	case 1:
		{cout<<"请输入你的出发地点的前面的编号"<<endl;
		cin>>n;
		ShortestPath_DIJ(G,n);break;}
	case 2:
		{
			cout<<"输出目的地的矩阵信息"<<endl;
			showArgh(G);break;
		}
	}
	cout<<"是否继续操作，若是，请输入YES 或者yes； 若否 请输入 no"<<endl;
	cin>>o;
	if(o=="YES"||o=="yes")

		continue;
	else
		break;
	}	
	return 0;
}