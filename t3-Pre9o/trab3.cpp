#include <iostream>
#include <list>
#include <iomanip>

struct previdencia{
    char especie;
    double valor;
    double preco_cota;
    int ano;
    double cotas;
};

void aplicacao(std::list<previdencia*> &lista, previdencia *transacoes){
    lista.push_back(transacoes);
}

void retirada(std::list<previdencia*> &lista, previdencia transacoes){
    double imposto = 0;
    char espaco = 32;
    double dinheiro = 0;

    transacoes.cotas = transacoes.valor/transacoes.preco_cota;
    dinheiro = transacoes.valor;

    for(auto it = lista.begin(); it != lista.end();){
        double lucro;
        if((*it)->cotas >= transacoes.cotas){
           
            lucro = (transacoes.cotas * transacoes.preco_cota) - (transacoes.cotas * (*it)->preco_cota);
            (*it)->cotas -= transacoes.cotas;

            if(transacoes.ano - (*it)->ano < 2){
                imposto = imposto + lucro * 0.35;
            }
            else if(transacoes.ano - (*it)->ano >=2 && transacoes.ano - (*it)->ano < 4){
                imposto = imposto + lucro * 0.3;
            }
            else if(transacoes.ano - (*it)->ano >=4 && transacoes.ano - (*it)->ano < 6){
                imposto = imposto + lucro * 0.25;
            }
            else if(transacoes.ano - (*it)->ano >=6 && transacoes.ano - (*it)->ano < 8){
                imposto = imposto + lucro * 0.2;
            }
            else if(transacoes.ano - (*it)->ano >=8 && transacoes.ano - (*it)->ano < 10){
                imposto = imposto + lucro * 0.15;
            }
            else if(transacoes.ano-(*it)->ano >= 10){
                imposto = imposto + lucro * 0.1;
            }
            break;
        }
        else{
            lucro = ((*it)->cotas * transacoes.preco_cota) - ((*it)->cotas * (*it)->preco_cota);
            transacoes.cotas -= (*it)->cotas;

            if(transacoes.ano - (*it)->ano < 2){
                imposto = imposto + lucro * 0.35;
            }
            else if(transacoes.ano - (*it)->ano >=2 && transacoes.ano - (*it)->ano < 4){
                imposto = imposto + lucro * 0.3;
            }
            else if(transacoes.ano - (*it)->ano >=4 && transacoes.ano - (*it)->ano < 6){
                imposto = imposto + lucro * 0.25;
            }
            else if(transacoes.ano - (*it)->ano >=6 && transacoes.ano - (*it)->ano < 8){
                imposto = imposto + lucro * 0.2;
            }
            else if(transacoes.ano - (*it)->ano >=8 && transacoes.ano - (*it)->ano < 10){
                imposto = imposto + lucro * 0.15;
            }
            else if(transacoes.ano-(*it)->ano >= 10){
                imposto = imposto + lucro * 0.1;
            }
            
            delete *it;
            it = lista.erase(it);
        }
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << dinheiro << espaco << imposto << std::endl;
}

void retirar_tudo(std::list<previdencia*> &lista, previdencia transacoes){
    double imposto = 0;
    double valor_total = 0;
    char espaco = 32;

    for(auto it = lista.begin(); it != lista.end(); it++){
        double lucro = ((*it)->cotas * transacoes.preco_cota) - ((*it)->cotas * (*it)->preco_cota);
        valor_total += (*it)->cotas * transacoes.preco_cota;
        
        if(transacoes.ano - (*it)->ano < 2){
            imposto = imposto + lucro * 0.35;
        }
        else if(transacoes.ano - (*it)->ano >=2 && transacoes.ano - (*it)->ano < 4){
            imposto = imposto + lucro * 0.3;
        }
        else if(transacoes.ano - (*it)->ano >=4 && transacoes.ano - (*it)->ano < 6){
            imposto = imposto + lucro * 0.25;
        }
        else if(transacoes.ano - (*it)->ano >=6 && transacoes.ano - (*it)->ano < 8){
            imposto = imposto + lucro * 0.2;
        }
        else if(transacoes.ano - (*it)->ano >=8 && transacoes.ano - (*it)->ano < 10){
            imposto = imposto + lucro * 0.15;
        }
        else if(transacoes.ano-(*it)->ano >= 10){
            imposto = imposto + lucro * 0.1;
        }
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << valor_total << espaco << imposto << std::endl;  
}
    
int main(){
    previdencia transacoes;

    std::list<previdencia*> lista;

    while(std::cin >> transacoes.especie >> transacoes.valor >> transacoes.preco_cota >> transacoes.ano){ 
        if(transacoes.especie == 'A' || transacoes.especie == 'a'){
            previdencia* op = new previdencia;
            op->especie = transacoes.especie;
            op->valor = transacoes.valor;
            op->preco_cota = transacoes.preco_cota;
            op->ano = transacoes.ano;
            op->cotas = transacoes.valor/transacoes.preco_cota;
            aplicacao(lista, op);
        }
        else if(transacoes.especie == 'R' || transacoes.especie == 'r'){
            if(transacoes.valor < 0){
                transacoes.cotas = 0;
                retirar_tudo(lista, transacoes);
            }
            else{
                retirada(lista, transacoes);
            }
        }
    }
    while(lista.empty() == false){
        delete lista.front();
        lista.pop_front();
    }
    return 0;
}