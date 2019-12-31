#include<stdlib.h>
#include"ustr.h"
typedef struct{
uchar** vals;
size_t size;
xmangement * next;
}xmangement;
xmangement new_xmangement(uchar** keys,size_t size,size_t max_len){
  xmangement ret;
  ret.next=NULL;
  ret.size=size;
  ret.vals=(uchar**)calloc(size,sizeof(uchar*));
  if(ret.vals!=NULL){
    size_t len;
    for(size_t i=0;i<size;i=i+1){
      len=ustrnlen(*(keys+i),max_len);
      *(ret.vals+i)=(uchar*)calloc(len+1,sizeof(uchar));
      if(*(ret.vals+i)!=NULL){
        ustrcpy(*(ret.vals+i),len+1,*(keys+i));
      }else{
        
