#ifndef expression_h
#define expression_h
#include"object.h"
class expression{
  private:
    std::string _operator;
    std::string id;
    object val;
    expression * l_subexpr;
    expression * r_subexpr;
  public:
    expression(){
      this->l_subexpr=nullptr;
      this->r_subexpr=nullptr;
    }
    ~expression(){
      delete this->l_subexpr;
      delete this->r_subexpr;
    }
    bool empty(){
      return this->_operator==""&&this->id==""&&this->val.type()=="?"&&this->l_subexpr==nullptr&&this->r_subexpr==nullptr&&
    }
    std::string tostr(){
      
    }
    object eval(std::unordered_map<std::string,object> map){
      
    }
}
#endif
