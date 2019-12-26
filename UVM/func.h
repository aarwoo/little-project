#include<string>
#include<vector>
#include"object.h"
class func{
  private:
    std::string var;
    object atom;
    std::vector<func>expr;
    func set_var(std::string _var,func vexpr){
      if(_var==var){
        if(expr.size()==0){
          expr.push_back(vexpr);
          var="";
        }else{
          /*Pass*/
        }
      }else{
        for(auto& i:expr){
          i=i.setvar(_var,vexpr);
        }
      }
      return *this;
    }
  public:
    func apply(func vexpr){
      if(var!=""){
        for(auto& i:expr){
          i=i.setvar(var,vexpr);
        }
      }else{
        atom=atom.apply(vexpr);
      }
    return *this;
    }
    func calc(){
      func ans;
      expr[0]=expr[0].calc();
      ans=expr[0];
      for(size_t i=1;i<expr.size();i=i+1){
        ans=ans.apply(expr[i]).calc();
      }
      return ans;
};
