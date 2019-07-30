#include <iostream>

#define MaxSize 10	//最大顶点数目
#define INF	10		//边的最大权值 
 

//邻接矩阵 
typedef struct{
	int no;		//顶点编号 
	char info;	//顶点其他信息 
}VertexType; 	//定点类型
typedef struct {
	int edges[MaxSize][MaxSize];//边 int为权值类型
	int n,e;	//顶点和边数
	VertexType vex[MaxSize];	//存放顶点信息 
}MGraph;	//图的邻接矩阵类型	
  
//邻接表 
typedef struct ArcNode{
	int adjvex;	//该边所指向结点的位置 - 数组序号
	struct ArcNode *nextarc; //指向下一条边的指针
	int info;	//边的权值 
}ArcNode;	//边的定义
typedef struct{
	char data;	//顶点信息
	int count;	//顶点入度--没用到可以不写 
	ArcNode *firstarc;	//指向第一条边的指针 
}VNode;	//顶点 
typedef struct{
	VNode adjlist[MaxSize];	//邻接表
	int n,e;	//顶点边数	
}AGraph;	//图的邻接表类型  


//深度优先搜寻遍历
int visit[MaxSize];	//访问标记数组
void Visit(int v){	//访问函数 
}
void DFS(AGraph *G, int v){
	//G 搜索图  v 搜索结点 
	ArcNode *p;
	visit[v] = 1;	//访问标记 
	Visit(v);		//访问操作 
	p = G->adjlist[v].firstarc;	//p指向访问的第一条边
	while(p != NULL){
		if(visit[p->adjvex] == 0)	//若顶点未访问 递归访问 
			DFS(G, p->adjvex);
		p = p->nextarc;				//指向下一条边 
	} 
} 


//广度优先搜索遍历
void BFS(AGraph *G, int v, int visit[MaxSize]){
	ArcNode *p;
	int que[MaxSize], front=0, rear=0;	//定义循环队列
	Visit(v);	//访问结点 
	visit[v] = 1; 
	rear = (rear + 1)%MaxSize;			//结点入队 
	que[rear] = v;
	while(front != rear){				//直到队空遍历完成
		front = (front + 1)%MaxSize;	//对头出队
		p = G->adjlist[que[front]].firstarc;//指向结点第一条边 
		while(p != NULL){	//循环访问该结点其他边 
			if(visit[p->adjvex] == 0){	//结点未访问则访问并入队 
				Visit(p->adjvex);
				visit[p->adjvex] = 1;
				rear = (rear + 1)%MaxSize;
				que[rear] = p->adjvex;
			}
			p = p->nextarc;	//指向下一条边  
		} 
	}
} 


//Prim最小代价生成树
//入口参数：邻接矩阵存储图 开始顶点 输出权值 
//复杂度：	O(n^2) 
void Prim(MGraph g, int v0, int &sum){
	int lowcast[MaxSize], vset[MaxSize], v;	
	//lowcast-存储最短边权值 ; vser-记录生成树的剩余顶点 ; v-临时顶点
	int i, j, k, min;
	
	v = v0;	//以v0为根节点生成树
	for(i=0; i<g.n; ++i){	//此循环初始化两个数组 
		lowcast[i] = g.edges[v0][i];	//侯选边 
		vset[i] = 0;	//将树清空 
	} 
	vset[v0] = 1;	//将v0并入树中
	sum = 0;		//将权值清零
	
	for(i=0; i<g.n-1; ++i){
		min = INF;	//初始化最小边变量
		for(j=0; j<g.n; ++j)	//循环查找当前最小边 
			if(vset[j]==0 && lowcast[j]<min){	//判断结点未被并入树 && 边的权值最小 
				min = lowcast[j];	//替换最小值 
				k = j;	//保存该结点 
			}
		vset[k] = 1;	//将找到的权值最小边并入树中
		v = k;	//结点替换
		sum += min;	//增加该权值
		
		for(j=0; j<g.n; ++j)	//在新结点更新侯选边 
			if(vset[j]==0 && g.edges[v][j]<lowcast[j])	//若v到j结点最短则（v,j）并入侯选边 
				lowcast[j] = g.edges[v][j];
	} 
}  


//kruskal算法
typedef struct{
	int a, b;	//边的两个顶点
	int w;		//边的权值 
}Road;	//边的结构体 
Road road[MaxSize];	//边的结构体数组 
int v[MaxSize];		//定义并查集数组
int getRoot(int a){	//并查集中寻找根结点 
	while(a != v[a])
		a = v[a];	//相当于双亲存储结构  
	return a;
} 
void sort(Road road[], int n){//对长度为 n 的边结构体根据权值排序 
	//学完排序再来补充 只会冒泡就不献丑了 
}
//kruskal算法
void Kruskal(MGraph g, int &sum, Road road[]){
	int i;
	int N, E, a, b;
	N = g.n;	//顶点数 
	E = g.e;	//边数 
	sum = 0;	//路径初始化0
	for(i=0; i<N; ++i)	//初始化并查集 全部为N个树的根结点 
		v[i] = i;
	sort(road, E);	//排序
	for(i=0; i<E; ++i){	//循环全部边 
		a = getRoot(road[i].a);	//找到该边两结点在并查集中的根结点 
		b = getRoot(road[i].b);
		if(a != b){	//确保在并查集中不在一棵树内 不产生回路 
			v[a] = b;	//将 a b 所在的两棵树合并 
			sum += road[i].w;	//路径增加 
		}
	} 
} 

