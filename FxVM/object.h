#ifndef object_h
#define object_h
#include<vector>
#include<unordered_map>
#include<string>
class __object{
  public:
    virtual ~__object(){
      /*PASS*/
    }
    virtual std::string type(){
      return "?";
    }
    virtual std::string tostr(){
      return "";
    }
    virtual __object * calc(std::string _operator);
    virtual __object * calc(std::string _operator,__object * another);
}
class object{
  private:
    __object * val;
  public:
    object(){
      this->val=new __object;
    }
    ~object(){
      delete this->val;
    }
    std::string type(){
      return this->val->type();
    }
    std::string tostr(){
      return this->val->tostr();
    }
    object setval(__object * val){
      delete this->val;
      this->val=val;
    }
    object calc(std::string _operator){
      return (new object)->setval(this->val->calc(_operator));
    }
    object calc(std::string _operator,object another){
      return (new object)->setval(this->val->calc(_operator,another.val));
    }
}
#include"expression.h"
class _bool: public __object{
  private:
    bool val;
  public:
    std::string type(){
      return "_bool";
    }
    _bool * setval(bool val){
      this->val=val;
      return this;
    }
    __object * calc(std::string _operator){
      if(_operator=="-"){
        return (new _bool)->setval(!this->val);
      }else if(_operator=="?"){
        return (new _bool)->setval(true);
      }else{
        return (new _bool)->setval(this->val);
      }
    }
    __object * calc(std::string _operator,__object * another){
      _bool * tmp=dynamic_cast<_bool *>(another);
      if(tmp!=nullptr){
        if(_operator=="\\/"){
          return (new _bool)->setval(this->val||tmp->val);
        }else if(_operator=="/\\"){
          return (new _bool)->setval(this->val&&tmp->val);
        }else{
          return (new _bool)->setval(this->val);
        }
      }else{
        return this->calc(_operator,(new _bool)->setval(false));
      }
}
class _err: public __object{
  private:
    std::string val;
  public:
    std::string type(){
      return "_err";
    }
    std::string tostr(){
      return this->val;
    }
    _err * setval(std::string val){
      this->val=val;
      return this;
    }
    __object * calc(std::string _operator){
      if(_operator=="?"){
        return (new _bool)->setval(true);
      }else{
        return (new _err)->setval(_operator+this->type()+" is underfined.");
      }
    }
    __object * calc(std::string _operator,__object * another){
      _err * tmp=dynamic_cast<_err *>(another);
      if(tmp!=nullptr){
        if(_operator=="+"){
          return (new _err)->setval(this->val+"\n\n"+tmp->val);
        }else if(_ooperator=="="){
          return (new _bool)->setval(this->val==tmp->val);
        }else{
          return this->calc("+",tmp)->calc("+",(new _err)->setval(this->type()+_operator+tmp->type()+" is underfined.");
        }
      }else{
        return this->calc("+",(new _err)->setval(this->type()+_operator+tmp->type()+" is underfined.");
      }
    }
}
class _str: public __object{
  private:
    std::string val;
  public:
    std::string type(){
      return "_err";
    }
    std::string tostr(){
      return this->val;
    }
    _str * setval(std::string val){
      this->val=val;
      return this;
    }
    __object * calc(std::string _operator){
      if(_operator=="?"){
        return (new _bool)->setval(true);
      }else{
        return (new _err)->setval(_operator+this->type()+" is underfined.");
      }
    }
    __object * calc(std::string _operator,__object * another){
      _str * tmp=dynamic_cast<_str *>(another);
      if(tmp!=nullptr){
        if(_operator=="+"){
          return (new _str)->setval(this->val+tmp->val);
        }else if(_operator=="<"){
          return (new _bool)->setval(this->val<tmp->val);
        }else{
          return (new _err)->setval(this->type()+_operator+tmp->type()+" is underfined.");
        }
      }else{
        return (new _err)->setval(this->type()+_operator+tmp->type()+" is underfined.");
      }
    }
}
class _num: public __object{
  private:
    long double val;
  public:
    std::string type(){
      return "_num";
    }
    std::string tostr(){
      std::stringstream tmp;
      tmp<<this->val;
      return tmp.str();
    }
    _num * setval(long double val){
      this->val=val;
      return this;
    }
    __object * calc(std::string _operator){
      if(_operator=="-"){
        return (new _num)->setval(-(this->val));
      }else if(_opertor=="?"){
        return (new _bool)->setval(true);
      }else{
        return (new _err)->setval(_operator+this->type()+" is underfined.");
      }
    }
    __object * calc(std::string _operator,__object * another){
      _num * tmp=dynamic_cast<_num *>(another);
      if(tmp!=nullptr){
        if(_operator=="^"){
          return (new _num)->setval(pow(this->val,tmp->val));
        }else if(_operator=="*"){
          return (new _num)->setval(this->val*(tmp->val));
        }else if(_operator=="/"){
          return (new _num)->setval(this->val/(tmp->val));
        }else if(_operator=="+"){
          return (new _num)->setval(this->val+(tmp->val));
        }else if(_operator=="<"){
          return (new _bool)->setval(this->val<(tmp->val));
        }else{
          return (new _err)->setval(this->type()+_operator+tmp->type()+" is undefined.");
        }
      }else{
        return (new _err)->etval(this->type()+_operator+tmp->type()+" is unefined.");
      }
    }
}
class _func: public __object{
  private:
    std::vector<std::string> argument_var;
    std::vector<pair<expression,expression> > expr;
  public:
    std::string type(){
      return "_func";
    }
    std::string tostr(){
      std::stringstream tmp;
      size_t i;
      tmp<<"(";
      for(i=0;i<this->argument_var.size()-1;i=i+1){
        tmp<<(this->argument_var)[i]<<",";
      }
      tmp<<(this->argument_var)[i]<<")=>{";
      for(i=0;i<this->expr.size()-1;i=i+1){
        if((this->expr)[i].first().empty()==false){
          tmp<<(this->expr)[i].first().tostr()<<":"<<(this->expr)[i].second().tostr()<<",\n";
        }else{
          tmp<<(this->expr)[i].second().tostr()<<",\n";
        }
      }
      if((this->expr)[i].first().empty()==false){
        tmp<<(this->expr)[i].first().tostr()<<":"<<(this->expr)[i].second().tostr()<<"}";
      }else{
        tmp<<(this->expr)[i].second().tostr()<<"}";
      }
      return tmp.str();
    }
    _func * setval(std::vector<std::string> argument_var,std::vector<std::pair<expression,expression> > expr){
      this->argument_var=argument_var;
      this->expr=expr;
      return this;
    }
    object apply(std::vector<object> argument){
      std::unordered_map<std::string,object> map;
      std::stringstream tmp;
      object tmp1;
      if(this->argument_var.size()==argument.size()){
        for(size_t i=0;i<argument.size();i=i+1){
          map[(this->argument_var)[i]]=argument[i];
        }
        for(auto i:this->expr){
          if(i.first().empty()==false){
            tmp1=i.first().eval(map);
          }else{
            tmp1=tmp1.setval((new _bool)->setval(true));
          }
          if(tmp1.type()=="_bool"&&tmp1.tostr()=="_true"){
            return i.second().eval(map);
          }else{
            /*PASS*/
          }
        }
      }else{
        tmp<<this->tostr()<<" must receive and only receive "<<this->argument_var.size()<<" arguments.";
        return (new _err)->setval(tmp.str());
      }
    }
}
#endif
