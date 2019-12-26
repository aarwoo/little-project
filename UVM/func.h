#include<unordered_map>
class func{
  private:
    std::unordered_map<string,func>var;
    std::vector<func>expr;
  public:
    func as_var(string _var,func _expr);
};
