#ifndef PIPE__H
#define PIPE__H
#include <map>
template<typename T>
class Pipe{
  using pfunc = T (*)(T);
  
  int fc = 0;
  int fcc=0;
  public:
  std::map<int, pfunc> funcMap; 
  Pipe(){}
  Pipe(pfunc func){
      funcMap[fc] = func;
      fc++;
  }
  void add_operation(pfunc func){
    funcMap[fc] = func;
    fc++;
  }
  T run(T value){
    if(funcMap.empty()){
        return value;
    } else {
        //std::cout<<funcMap.size()<<std::endl;
        for(unsigned int i = 0; i<funcMap.size(); i++){
            //std::cout<<"value: "<<value<<std::endl;
            //std::cout<<"i: "<<i<<std::endl;
            value = funcMap[i](value);
        }
    }
    return value;

    
  }

  void clear(){
      funcMap.clear();
      fc=0;
  }

  Pipe<T>& operator+=(Pipe<T> const& p){
      std::map<int , pfunc> m = p.getFuncMap();
      for(unsigned int i = 0; i<m.size(); i++ ){
          
          this->funcMap[fc] = m[i];
          this->fc++;
      }
      return *this;
  }

  T operator() (T v){
      return run(v);
  }
  Pipe<T>& operator|(Pipe<T> const& p){
    std::map<int , pfunc> m = p.getFuncMap();
      for(unsigned int i = 0; i<m.size(); i++ ){
          
          this->funcMap[fc] = m[i];
          this->fc++;
      }
      return *this;
  /*    Pipe<T> v;
      
      std::map<int , pfunc> m = p.getFuncMap();
      fcc = fc;
      for(unsigned int i = 0; i<funcMap.size(); i++ ){
          v.funcMap[i] = funcMap[i];
          v.fc++;
      }
      for (int i = 0; i < m.size(); i++)
      {
          v.funcMap[v.fc] = m[i];
          v.fc++; 
      }
      
      return *v;  */   
  } 

  std::map<int, pfunc> getFuncMap() const {
      return funcMap;
  }
  void xd(){
      for(auto item:funcMap){
          std::cout<<item.first<<std::endl;
      }
  }
};
#endif