#ifndef generator_h
#define generator_h
class __generator{
  public:
    virtual std::string tostr(){
      return "";
    }
    virtual object eval(std::unordered_map<std::string,object> map){
      return *(new object);
    }  
}
class generator{
  private:
    __generator * gen;
  public:
    generator(){
      this->gen=(new __generator);
    }
    ~generator(){
      delete this->gen;
    }
    std::string tostr(){
      return this->gen->tostr();
    }
#endif
