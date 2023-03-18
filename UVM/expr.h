#include<string>
#include<vector>
class expr;
class __expr{
  public:
    virtual __expr();
    virtual ~__expr();
    virtual std::string type();
    virtual std::string tostr();
    virtual __expr* toexpr(std::string token);
    virtual expr apply(expr arg,std::map<std::string,expr > env);
};
class expr{
  private:
    __expr * e;
  public:
    expr(){e=new __expr;}
    ~expr(){delete e;}
    std::string type(){
      return e->type();
    }
    expr toexpr(std::string token){
      
    }
    expr apply(expr arg,std::map<std::string,expr > env);
};
