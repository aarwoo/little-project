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
xmangement* append_xmangement(xmangement* xm,uchar** vals,size_t vals_counts,size_t each_val_max_len){
  if(xm==NULL){
    return NULL;
  }else if(xm->vals_counts==vals_counts){
    xmangement* tmp;
    for(tmp=xm;tmp->next!=NULL;tmp=tmp->next){
      /*PASS*/
    }
    tmp->next=new_xmangement(vals,vals_counts,each_val_max_len);
    return xm;
  }else{
    return NULL;
  }
}
uchar* view_xmangement(xmangement* xm,size_t pos,uchar* key){
  if(xm==NULL){
    return NULL;
  }else{
    for(size_t i=0;i<xm->vals_counts;i=i+1){
      if(ustrcmp(*(xm->vals+i),key)==0){
        pos=pos+1;
        if(pos==0){
          return NULL;
        }else{
          while(pos!=0&&xm->next!=NULL){
            xm=xm->next;
            pos=pos-1;
          }
          if(pos==0){
            uchar * ret;
            size_t len=ustrnlen(*(xm->vals+i),SIZE_MAX);
            ret=(uchar *)calloc(len+1,sizeof(uchar));
            if(ret==NULL){
              return NULL;
            }else{
              ustrcpy(ret,len+1,*(xm->vals+i));
              return ret;
            }
          }else{
            return NULL;
          }
        }
      }else{
        /*PASS*/
      }
    }
    return NULL;
  }
}
xmangement* remove_xmangement(xmangement * xm,size_t pos){
  xmangement* tmp;
  xmangement* del;
  tmp=xm;
  pos=pos+1;
  if(pos==0){
    return xm;
  }else{
    while(pos!=1&&tmp->next!=NULL){
      tmp=tmp->next;
      pos=pos-1;
    }
    if(pos==1){
      del=tmp->next;
      if(del!=NULL){
        tmp->next=del->next;
        del->next=NULL;
        delete_xmangement(del);
        return xm;
      }else{
        return xm;
      }
    }else{
      return xm;
    }
  }
}
