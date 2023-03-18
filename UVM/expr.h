#include<string>
#include<vector>
#include<variant>
#include <utility>
class expr{
  private:
  std::variant<std::vector<expr>, //call list (F arg1 arg2 ...)
               std::pair<std::vector<std::string>,std::vector<expr> >, // func def (var1 var2 ...)->expr
               std::pair<std::string,std::vector<expr> >, // var and it's val
               std::string, //value below
               long double> ex;
};
