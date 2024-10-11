#include <iostream>
#include <string>

void tamanho(int *N){
    do{
        std::cin >> *N;
    }while(*N<1 || *N>50);
}

void ler(char **matriz, int N){
    for(auto i=0; i<N; i++){
        for(auto j=0; j<N; j++){
            std::cin >> matriz[i][j];
        }
    }
}

void zerar(char **matriz, int N){
    for(auto i=0; i<N; i++){
        for(auto j=0; j<N; j++){
            if(matriz[i][j]!='*'){
                matriz[i][j]=48;
            }
        }
    }
}

void verificar(char **matriz, int N){
    for(auto i=0; i<N; i++){
        for(auto j=0; j<N; j++){
            if(matriz[i][j]!='*'){
                if(i>0 && j>0){
                    if(matriz[i-1][j-1]=='*'){
                        matriz[i][j]++;
                    }
                }
                if(i>0){
                    if(matriz[i-1][j]=='*'){
                        matriz[i][j]++;
                    }
                }
                if(i>0 && j<N-1){
                    if(matriz[i-1][j+1]=='*'){
                        matriz[i][j]++;
                    }
                }
                if(j>0){
                    if(matriz[i][j-1]=='*'){
                        matriz[i][j]++;
                    }
                }
                if(j<N-1){
                    if(matriz[i][j+1]=='*'){
                        matriz[i][j]++;
                    }
                }
                if(i<N-1 && j>0){
                    if(matriz[i+1][j-1]=='*'){
                        matriz[i][j]++;
                    }
                }
                if(i<N-1){
                    if(matriz[i+1][j]=='*'){
                        matriz[i][j]++;
                    }
                }
                if(i<N-1 && j<N-1){
                    if(matriz[i+1][j+1]=='*'){
                        matriz[i][j]++;
                    }
                }
           }
        }
    }
}

void mostrar(char **matriz, int N){
     for(auto i=0; i<N; i++){
        for(auto j=0; j<N; j++){
            std::cout << matriz[i][j];
        }
        std::cout << std::endl;
    }
}

void liberar(char **matriz, int N){
    for(auto i=0; i<N; i++){
        delete[] matriz[i];
    }
    delete[] matriz;
}

int main(){
    char **matriz{nullptr};
    int N;

    tamanho(&N);
    
    matriz=new char*[N];

    for(auto i=0; i<N; i++){
        matriz[i]=new char[N];
    }   

    ler(matriz, N);
    zerar(matriz, N);
    verificar(matriz, N);
    mostrar(matriz, N);
    liberar(matriz, N);
    
    return 0;
}