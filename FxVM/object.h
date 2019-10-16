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
    std::string type(){
      return this->val->type();
    }
    object calc(std::string _operator){
      this->val=this->val->calc(_operator);
    }
    object calc(std::string _operator,object another){
      if(this->type()==another.type()){
        return this->val->calc(_operator,another.val);
      }else{
        return make_err("Undefined!!!");
      }
    }
}
