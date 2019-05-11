#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define ERROR	0
#define OK		1

typedef struct{
	char *ch;	//指向动态分配存储区首地址的指针 
	int length; //串的长度 
}Str;
 
int strassign(Str *S, char *ch){
	//将串ch保存在S所指的空间
	int len = 0,i=1;
	char *c = ch;
	
	if(S->ch)
		free(S->ch);		//释放原串空间 
	while(*c){				//求串长度 
		++len;
		++c;
	}
	if(len == 0){			//若串长为零直接返回空串 
		S->ch = NULL;
		S->length = 0;
		return OK;
	}
	else{
		S->ch = (char *)malloc((len+1)*sizeof(char));//分配串长+'\0'的空间
		if(S->ch == NULL)
			return ERROR;	//内存分配失败 
		else{
			c = ch;			//重新指向首地址
			for(i=1;i<=len+1;++i){
				S->ch[i] = *c;
				++c;
			} 				//将字符串赋值 
			S->length = len;//第一个位置不存储
			S->ch[0] = S->length; 
			return OK;
		} 
	}
}

int Str_index(Str str, Str substr){
	//简单模式匹配算法
	int i=1,j=1,k=i;
	while(i<=str.length && j<=substr.length){
		if(str.ch[i] == substr.ch[j]){
			++i;	//当前字符匹配后移 
			++j;
		}
		else{		//当前不匹配k指针后移，模式串在k处从新比较 
			j=1;
			i = ++k;
		}
	}
	if(j>substr.length)
		return k;	//成功返回主串中相匹配的位置 
	else
		return 0;
} 

int KMP(Str str, Str Substr, int *next){
	//对 substr进行KMP匹配
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
	//求模式串str的next数组 
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
	//这里必须两个都要初始化 
	strassign(&s1,"aaaa1221  asaas");
	printf("字符串1为："); 
	printf(&s1.ch[1]);
	printf("\t长：%d \n",s1.length);

	strassign(&s2,"122aaaaaaaaa");
	printf("字符串2为：");
	printf(&s2.ch[1]);
	printf("\t长：%d \n",s2.length);
	
	printf("简单匹配结果为：%d \n",Str_index(s1,s2));
	getnext(s2, next);
	printf("next数组以求得\t"); 
	for(;i<4;i++)
		printf("%d",next[i]);
	putch('\n');
	
	KMP(s1,s2,next);
	//printf("KMP匹配结果为：%d \n",);
	return 0;
}
