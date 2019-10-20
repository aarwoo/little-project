#ifndef expression_h
#define expression_h
#include"object.h"
class __expression{
  public:
    virtual ~__expression(){
      /*PASS*/
    }
    virtual bool empty(){
      return true;
    }
    virtual std::string tostr(){
      return "";
    }
    virtual object eval(std::unordered_map<std::string,object> map){
      return *(new object);
    }
}
class expression{
  private:
    __expression * expr;
  public:
    expression(){
      this->expr=new __expression;
    }
    ~expression(){
      delete this->expr;
    }
    bool empty(){
      return this->expr->empty();
    }
    std::string tostr(){
      return this->expr->tostr();
    }
    object eval(std::unordered_map<std::string,object> map){
      return this->expr->eval(map);
    }
}
#endif
