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
class var_expr: public __expression{
  private:
    std::string var;
  public:
    var_expr * setval(std::string var){
      this->var=var;
      return this;
    }
    bool empty(){
      return this->var!="";
    }
    std::string tostr(){
      return this->var;
    }
    object eval(std::unordered_map<std::string,object> map){
      if(map.count(this->var)==1){
        return map[this->var];
      }else{
        return global_var(this->var);
      }
    }
}
class func_call_expr: public __expression{
  private:
    expression f;
    std::vector<expression>arg;
  public:
    bool empty(){
      return this->f.empty()&&this->arg.size()>0;
    }
    std::string tostr(){
      std::string tmp;
      size_t i;
      tmp=this->f.tostr()+"(";
      for(i=0;i<this->arg.size()-1;i=i+1){
        tmp=tmp+(this->arg)[i].tostr()+",";
      }
      tmp=tmp+(this->arg)[i].tostr()+")";
      return tmp;
    }
}
#endif
