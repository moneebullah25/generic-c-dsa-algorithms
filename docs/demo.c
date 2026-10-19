#include <stdio.h>
#include <stdlib.h>
#include "c_stack.h"
#include "c_helper.h"
#include "c_sort.h"
int main(void){
  StackInt *s=malloc(sizeof(StackInt)); StackNew(s,IntDataCompare,FreeData);
  for(int i=1;i<=4;i++) StackPush(s,i);
  StackIter *it=StackIterator(s); int sum=0;
  while(StackNext(s,it)){ printf("stack item: %d\n",*(int*)it->data); sum+=*(int*)it->data; }
  printf("sum = %d\n",sum);
  int a[]={5,2,9,1,7}; 
  QuickSort(a,sizeof(int),0,4,IntDataCompare,MemorySwap);
  printf("QuickSort:"); for(int i=0;i<5;i++) printf(" %d",a[i]); printf("\n");
  return 0;}
