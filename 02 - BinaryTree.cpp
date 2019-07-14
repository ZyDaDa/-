#include <iostream>
#include <malloc.h>

using namespace std; 

typedef char ElemType  ; 

//二叉树链式存储结构定义 
typedef struct BTNode{
	ElemType  data;		//数据域 
	struct BTNode *lchild;	//左孩子 
	struct BTNode *rchild;	//右孩子 
}BTNode; 


//根据前序序列，中序序列构造二叉树 
//参数：前序序列 中序序列 序列长度 
BTNode *createBT(ElemType *pre, ElemType *in, int n){
	BTNode *root = NULL;	//定义二叉树根节点     
	ElemType *p;			
	int k;
	
	if(n <= 0)	//数组长度错误 
		return NULL;
	if(pre == NULL || in == NULL)//序列空 
		return NULL;
		
	root = (BTNode*)malloc(sizeof(BTNode));	//构造根结点 
	root->data = *pre;
	
	for(p = in;p < in + n;++p)	//计算左子树长度 
		if(*p == *pre)
			break;
	k = p - in;
	
	root->lchild = createBT(pre + 1,in,k);	//递归构造左右子树 
	root->rchild = createBT(pre + 1 + k, p + 1, n - k - 1);	
	
	return root;
}

//访问函数
void visit(BTNode *p){
	//访问结点 
	cout<<p->data; 
} 

//二叉树先序遍历 - 递归 
void preorder(BTNode *p){
	if(p != NULL){
		visit(p);	//访问结点 
		preorder(p->lchild);//先序遍历左孩子结点 
		preorder(p->rchild);//先序遍历右孩子结点 
	}
}

//二叉树中序遍历 - 递归 
void inorder(BTNode *p){
	if(p != NULL){
		inorder(p->lchild);//中序遍历左孩子结点 
		visit(p);	//访问结点 
		inorder(p->rchild);//中序遍历右孩子结点 
	}
}

//二叉树中后序遍历 - 递归 
void postorder(BTNode *p){
	if(p != NULL){
		postorder(p->lchild);//后序遍历左孩子结点 
		postorder(p->rchild);//后序遍历右孩子结点 
		visit(p);	//访问结点 
	}
}



int main(int argc, char** argv) {
	
	ElemType pre[] = "ABCDEF";
	ElemType in[] = "CBAEDF";
	BTNode *a = (BTNode *)malloc(sizeof(BTNode)); 
	a = createBT(pre,in,6);
	inorder(a);
	
	
	return 0;
}
