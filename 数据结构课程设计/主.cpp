# include<iostream>
using namespace std;
#include<string>
#include<fstream>
#define MaxInt 10000
#define MVNum 100
typedef int ArcType;
//���嶨����Ϣ�Ľṹ��
typedef struct
{
	string name;
}point;
typedef point VerTexType;
//ͼ���ڽӾ���洢��ʾ
typedef struct
{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int pointnum,sidenum;
}AMGraph;
//�ļ���������ȡtxt�еĵ�ͼ��Ϣ��������
void read(AMGraph &G)
{
	ifstream ifile1,ifile2,ifile3;
	ifile1.open("�������.txt");
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
	ifile2.open("������Ϣ.txt");
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
	ifile3.open("����.txt");
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
//�������ľ���
void showArgh(AMGraph G)
{
	for(int i=0;i<G.pointnum;i++)		
			{for(int j=0;j<G.pointnum;j++)
					cout<<"\t\t\t"<<G.arcs[i][j];	
	cout<<endl;}
}
//ͼ�ĳ�ʼ��
void init(AMGraph &G)
{
	read(G);
}
//�Ͻ�˹�����㷨��ĳ��ԭ�㵽���������·�����������������תվ��
void ShortestPath_DIJ(AMGraph G,int v0)
{
	int v,i,j,w,min;
	int n=G.pointnum;
	bool *S=new bool[n];//�����Ƿ��Ѿ�ȷ�������·�����ȵĶ���
	int *D=new int[n];//���浽vi�����·������
	int *Path=new int[n];//���·�������ǰһ����������
	int *adss=new int[n];//��¼�洢��S�д洢���ж�������
	
	//��ʼ�����ж���
	for(v=0;v<n;v++)
	{
		S[v]=false;
		D[v]=G.arcs[v0][v];
		if(D[v]<MaxInt)
			Path[v]=v0;//��ʼ�������ܵ���ĵ㣬ֱ��ľ��������̾��룬ǰһ�����㶼����ʼ��
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
		//���´�v0��ʣ�»�δ���ʵĶ������̾���
		for(w=0;w<n;w++)
			if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
		{
			D[w]=D[v]+G.arcs[v][w];
			Path[w]=v;
		
		}
	}
	for(i=0;i<n;i++)
	{
		cout<<G.vexs[v0].name<<"��"<<G.vexs[adss[i]].name<<"����̾���Ϊ��"<<D[i];
		if(Path[i]==v0||Path[i]==-1)
		{
			cout<<endl;
			continue;
		}
		cout<<"�辭����תվ"<<G.vexs[Path[i]].name<<endl;
		}
		cout<<endl;
				
	}


int main()
{
	AMGraph G;
	
	init(G);
	cout<<"                       **********************************                    **********************************"<<endl;
	cout<<"                       ********************************** ��ӭʹ��MT����ϵͳ **********************************"<<endl;
	cout<<"                       ********************************** ~~~~~~~~~~~~~~~~~~ **********************************"<<endl;
	cout<<endl;
	cout<<endl;
	int n;
	cout<<"                       **********************************      Ŀ�ĵ���Ϣ     *********************************"<<endl;
	cout<<endl;
	cout<<endl;
	for(int i=0;i<G.pointnum;i++)
		cout<<"\t\t\t\t"<<i<<"."<<G.vexs[i].name;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	int m=0;
	string o;
	cout<<"                             ***************              1. Ѱ�����·��                ***************"<<endl;
	cout<<"                             **************               2. �鿴Ŀ�ĵؾ���               **************"<<endl;
	cout<<endl;
	cout<<endl;
	while(1)
	{
		cout<<"��������Ҫѡ��Ĳ�����"<<endl;
	cin>>m;
	switch(m)
	{
	case 1:
		{cout<<"��������ĳ����ص��ǰ��ı��"<<endl;
		cin>>n;
		ShortestPath_DIJ(G,n);break;}
	case 2:
		{
			cout<<"���Ŀ�ĵصľ�����Ϣ"<<endl;
			showArgh(G);break;
		}
	}
	cout<<"�Ƿ�������������ǣ�������YES ����yes�� ���� ������ no"<<endl;
	cin>>o;
	if(o=="YES"||o=="yes")

		continue;
	else
		break;
	}	
	return 0;
}