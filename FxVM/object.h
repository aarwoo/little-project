#include<vector>
#include<map>
#include<string>
class _err;
class _bool;
class __object{
  public:
    virtual std::string type(){
      return "?";
    }
    virtual __object * calc(std::string _operator){
      return (new _err)->setval(_operator+this->type()+" is undefined.");
    }
    virtual __object * calc(std::string _operator,__object * another){
      return (new _err)->setval(this->type()+_operator+another->type()+" is undefined.");
    }
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
    object setval(__object * val){
      delete this->val;
      this->val=val;
    }
    object calc(std::string _operator){
      this->val=this->val->calc(_operator);
      return *this;
    }
    object calc(std::string _operator,object another){
      this->val=this->val->calc(_operator,another.val);
      return *this;
    }
}
class _err:__object{
  private:
    std::string val;
  public:
    std::string type(){
      return "_err";
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
class _bool:__object{
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
        return (new _bool)->setval(!(this->val));
      }else if(_operator=="?"){
        return (new _bool)->setval(true);
      }else{
        return (new _err)->setval(_operator+this->type()+" is undefined.");
      }
    }
    __object * calc(std::string _operator,__object * another){
      _bool * tmp=dynamic_cast<_bool *>(another);
      if(tmp!=nullptr){
        if(_operator=="="){
          return (new _bool)->setval(this->val==tmp->val);
        }else if(_operator=="/\"){
          return (new _bool)->setval(this->val&&tmp->val);
        }else if(_operator=="\/"){
          return (new _bool)->setval(this->val||tmp->val);
        }else{
          return (new _err)->setval(this->type()+_operator+tmp->type()+" is underfined.");
        }
      }else{
        return (new _err)->setval(this->type()+_operator+tmp->type()+" is undefined.");
      }
    }
}
class _num:__object{
  private:
    long double val;
  public:
    std::string type(){
      return "_num";
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
        
