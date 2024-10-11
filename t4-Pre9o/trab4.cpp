#include <iostream>
#include <string>
#include <map>
#include <sstream>

#include "calculadora.hpp"

struct Celula{
    std::string id;
    int valor = 0;
    bool calculado = false;
    std::string formula;
};

struct Planilha{
    std::map<std::string, Celula> celulas;

    int calculaValor(const std::string& id, std::string formula){
        Calculadora <int> calc;
        std::map<std::string, int> copia;
        
        if(celulas[id].calculado){
            return celulas[id].valor;
        }

        if(formula[0] != '=') {
            return 1;
        }

        formula = formula.substr(1);

        for(std::size_t i = 0; i < formula.size(); i++){
            std::string letra;
            if((formula[i] == ' ' || formula[i] >= '0') && (formula[i] <= '9')){
                continue;
            }

            if(formula[i] >= 'A' && formula[i] <= 'Z'){
                letra = formula[i];
            }

            // pegar numero
            std::string numero;
            i++;
            while(formula[i] >= '0' && formula[i] <= '9'){
                numero += formula[i];
                i++;
            }
            i--;

            std::string coordenada = letra + numero;
            int resultado = calculaValor(coordenada, celulas[coordenada].formula);
            copia[coordenada] = resultado;
        }

        // for pra substituir o cache
        for(std::size_t i = 0; i < formula.size(); i++){
            std::string letra;
            if(formula[i] == ' '){
                continue;
            }



            if(formula[i] >= 'A' && formula[i] <= 'Z'){
                letra = formula[i];
            }
            else{
                continue;
            }


            // pegar numero
            std::string numero;
            i++;

            while(formula[i] >= '0' && formula[i] <= '9'){
                numero += formula[i];
                i++;
            }
            i--;

            std::string coordenada = letra + numero;
            std::string valor = std::to_string(copia[coordenada]);
            formula.replace(i - coordenada.size() + 1, coordenada.size(), valor);
        }

        // chamaaa calculadora

        calc.formula(formula);
        if(!calc.fim()) {
            return 1;
        }
        return calc.resultado();
    }
};

int main(){
    Planilha p;
    std::string id;
    std::string formula;

    while(std::cin >> id >> formula){
        p.celulas[id] = Celula();
        p.celulas[id].id = id;
        p.celulas[id].formula = formula;
        if(formula[0] == '='){
            p.celulas[id].calculado = false;
        }
        else{
            p.celulas[id].calculado = true;
            p.celulas[id].valor = std::stoi(formula);
        }
    }

    for(auto& par : p.celulas){
        if(par.second.calculado){
            std::cout << par.second.id << " " << par.second.valor << std::endl;
        }
        else{
            std::cout << par.second.id << " " << p.calculaValor(par.second.id, par.second.formula) << std::endl;
        }
    }

    return 0;
}