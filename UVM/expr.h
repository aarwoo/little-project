#include<string>
#include<vector>
#include<variant>
#include<utility>
#include<optional>
class expr{
  private:
  	typedef std::vector<expr> exprs; //call list (F arg1 arg2 ...)
  	typedef std::pair<std::vector<std::string>,exprs> func; // func def (var1 var2 ...)->expr
  	typedef std::pair<std::string,exprs> var; // var and it's val
  	typedef std::string str; //string value
	typedef long double num; //num value
	typedef std::vector<std::string> errs; //error msg list
	//bool value there is not typedef,just using C++ typename bool
	using 
  	std::variant<exprs, 
               	 func, 
                 var,
                 str,
                 num,
				 errs,
				 bool> ex;
    template<typename T>
    std::optional<T> read(){
    	T* p=std::get_if<T>(&ex);
    	if(p!=nullptr)
    		return p;
    	else
    		return std::nullopt;
	}
	template<typename T>
	void write(T val){
		ex=val;
		return;
	}
	template<typename T>
	expr bin_op(T (*bin_op)(T x,T y),expr y,std::string err_msg){ //binary operator
		T* x=std::get_if<T>(&ex);
		T* y=std::get_if<T>(&(y.ex));
		errs* e=std::get_if<errs>(&ex);
		if(x!=nullptr&&y!=nullptr){
			ex=bin_op(*x,*y);
		}else if(e!=nullptr){
			e->push_back(err_msg);
		}else{
			errs tmp;
			tmp.push_back(err_msg);
			ex=tmp;
		}
		return *this;
	}
	template<typename T>
	expr bin_op(bool (*bin_op)(T x,T y),expr y,std::string err_msg){ //binary operator,for compare
		T* x=std::get_if<T>(&ex);
		T* y=std::get_if<T>(&(y.ex));
		errs* e=std::get_if<errs>(&ex);
		if(x!=nullptr&&y!=nullptr){
			ex=bin_op(*x,*y);
		}else if(e!=nullptr){
			e->push_back(err_msg);
		}else{
			errs tmp;
			tmp.push_back(err_msg);
			ex=tmp;
		}
		return *this;
	}
  public:
  	
};
