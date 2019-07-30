#include <iostream>

#define MaxSize 10	//��󶥵���Ŀ
#define INF	10		//�ߵ����Ȩֵ 
 

//�ڽӾ��� 
typedef struct{
	int no;		//������ 
	char info;	//����������Ϣ 
}VertexType; 	//��������
typedef struct {
	int edges[MaxSize][MaxSize];//�� intΪȨֵ����
	int n,e;	//����ͱ���
	VertexType vex[MaxSize];	//��Ŷ�����Ϣ 
}MGraph;	//ͼ���ڽӾ�������	
  
//�ڽӱ� 
typedef struct ArcNode{
	int adjvex;	//�ñ���ָ�����λ�� - �������
	struct ArcNode *nextarc; //ָ����һ���ߵ�ָ��
	int info;	//�ߵ�Ȩֵ 
}ArcNode;	//�ߵĶ���
typedef struct{
	char data;	//������Ϣ
	int count;	//�������--û�õ����Բ�д 
	ArcNode *firstarc;	//ָ���һ���ߵ�ָ�� 
}VNode;	//���� 
typedef struct{
	VNode adjlist[MaxSize];	//�ڽӱ�
	int n,e;	//�������	
}AGraph;	//ͼ���ڽӱ�����  


//���������Ѱ����
int visit[MaxSize];	//���ʱ������
void Visit(int v){	//���ʺ��� 
}
void DFS(AGraph *G, int v){
	//G ����ͼ  v ������� 
	ArcNode *p;
	visit[v] = 1;	//���ʱ�� 
	Visit(v);		//���ʲ��� 
	p = G->adjlist[v].firstarc;	//pָ����ʵĵ�һ����
	while(p != NULL){
		if(visit[p->adjvex] == 0)	//������δ���� �ݹ���� 
			DFS(G, p->adjvex);
		p = p->nextarc;				//ָ����һ���� 
	} 
} 


//���������������
void BFS(AGraph *G, int v, int visit[MaxSize]){
	ArcNode *p;
	int que[MaxSize], front=0, rear=0;	//����ѭ������
	Visit(v);	//���ʽ�� 
	visit[v] = 1; 
	rear = (rear + 1)%MaxSize;			//������ 
	que[rear] = v;
	while(front != rear){				//ֱ���ӿձ������
		front = (front + 1)%MaxSize;	//��ͷ����
		p = G->adjlist[que[front]].firstarc;//ָ�����һ���� 
		while(p != NULL){	//ѭ�����ʸý�������� 
			if(visit[p->adjvex] == 0){	//���δ��������ʲ���� 
				Visit(p->adjvex);
				visit[p->adjvex] = 1;
				rear = (rear + 1)%MaxSize;
				que[rear] = p->adjvex;
			}
			p = p->nextarc;	//ָ����һ����  
		} 
	}
} 


//Prim��С����������
//��ڲ������ڽӾ���洢ͼ ��ʼ���� ���Ȩֵ 
//���Ӷȣ�	O(n^2) 
void Prim(MGraph g, int v0, int &sum){
	int lowcast[MaxSize], vset[MaxSize], v;	
	//lowcast-�洢��̱�Ȩֵ ; vser-��¼��������ʣ�ඥ�� ; v-��ʱ����
	int i, j, k, min;
	
	v = v0;	//��v0Ϊ���ڵ�������
	for(i=0; i<g.n; ++i){	//��ѭ����ʼ���������� 
		lowcast[i] = g.edges[v0][i];	//��ѡ�� 
		vset[i] = 0;	//������� 
	} 
	vset[v0] = 1;	//��v0��������
	sum = 0;		//��Ȩֵ����
	
	for(i=0; i<g.n-1; ++i){
		min = INF;	//��ʼ����С�߱���
		for(j=0; j<g.n; ++j)	//ѭ�����ҵ�ǰ��С�� 
			if(vset[j]==0 && lowcast[j]<min){	//�жϽ��δ�������� && �ߵ�Ȩֵ��С 
				min = lowcast[j];	//�滻��Сֵ 
				k = j;	//����ý�� 
			}
		vset[k] = 1;	//���ҵ���Ȩֵ��С�߲�������
		v = k;	//����滻
		sum += min;	//���Ӹ�Ȩֵ
		
		for(j=0; j<g.n; ++j)	//���½����º�ѡ�� 
			if(vset[j]==0 && g.edges[v][j]<lowcast[j])	//��v��j��������v,j�������ѡ�� 
				lowcast[j] = g.edges[v][j];
	} 
}  


//kruskal�㷨
typedef struct{
	int a, b;	//�ߵ���������
	int w;		//�ߵ�Ȩֵ 
}Road;	//�ߵĽṹ�� 
Road road[MaxSize];	//�ߵĽṹ������ 
int v[MaxSize];		//���岢�鼯����
int getRoot(int a){	//���鼯��Ѱ�Ҹ���� 
	while(a != v[a])
		a = v[a];	//�൱��˫�״洢�ṹ  
	return a;
} 
void sort(Road road[], int n){//�Գ���Ϊ n �ı߽ṹ�����Ȩֵ���� 
	//ѧ�������������� ֻ��ð�ݾͲ��׳��� 
}
//kruskal�㷨
void Kruskal(MGraph g, int &sum, Road road[]){
	int i;
	int N, E, a, b;
	N = g.n;	//������ 
	E = g.e;	//���� 
	sum = 0;	//·����ʼ��0
	for(i=0; i<N; ++i)	//��ʼ�����鼯 ȫ��ΪN�����ĸ���� 
		v[i] = i;
	sort(road, E);	//����
	for(i=0; i<E; ++i){	//ѭ��ȫ���� 
		a = getRoot(road[i].a);	//�ҵ��ñ�������ڲ��鼯�еĸ���� 
		b = getRoot(road[i].b);
		if(a != b){	//ȷ���ڲ��鼯�в���һ������ ��������· 
			v[a] = b;	//�� a b ���ڵ��������ϲ� 
			sum += road[i].w;	//·������ 
		}
	} 
} 

