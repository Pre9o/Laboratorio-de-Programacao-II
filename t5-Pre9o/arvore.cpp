#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <functional>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>


template<typename T>
struct Arvore {
    T valor = 0;
    Arvore<T>* esq = nullptr;
    Arvore<T>* dir = nullptr;

    void inserir(T valor){
        if(valor < this->valor){
            if(esq == nullptr){
                esq = new Arvore<T>();
                esq->valor = valor;
            }else{
                esq->inserir(valor);
            }
        }else{
            if(dir == nullptr){
                dir = new Arvore<T>();
                dir->valor = valor;
            }else{
                dir->inserir(valor);
            }
        }
    }

    void inicia(std::list<T>& entrada){
        if(entrada.empty())
            return;

        valor = entrada.front();
        entrada.pop_front();

        for(auto& i : entrada){
            inserir(i);
        }
    }


    bool vazio(){
        return this->valor == 0 && this->esq == nullptr && this->dir == nullptr;
    }


    bool posOrdem(std::list<T>& saida){
        if(vazio()){
            return false;
        }

        if(esq != nullptr){
            esq->posOrdem(saida);
        }

        if(dir != nullptr){
            dir->posOrdem(saida);
        }

        saida.push_back(valor);

        return true;
    }

    void destroi(void){
        if(esq != nullptr){
            esq->destroi();
            delete esq;
        }

        if(dir != nullptr){
            dir->destroi();
            delete dir;
        }
    }
};


TEST_CASE("Teste vazio") {
    Arvore<int> a;
    std::list<int> entrada {};
    a.inicia(entrada);
    REQUIRE(a.vazio() == true);
    a.destroi();
}

TEST_CASE("Teste nao vazio") {
    Arvore<int> a;
    std::list<int> entrada {1};
    a.inicia(entrada);
    REQUIRE(a.vazio() == false);
    a.destroi();
}

TEST_CASE("Caso 1") {
    Arvore<int> a;
    std::list<int> entrada {5, 3, 7};
    std::list<int> saida;
    std::list<int> resultado {3, 7, 5};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}

TEST_CASE("Caso 3") {
    Arvore<char> a;
    std::list<char> entrada {'F', 'C', 'A', 'D', 'J', 'H', 'I', 'K'};
    std::list<char> saida;
    std::list<char> resultado {'A', 'D', 'C', 'I', 'H', 'K', 'J', 'F'};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}

TEST_CASE("Caso N") {
    Arvore<int> a;
    std::list<int> entrada {50, 30, 24, 5, 28, 45, 98, 52, 60};
    std::list<int> saida;
    std::list<int> resultado {5, 28, 24, 45, 30, 60, 52, 98, 50};
    a.inicia(entrada);
    a.posOrdem(saida);
    REQUIRE(saida == resultado);
    a.destroi();
}
