// arvore.cpp
// Estrutura de uma Árvore Binária de Busca (ABB) com balanceamento AVL.
//
// The MIT License (MIT)
//
// Copyright (c) 2022 João Vicente Ferreira Lima, UFSM
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define CATCH_CONFIG_MAIN // O Catch fornece uma main()
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
struct Abb{
    T dado;
    Abb<T>* esq;
    Abb<T>* dir;
    int altura;
};

template<typename T>
bool abb_vazio(Abb<T>* no){
    return (no == nullptr);
}

template<typename T>
int abb_altura(Abb<T>* no){
    if(abb_vazio(no))
        return 0;

    return no->altura;
}

template<typename T>
int abb_get_fb(Abb<T>* no){
    if(abb_vazio(no))
        return 0;
    return (abb_altura(no->esq) - abb_altura(no->dir));
}

template<typename T>
Abb<T>* abb_esq_rotate(Abb<T>* x){
    Abb<T>* y = x->dir;
    Abb<T>* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = std::max(abb_altura(x->esq), abb_altura(x->dir)) + 1;
    y->altura = std::max(abb_altura(y->esq), abb_altura(y->dir)) + 1;

    return y;
}

template<typename T>
Abb<T>* abb_dir_rotate(Abb<T>* x){
    Abb<T>* y = x->esq;
    Abb<T>* T2 = y->dir;

    y->dir = x;
    x->esq = T2;

    x->altura = std::max(abb_altura(x->esq), abb_altura(x->dir)) + 1;
    y->altura = std::max(abb_altura(y->esq), abb_altura(y->dir)) + 1;

    return y;
}

template<typename T>
Abb<T>* abb_inicia(T v){
    Abb<T>* no = new Abb<T>;
    no->dado = v;
    no->altura = 1;
    no->esq = nullptr;
    no->dir = nullptr;

    return no;
}

template<typename T>
Abb<T>* abb_inicia(std::list<T>& entrada){
    Abb<T>* no = nullptr;
    if(entrada.empty() == true)
      return nullptr;

    for(auto it = entrada.begin(); it != entrada.end(); it++){
      no = abb_insere(no, *it);
    }

    return no;
}  

template<typename T>
Abb<T>* abb_insere(Abb<T>* no, T v){
    if (abb_vazio(no))
        return abb_inicia(v);

    if (v < no->dado)
        no->esq = abb_insere(no->esq, v);
    else if (v > no->dado)
        no->dir = abb_insere(no->dir, v);
    else
        return no;

    no->altura = 1 + std::max(abb_altura(no->esq), abb_altura(no->dir));
    
    int fb = abb_get_fb(no);

    if (fb > 1 && v < no->esq->dado)
        return abb_dir_rotate(no);

    if (fb < -1 && v > no->dir->dado)
        return abb_esq_rotate(no);

    if (fb > 1 && v > no->esq->dado){
        no->esq =  abb_esq_rotate(no->esq);
        return abb_dir_rotate(no);
    }   

    if (fb < -1 && v < no->dir->dado){
        no->dir = abb_dir_rotate(no->dir);
        return abb_esq_rotate(no);
    }

    return no;
}

template<typename T>
Abb<T>* abb_no_minimo(Abb<T>* no){
    Abb<T>* curr = no;

    while(curr->esq != nullptr)
        curr = curr->esq;

    return curr;
}

template<typename T>
Abb<T>* abb_remove(Abb<T>* no, T v){
    if(abb_vazio(no))
        return no;

    if(v < no->dado)
        no->esq = abb_remove(no->esq, v);
    else if (v > no->dado)
        no->dir = abb_remove(no->dir, v);
    else
    {
        if((no->esq == nullptr) || (no->dir == nullptr)){
            Abb<T>* temp = no->esq ? no->esq : no->dir;
            if (temp == nullptr){
                temp = no;
                no = nullptr;
            }
            else
             *no = *temp;
            delete temp;
        }
        else
        {
            Abb<T>* temp = abb_no_minimo(no->dir);

            while (temp->esq != nullptr)
                temp = temp->esq;

            no->dado = temp->dado;
            no->dir = abb_remove(no->dir, temp->dado);
        }
    }

    if(no == nullptr)
      return no;

    no->altura = 1 + std::max(abb_altura(no->esq), abb_altura(no->dir));

    int fb = abb_get_fb(no);

    if(fb > 1 && abb_get_fb(no->esq) >= 0)
        return abb_dir_rotate(no);

    if(fb > 1 && abb_get_fb(no->esq) < 0){
        no->esq =  abb_esq_rotate(no->esq);
        return abb_dir_rotate(no);
    }

    if(fb < -1 && abb_get_fb(no->dir) <= 0)
        return abb_esq_rotate(no);

    if(fb < -1 && abb_get_fb(no->dir) > 0){
        no->dir = abb_dir_rotate(no->dir);
        return abb_esq_rotate(no);
    }   

    return no;
}

