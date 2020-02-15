//This code is for C++20
#include<string>
#include<vector>
#include<unordered_map>
#include<memory>
class func{
  private:
    std::string obj;
    std::shared_ptr<func> above;
    std::shared_ptr<std::unordered_map<std::string,func> > space;
    std::vector<func> expr;
  public:
    func func(){
      space=std::make_shared_default_init<std::unordered_map<std::string,func> >();
    }
    func& look_up_space(std::string key){
      if(space->contains(key)==true){
        return space[func];
      }else if(above.get()!=nullptr){
        return above->look_up_space(key);
      }else{
        return space[func];
      }
    }
    func calc(){
      if(expr.size()==0){
         if(obj[0]=="$"){
           return Kernel(obj.substr(1));
         }else if(obj[0]=="#"){
           func tmp;
           tmp.obj=obj.substr(1);
           tmp.above=above;
           tmp.space=space;
           return tmp;
         }else if(obj[0]=="\""||obj[0]=="+"){
           return *this;
         }else{
           return look_up_space(obj);
         }
      }else{
        if(obj[0]=="$"){
          return *this;
        }else if(obj[0]=="#"){
          func tmp;
          tmp=*this;
          tmp.obj="";
          return tmp;
        }else if(obj==""){
          func tmp;
          tmp=expr[0].calc();
          for(size_t i=1;i<expr.size();i=i+1){
            tmp=tmp.apply(expr[i].calc()).calc();
          }
          return tmp;
        }else{
          return *this;
        }
      }
    }
};