//Dijkstra�㷨�����·��
int dist[MaxSize];	//��������-�洢����㵽�������·������ 
int path[MaxSize];	//·������-�洢���·����ǰһ������
//Dijkstra�㷨
//��ڲ����� ����ͼ  ��ʼ���v  ��������dist  ·������path 
//�㷨���Ӷȣ� O(n^2) 
void Dijkstra(MGraph g, int v, int dist[], int path[]){
	int set[MaxSize];	//������� �Ѳ������·��Ϊ1 ����Ϊ0
	int min, i, j, u;
	for(i=0;i<g.n;++i){	//�Ը��������ʼ�� 
		dist[i] = g.edges[v][i];	//��ʼ����������Ϊ��v��i������ 
		set[i] = 0;					//���������� 
		if(g.edges[v][i] < INF)		//��v-i��ֱ����ͨ·�� ��·�������ϸý���ǰһ��������Ϊv 
			path[i] = v;
		else
			path[i] = -1; 
	} 
	set[v] = 1;		//�Կ�ʼ���v��ʼ�� 
	path[v] = -1;
	//��ʼѭ���������·�� 
	for(i=0;i<g.n-1;++i){
		min = INF;
		for(j=0;j<g.n;++j)	//�ҵ���ǰʣ�ඥ������·�� 
			if(set[j]==0 && dist[j]<INF){
				u = j;
				min = dist[j];
			}
		set[u] = 1;	//�����·���㲢��
		for(j=0;j<g.n;++j){	//���¶��㿪ʼ�������·�� 
			if(set[j]==0 && dist[u]+g.edges[u][j]<dist[j]){	//����ʱֻ���ж��½����������ľ��� 
				dist[j] = dist[u]+g.edges[u][j];
				path[j] = u;
			}
		} 		
	} 
} 

//Floyd�㷨�����·��
//��ڲ���������ͼg  �洢���·�������㾭���м������� 
void Floyd(MGraph g, int Path[][MaxSize]){
	int i, j, k;
	int A[MaxSize][MaxSize];	//�洢������������·�� 
	for(i=0; i<g.n; ++i)		//ѭ����ʼ�������� 
		for(j=0; j<g.n; ++j){
			A[i][j] = g.edges[i][j];	//A��ʼ��Ϊ�����ֱ�ӳ��� 
			Path[i][j] = -1;			//Path��ʼ��Ϊ-1 û���м�� 
		}
	 
	for(k=0; k<g.n; ++k)		//ѡ��k��Ϊ�м��			
		for(i=0; i<g.n; ++i)	//ѡ�񶥵�i 
			for(j=0; j<g.n; ++j)//ѡ�񶥵�j 
				if(A[i][j] > A[i][k]+A[k][j]){	//�ж����·�� 
					A[i][j] = A[i][k]+A[k][j];
					Path[i][j] = k;
				}
} 
 
//��������
void TopSort(AGraph *G){
	int i, j, n=0;	//����i j  ��������ʼ��0 
	int stack[MaxSize], top=-1;	//�����ʼ��ջ
	ArcNode *p;
	
	for(i=0; i<G->n; ++i)	//ѭ�������Ϊ0�Ķ�����ջ 
		if(G->adjlist[i].count == 0)
			stack[++top] = i; 
	
	while(top != -1){		//ջ��������� 
		i = stack[top--];	//ջ����ջ 
		++n;				//������++ 
		cout<<i<<" ";		//����ö��� 
		p = G->adjlist[i].firstarc;	//ָ��ö���ı� 
		while(p != NULL){	//ɾ���ö������б�Ѱ�����Ϊ0���� 
			j = p->adjvex;	//��ȡ�ñߵ�ָ��Ķ��� 
			--(G->adjlist[j].count);	//�������-1 
			if(G->adjlist[j].count == 0)//�����Ϊ0��ջ 
				stack[++top] = j;
			p = p->nextarc;	//ָ����һ���� 
		} 
	}
	if(n == G->n)	//����ɹ� 
		return 1;
	else			//ʧ�� 
		return 0;
} 

//�ڽӾ���ת�ڽӱ�
void AGraphToMGraph(AGraph g1, MGraph &g2){
	int i, j;
	ArcNode *p;
	//���ƶ������ͱ��� 
	g2.e = g1.e;
	g2.n = g1.n; 
	//��ʼ���� 
	for(i=0; i<g1.n; ++i)
		for(j=0; j<g1.n; ++j){
			if(i == j)
				g2.edges[i][j] = 0;	
			else
				g2.edges[i][j] = INF;
		} 
	//���Ʊ�Ȩֵ 
	for(i=0; i<g1.n; ++i){
		p = g1->adjlist[i].firstarc;	//ָ��ö����һ���� 
		while( p != NULL){
			g2.edges[i][p.adjvex] = p.info;	//����Ȩֵ 
			p = p.nextarc;	//ָ����һ���� 
		}
	}
}

int main(int argc, char** argv) {
	
	return 0;
}
