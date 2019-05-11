#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define ERROR	0
#define OK		1

typedef struct{
	char *ch;	//ָ��̬����洢���׵�ַ��ָ�� 
	int length; //���ĳ��� 
}Str;
 
int strassign(Str *S, char *ch){
	//����ch������S��ָ�Ŀռ�
	int len = 0,i=1;
	char *c = ch;
	
	if(S->ch)
		free(S->ch);		//�ͷ�ԭ���ռ� 
	while(*c){				//�󴮳��� 
		++len;
		++c;
	}
	if(len == 0){			//������Ϊ��ֱ�ӷ��ؿմ� 
		S->ch = NULL;
		S->length = 0;
		return OK;
	}
	else{
		S->ch = (char *)malloc((len+1)*sizeof(char));//���䴮��+'\0'�Ŀռ�
		if(S->ch == NULL)
			return ERROR;	//�ڴ����ʧ�� 
		else{
			c = ch;			//����ָ���׵�ַ
			for(i=1;i<=len+1;++i){
				S->ch[i] = *c;
				++c;
			} 				//���ַ�����ֵ 
			S->length = len;//��һ��λ�ò��洢
			S->ch[0] = S->length; 
			return OK;
		} 
	}
}

int Str_index(Str str, Str substr){
	//��ģʽƥ���㷨
	int i=1,j=1,k=i;
	while(i<=str.length && j<=substr.length){
		if(str.ch[i] == substr.ch[j]){
			++i;	//��ǰ�ַ�ƥ����� 
			++j;
		}
		else{		//��ǰ��ƥ��kָ����ƣ�ģʽ����k�����±Ƚ� 
			j=1;
			i = ++k;
		}
	}
	if(j>substr.length)
		return k;	//�ɹ�������������ƥ���λ�� 
	else
		return 0;
} 

int KMP(Str str, Str Substr, int *next){
	//�� substr����KMPƥ��
	int i=1,j=1;
	while(i<=str.length && j<=Substr.length){ 
		if(j==0 || str.ch[i] == Substr.ch[j]){
			++i;
			++j;
		}
		else{
			j = next[j];
			printf("%d\t",i);			
		}
	} 
	if(j>Substr.length)
		return i-Substr.length;
	else 
		return 0;
}

void getnext(Str str, int *next){
	//��ģʽ��str��next���� 
	int i=1,j=0;
	next[0] = str.length;
	next[1] = 0;
	while(i<str.length+1){
		if(j==0 || str.ch[i] == str.ch[j]){
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

int main(int argc, char *argv[]) {
	Str s1 = {NULL,0},s2 = {NULL,0};
	int next[4]; 
	int i=0;
	//�������������Ҫ��ʼ�� 
	strassign(&s1,"aaaa1221  asaas");
	printf("�ַ���1Ϊ��"); 
	printf(&s1.ch[1]);
	printf("\t����%d \n",s1.length);

	strassign(&s2,"122aaaaaaaaa");
	printf("�ַ���2Ϊ��");
	printf(&s2.ch[1]);
	printf("\t����%d \n",s2.length);
	
	printf("��ƥ����Ϊ��%d \n",Str_index(s1,s2));
	getnext(s2, next);
	printf("next���������\t"); 
	for(;i<4;i++)
		printf("%d",next[i]);
	putch('\n');
	
	KMP(s1,s2,next);
	//printf("KMPƥ����Ϊ��%d \n",);
	return 0;
}
