#include<stdlib.h>
#include"ustr.h"
typedef struct{
uchar** vals;
size_t size;
xmangement * next;
}xmangement;
xmangement new_xmangement(uchar**keys,size_t size){
  xmangement ret;
  ret.next=NULL;
  ret.size=size;
  ret.vals=(uchar**)calloc(size,sizeof(uchar*));
  if(ret.vals!=NULL){
    for(size_t i=0;i<size;i=i+1){
      *(ret.vals+i)=(uchar**)calloc(
