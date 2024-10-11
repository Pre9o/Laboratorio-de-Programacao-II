
# TDD- Árvore Binária de Busca AVL

Este é o código exemplo do trabalho usando TDD (*Test Driven Development*) com o framework C++ [Catch2](https://github.com/catchorg/Catch2/tree/v2.x).

O framework Catch2 consegue ser utilizado apenas com o arquivo header [catch.hpp](catch.hpp) sem necessidade de instalação.

**NÃO MODIFIQUE OS TESTES** 

Todos os testes estão prontos no arquivo [arvore.cpp](arvore.cpp). A compilação e teste pode ser feita com os comandos:
```
$ g++ -Wall -std=c++11 arvore.cpp 
```

A saída resumida do teste (código exemplo):
```
$ ./a.out --reporter compact --success
arvore.cpp:174: passed: abb_vazio(a) == true for: true == true
arvore.cpp:182: passed: abb_vazio(a) == false for: false == false
arvore.cpp:194: failed: saida == resultado for: { 5 } == { 5, 3, 7 }
arvore.cpp:205: failed: saida == resultado for: { 1 } == { 2, 1, 3 }
arvore.cpp:216: failed: saida == resultado for: { 3 } == { 2, 1, 3 }
arvore.cpp:227: failed: saida == resultado for: { 5 } == { 7, 5, 10 }
arvore.cpp:238: failed: saida == resultado for: { 5 } == { 3, 1, 5 }
arvore.cpp:247: failed: abb_vazio(a) == true for: false == true
arvore.cpp:259: failed: saida == resultado for: { 4 } == { 6, 4, 7 }
arvore.cpp:270: failed: saida == resultado for: { 1 } == { 4, 2, 1, 3, 6, 5, 7 }
arvore.cpp:281: failed: saida == resultado for: { 41 }
==
{ 41, 20, 11, 26, 23, 29, 55, 50, 65 }
arvore.cpp:296: failed: saida == resultado for: { 50 } == { 30, 26, 24, 28, 52, 50, 60 }
arvore.cpp:314: failed: saida == resultado for: { 41 } == {  }
Failed 11 test cases, failed 11 assertions.
```

