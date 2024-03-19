#include<iostream>

using namespace std;

void f(int* num){
  int x = 4;
  *num = x;
  return;
}

int main(){
  int y = 1;
  f(&y);
  std::cout<<y<<endl;
  return 0;
}
