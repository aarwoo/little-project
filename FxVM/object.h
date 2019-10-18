#include<vector>
#include<map>
#include<string>
class __object{
  public:
    virtual std::string type(){
      return "?";
    }
    virtual __object * calc(std::string _operator){
      return this;
    }
    virtual __object * calc(std::string _operator,__object * another){
      return this;
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
    object calc(std::string _operator){
      this->val=this->val->calc(_operator);
      return *this;
    }
    object calc(std::string _operator,object another){
      this->val=this->val->calc(_operator,another.val);
      return *this;
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
        this->val=-(this->val);
        return this;
      }else if(_opertor=="?"){
        return (new _bool).setval(true);
      }else{
        return (new _err).setval(_operator+this->type()+" is underfined.");
      }
    }
    __object * calc(std::string _operator,__object * another){
      _num * tmp=dynamic_cast<_num *>(another);
      if(tmp!=nullptr){
        if(_operator=="^"){
          return (new _num).setval(pow(this->val,tmp->val));
        }else if(_operator=="*"){
          return (new _num).setval(this->val*(tmp->val));
        }else if(_operator=="/"){
          return (new _num).setval(this->val/(tmp->val));
        }else if(_operator=="+"){
          return (new _num).setval(this->val+(tmp->val));
        }else if(_operator=="<"){
          return (new _num).setval(this->val<(tmp->val));
        }else{
          return (new _err).setval(this->type()+_operator+tmp->type()+" is undefined.");
        }
      }else{
        return (new _err).setval(this->type()+_operator+tmp->type()+" is unefined.");
      }
}
        
