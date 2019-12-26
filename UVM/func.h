#include<string>
#include<vector>
class func{
  private:
    std::string obj;
    std::vector<func> expr;
    func set_var(std::string & obj,func & f){
    }
  public:
    func apply(func f);
    func calc();
};
