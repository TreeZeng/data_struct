#include <stdio.h>
#include <stdlib.h>
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

void main(){
	SqList L;
	InitList_Sq(&L);
	printf("初始化后, 当前顺序表长度为: %d\n", L.listsize);
	ListInsert_Sq(&L, 1, 10);
	ListInsert_Sq(&L, 2, 20);
	ListInsert_Sq(&L, 3, 30);
	ListInsert_Sq(&L, 4, 40);
	ListInsert_Sq(&L, 5, 50);

	printf("长度: %d\n", L.length);

	for(int i = 0; i <= L.length - 1; i++){
		printf("%d\n", L.elem[i]);
	}
}
