#include<stdlib.h>
#include"ustr.h"
typedef struct{
uchar** vals;
size_t vals_counts;
xmangement * next;
}xmangement;
xmangement* delete_xmangement(xmangement* xm){
  xmangement * tmp;
  while(xm!=NULL){
    for(size_t i=0;i<xm->vals_counts;i=i+1){
      free(*(xm->vals+i));
      *(xm->vals+i)=NULL;
    }
    free(xm->vals);
    xm->vals=NULL;
    xm->vals_counts=0;
    tmp=xm->next;
    xm->next=NULL;
    free(xm);
    xm=tmp;
  }
  return NULL;
}
xmangement* new_xmangement(uchar** keys,size_t keys_counts,size_t each_key_max_len){
  xmangement* ret;
  ret=(xmangement*)calloc(1,sizeof(xmangement));
  if(ret!=NULL){
    ret->next=NULL;
    ret->vals_counts=keys_counts;
    ret->vals=(uchar**)calloc(keys_counts,sizeof(uchar*));
    if(ret->vals!=NULL){
      size_t len;
      for(size_t i=0;i<keys_counts;i=i+1){
        len=ustrnlen(*(keys+i),each_key_max_len);
        *(ret->vals+i)=(uchar*)calloc(len+1,sizeof(uchar));
        if(*(ret->vals+i)!=NULL){
          ustrcpy(*(ret.vals+i),len+1,*(keys+i));
        }else{
          ret=delete_xmangement(ret);
          break;
        }
      }
    }else{
      ret=delete_xmangement(ret);
    }
  }else{
    ret=delete_xmangement(ret);
  }
  return ret;
}
