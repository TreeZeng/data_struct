#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "self_defination.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

typedef struct {
	ElemType *elem;
	int length; // 当前长度
	int listsize; //最大长度
} SqList;

Status InitList_Sq(SqList *L) {
	L -> elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (! L -> elem){
		exit(OVERFLOW);
	}
	L -> length = 0;
	L -> listsize = LIST_INIT_SIZE;
	return OK;
}

Status ListInsert_Sq(SqList *L, int i, ElemType e) {
	ElemType *q;

	// 参数校验
	if (i < 1 || i > L -> length + 1) {
		return ERROR;
	}
	// 扩容
	if (L -> length >= L -> listsize) {
		ElemType *newbase = (ElemType *) realloc(L -> elem, (L -> listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase) {
			exit(OVERFLOW);
		}
		L -> elem = newbase;
		L -> listsize += LISTINCREMENT;
	}
	// 1. 元素后移
	q = &(L -> elem[i-1]);
	for(ElemType *p = &(L -> elem[L -> length - 1]); p >= q; --p){
		*(p+1) = *p;
	}
	// 2. 插入元素
	*q = e;
	++(L -> length);

	return OK;
}

Status DeleteInsert_Sq(SqList *L, int i) {
	// 参数校验
	if (i < 1 || i > L -> length + 1)	{
		return ERROR;
	}
	// 长度判断
	if (L -> length == 0) {
		return ERROR;
	}

	// 1. 元素前移
	ElemType *q = &(L -> elem[i-1]);
	ElemType *p = &(L -> elem[L -> length - 1]);
	for (; q <= p; q++){
		*(q) = *(q+1);
	}
	--(L -> length);

	return OK;
}

void BubleSort_Sq(SqList *L) {
	int length = L -> length - 1;
	int swapVar;
	for (int i = 0; i < length; i++){
		for (int j = 0; j < length - i; j++){
			if(L -> elem[j] > L -> elem[j+1]){
				swapVar = L -> elem[j];
				L -> elem[j] = L -> elem[j+1];
				L -> elem[j+1] = swapVar;	
			}
		}
	}	
}

int LocateElem_Sq(SqList *L, ElemType e){
	int i = 1;
	ElemType *p = &(L -> elem[0]);
	
	while(i < L -> length){
		if(*p++ <= e){
			++i;
		}else{
			break;
		}
	}
	return i;
}

int GetElem_Sq(SqList *L, int i) {
	return L -> elem[i-1];
}

void main(){
	SqList L;
	InitList_Sq(&L);
	printf("初始化后, 当前顺序表大小为: %d; 长度为: %d\n", L.listsize, L.length);
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++){
		ListInsert_Sq(&L, 1, rand() % 100);
	}
	
	BubleSort_Sq(&L);
	printf("情况如下: \n");
	for(int i = 0; i <= L.length - 1; i++){
		printf("%d: %d\n", i+1, L.elem[i]);
	}

	int DeleteIndex;
	while (1) {
		printf("请输入要删除的元素下标: ");
		scanf("%d", &DeleteIndex);
		DeleteInsert_Sq(&L, DeleteIndex);
		printf("删除后: \n");
		for(int i = 0; i <= L.length - 1; i++){
			printf("%d: %d\n", i+1, L.elem[i]);
		}
	}

}
