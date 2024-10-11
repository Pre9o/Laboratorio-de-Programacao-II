#include <iostream>
#include <fstream>

int main(){
    int a, b, c;

    while(std::cin.eof()==false){
        std::cin >> a >> b >> c;

        if(std::cin.eof()==true){
            break;
        }

        if(a+b<c || a+c<b || b+c<a){
            std::cout << "invalido" << std::endl;
        }
        else if(a==b && b==c){
            std::cout << "equilatero" << std::endl;
        }
        else if(a==b || b==c || a==c){
            std::cout << "isosceles" << std::endl;
        }
        else{
            std::cout << "escaleno" << std::endl;
        }
   }

    return 0;
}