//Dijkstra算法求最短路径
int dist[MaxSize];	//距离数组-存储根结点到其余结点的路径长度 
int path[MaxSize];	//路径数组-存储最短路径的前一个顶点
//Dijkstra算法
//入口参数： 所求图  起始结点v  距离数组dist  路径数组path 
//算法复杂度： O(n^2) 
void Dijkstra(MGraph g, int v, int dist[], int path[]){
	int set[MaxSize];	//标记数组 已并入最短路径为1 否则为0
	int min, i, j, u;
	for(i=0;i<g.n;++i){	//对各个数组初始化 
		dist[i] = g.edges[v][i];	//初始化距离数组为（v，i）长度 
		set[i] = 0;					//标记数组清空 
		if(g.edges[v][i] < INF)		//若v-i有直接联通路径 则将路径数组上该结点的前一个顶点设为v 
			path[i] = v;
		else
			path[i] = -1; 
	} 
	set[v] = 1;		//对开始结点v初始化 
	path[v] = -1;
	//开始循环查找最短路径 
	for(i=0;i<g.n-1;++i){
		min = INF;
		for(j=0;j<g.n;++j)	//找到当前剩余顶点的最短路径 
			if(set[j]==0 && dist[j]<INF){
				u = j;
				min = dist[j];
			}
		set[u] = 1;	//将最短路径点并入
		for(j=0;j<g.n;++j){	//以新顶点开始更新最短路径 
			if(set[j]==0 && dist[u]+g.edges[u][j]<dist[j]){	//更新时只需判断新结点与其余结点的距离 
				dist[j] = dist[u]+g.edges[u][j];
				path[j] = u;
			}
		} 		
	} 
} 

//Floyd算法求最短路径
//入口参数：所求图g  存储最短路径两顶点经过中间点的数组 
void Floyd(MGraph g, int Path[][MaxSize]){
	int i, j, k;
	int A[MaxSize][MaxSize];	//存储任意两结点最短路径 
	for(i=0; i<g.n; ++i)		//循环初始化两数组 
		for(j=0; j<g.n; ++j){
			A[i][j] = g.edges[i][j];	//A初始化为两结点直接长度 
			Path[i][j] = -1;			//Path初始化为-1 没有中间点 
		}
	 
	for(k=0; k<g.n; ++k)		//选择k作为中间点			
		for(i=0; i<g.n; ++i)	//选择顶点i 
			for(j=0; j<g.n; ++j)//选择顶点j 
				if(A[i][j] > A[i][k]+A[k][j]){	//判断最短路径 
					A[i][j] = A[i][k]+A[k][j];
					Path[i][j] = k;
				}
} 
 
//拓扑排序
void TopSort(AGraph *G){
	int i, j, n=0;	//变量i j  计算器初始化0 
	int stack[MaxSize], top=-1;	//定义初始化栈
	ArcNode *p;
	
	for(i=0; i<G->n; ++i)	//循环将入度为0的顶点入栈 
		if(G->adjlist[i].count == 0)
			stack[++top] = i; 
	
	while(top != -1){		//栈空排序完成 
		i = stack[top--];	//栈顶出栈 
		++n;				//计数器++ 
		cout<<i<<" ";		//输出该顶点 
		p = G->adjlist[i].firstarc;	//指向该顶点的边 
		while(p != NULL){	//删除该顶点所有边寻找入度为0顶点 
			j = p->adjvex;	//获取该边的指向的顶点 
			--(G->adjlist[j].count);	//定点入度-1 
			if(G->adjlist[j].count == 0)//若入度为0入栈 
				stack[++top] = j;
			p = p->nextarc;	//指向下一条边 
		} 
	}
	if(n == G->n)	//排序成功 
		return 1;
	else			//失败 
		return 0;
} 

//邻接矩阵转邻接表
void AGraphToMGraph(AGraph g1, MGraph &g2){
	int i, j;
	ArcNode *p;
	//复制顶点数和边数 
	g2.e = g1.e;
	g2.n = g1.n; 
	//初始化边 
	for(i=0; i<g1.n; ++i)
		for(j=0; j<g1.n; ++j){
			if(i == j)
				g2.edges[i][j] = 0;	
			else
				g2.edges[i][j] = INF;
		} 
	//复制边权值 
	for(i=0; i<g1.n; ++i){
		p = g1->adjlist[i].firstarc;	//指向该顶点第一个边 
		while( p != NULL){
			g2.edges[i][p.adjvex] = p.info;	//复制权值 
			p = p.nextarc;	//指向下一条边 
		}
	}
}

int main(int argc, char** argv) {
	
	return 0;
}