template<typename T>
void abb_preOrdem(Abb<T>* a, std::list<T>& saida){
    if(!abb_vazio(a)){
        saida.push_back(a->dado);
        abb_preOrdem(a->esq, saida);
        abb_preOrdem(a->dir, saida);
    }
}   

template<typename T>
void abb_destroi(Abb<T>* a){
    if(!abb_vazio(a)){
        abb_destroi(a->esq);
        abb_destroi(a->dir);
        delete a;
    }
}


/*--------------------------------------*/
/********** INICIO DOS TESTES ***********/
/*--------------------------------------*/

TEST_CASE("Teste vazio") {
    Abb<int>* a;
    std::list<int> entrada {};
    a= abb_inicia(entrada);
    REQUIRE(abb_vazio(a) == true);
    abb_destroi(a);
}

TEST_CASE("Teste nao vazio") {
    Abb<int>* a;
    std::list<int> entrada {1};
    a= abb_inicia(entrada);
    REQUIRE(abb_vazio(a) == false);
    abb_destroi(a);
}


TEST_CASE("Caso 0") {
    Abb<int>* a;
    std::list<int> entrada {5, 3, 7};
    std::list<int> saida;
    std::list<int> resultado {5, 3, 7};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso ER") {
    Abb<int>* a;
    std::list<int> entrada {1, 2, 3};
    std::list<int> saida;
    std::list<int> resultado {2, 1, 3};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso DR") {
    Abb<int>* a;
    std::list<int> entrada {3, 2, 1};
    std::list<int> saida;
    std::list<int> resultado {2, 1, 3};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso DR-ER") {
    Abb<int>* a;
    std::list<int> entrada {5, 10, 7};
    std::list<int> saida;
    std::list<int> resultado {7, 5, 10};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso ER-DR") {
    Abb<int>* a;
    std::list<int> entrada {5, 1, 3};
    std::list<int> saida;
    std::list<int> resultado {3, 1, 5};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso DEL 0") {
    Abb<int>* a;
    std::list<int> entrada {5};
    a = abb_inicia(entrada);
    a = abb_remove( a, 5 );
    REQUIRE(abb_vazio(a) == true);
    abb_destroi(a);
}

TEST_CASE("Caso DEL 1") {
    Abb<int>* a;
    std::list<int> entrada {4, 2, 6, 7};
    std::list<int> saida;
    std::list<int> resultado {6, 4, 7};
    a = abb_inicia(entrada);
    a = abb_remove( a, 2 );
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso simples sequencial") {
    Abb<int>* a;
    std::list<int> entrada {1, 2, 3, 4, 5, 6, 7};
    std::list<int> saida;
    std::list<int> resultado {4, 2, 1, 3, 6, 5, 7};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso Notas MIT 2008") {
    Abb<int>* a;
    std::list<int> entrada {41, 20, 65, 11, 29, 50, 26, 23, 55};
    std::list<int> saida;
    std::list<int> resultado {41, 20, 11, 26, 23, 29, 55, 50, 65};
    a = abb_inicia(entrada);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso N") {
    Abb<int>* a;
    std::list<int> entrada {50, 30, 24, 5, 28, 45, 98, 52, 60};
    std::list<int> saida;
    std::list<int> resultado {30, 26, 24, 28, 52, 50, 60};
    a = abb_inicia(entrada);
    a = abb_remove( a, 98 );
    a = abb_remove( a, 45 );
    a = abb_remove( a, 5 );
    a = abb_insere( a, 26 );
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}

TEST_CASE("Caso remove todos") {
    Abb<int>* a;
    std::list<int> entrada {41, 20, 65, 11, 29, 50, 26};
    std::list<int> saida;
    std::list<int> resultado {};
    a = abb_inicia(entrada);
    a = abb_remove(a, 41);
    a = abb_remove(a, 29);
    a = abb_remove(a, 50);
    a = abb_remove(a, 20);
    a = abb_remove(a, 26);
    a = abb_remove(a, 65);
    a = abb_remove(a, 11);
    abb_preOrdem(a, saida);
    REQUIRE(saida == resultado);
    abb_destroi(a);
}