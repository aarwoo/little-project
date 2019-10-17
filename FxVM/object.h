#include<vector>
#include<map>
#include<string>
class __object{
  public:
    virtual std::string type(){
      return "This object's type is undefined.";
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
    __object * calc(std::string _operator){
      if(_operator=="-"){
        this->val=-(this->val);
        return this;
      }else if(_opertor=="?"){
        return make__bool(true);
      }else{
        return make_err("Undefined operator for _num");
      }
    }
}
        
