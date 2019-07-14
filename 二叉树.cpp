#include <iostream>
#include <malloc.h>

using namespace std; 

typedef char ElemType  ; 

//��������ʽ�洢�ṹ���� 
typedef struct BTNode{
	ElemType  data;		//������ 
	struct BTNode *lchild;	//���� 
	struct BTNode *rchild;	//�Һ��� 
}BTNode; 


//����ǰ�����У��������й�������� 
//������ǰ������ �������� ���г��� 
BTNode *createBT(ElemType *pre, ElemType *in, int n){
	BTNode *root = NULL;	//������������ڵ�     
	ElemType *p;			
	int k;
	
	if(n <= 0)	//���鳤�ȴ��� 
		return NULL;
	if(pre == NULL || in == NULL)//���п� 
		return NULL;
		
	root = (BTNode*)malloc(sizeof(BTNode));	//�������� 
	root->data = *pre;
	
	for(p = in;p < in + n;++p)	//�������������� 
		if(*p == *pre)
			break;
	k = p - in;
	
	root->lchild = createBT(pre + 1,in,k);	//�ݹ鹹���������� 
	root->rchild = createBT(pre + 1 + k, p + 1, n - k - 1);	
	
	return root;
}

//���ʺ���
void visit(BTNode *p){
	//���ʽ�� 
	cout<<p->data; 
} 

//������������� - �ݹ� 
void preorder(BTNode *p){
	if(p != NULL){
		visit(p);	//���ʽ�� 
		preorder(p->lchild);//����������ӽ�� 
		preorder(p->rchild);//��������Һ��ӽ�� 
	}
}

//������������� - �ݹ� 
void inorder(BTNode *p){
	if(p != NULL){
		inorder(p->lchild);//����������ӽ�� 
		visit(p);	//���ʽ�� 
		inorder(p->rchild);//��������Һ��ӽ�� 
	}
}

//�������к������ - �ݹ� 
void postorder(BTNode *p){
	if(p != NULL){
		postorder(p->lchild);//����������ӽ�� 
		postorder(p->rchild);//��������Һ��ӽ�� 
		visit(p);	//���ʽ�� 
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
