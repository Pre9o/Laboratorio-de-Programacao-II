#include <stack>
#include <string>
#include <iostream>
#include <cmath>

template<typename T>
struct Calculadora {
    bool erro = false;

    std::stack<T> operandos;    
    std::stack<char> operadores; 

    void cria(void){
    }

    int precedencia(char teste){
        if(teste == '+' || teste == '-'){
            return 1;
        }
        else if(teste == '*' || teste == '/'){
            return 2;
        }
        else{
            return 0;
        }
    }

    void destroi(void){
        while(operandos.empty() == false)
            operandos.pop();
        while(!operadores.empty())
            operadores.pop();
    }

    void operando(T op) {
        operandos.push(op);
    }

    void operador(char op){
        if(op == '(') {
            operadores.push(op);
        }
        else if(op == ')'){
            while(operadores.empty() == false && operadores.top() != '('){
                char operante = operadores.top();
                operadores.pop();
                auto operando_um = operandos.top();
                operandos.pop();

                if(operandos.empty() == false) {
                    auto operando_dois = operandos.top();
                    operandos.pop();

                    if (operante == '+') {
                        operandos.push(operando_um + operando_dois);
                    } else if (operante == '-') {
                        operandos.push(operando_dois - operando_um);
                    } else if (operante == '*') {
                        operandos.push(operando_um * operando_dois);
                    } else if (operante == '/') {
                        operandos.push(std::round((float)operando_dois/operando_um));
                    }
                }
            }
            if(operadores.empty() == false && operadores.top() == '('){
                operadores.pop();
            }
            else{
                erro = true;
            }
        }
        else if (op == '+' || op == '-' || op == '*' || op == '/'){
            while(operadores.empty() == false && precedencia(op) <= precedencia(operadores.top())){
                char operante = operadores.top();
                operadores.pop();
                auto operando_um = operandos.top();
                operandos.pop();

                if(operandos.empty() == false) {
                    auto operando_dois = operandos.top();
                    operandos.pop();

                    if (operante == '+') {
                        operandos.push(operando_um + operando_dois);
                    } else if (operante == '-') {
                        operandos.push(operando_dois - operando_um);
                    } else if (operante == '*') {
                        operandos.push(operando_um * operando_dois);
                    } else if (operante == '/') {
                        operandos.push(std::round((float)operando_dois/operando_um));
                    }
                }
            }
            operadores.push(op);
        }
    }

    void formula(std::string form){
        for(std::size_t i = 0; i < form.size(); i++){
            if(form[i] == ' ')
                continue;
            else if(form[i] == '(' || form[i] == ')' || form[i] == '+' || form[i] == '-' || form[i] == '*' || form[i] == '/'){
                if((i==0 && form[i] == '-') || (i>0 && form[i] == '-' && form[i-1] == '(')){
                    operando(0);
                }
                operador(form[i]);
            }
            else{
                std::string numero;
                while(form[i] != ' ' && form[i] != '(' && form[i] != ')' && form[i] != '+' && form[i] != '-' && form[i] != '*' && form[i] != '/'){
                    numero += form[i];
                    i++;
                }
                i--;
                operando(std::stoi(numero));
            }
        }

    }

    bool fim(void) {
        if(!operadores.empty() || operandos.size() != 1){
            while(!operadores.empty()){
                char operante = operadores.top();
                operadores.pop();
                if (operandos.empty() == false) {
                    auto operando_um = operandos.top();
                    operandos.pop();

                    if (operandos.empty() == false) {
                        auto operando_dois = operandos.top();
                        operandos.pop();

                        if (operante == '+') {
                            operandos.push(operando_um + operando_dois);
                        } else if (operante == '-') {
                            operandos.push(operando_dois - operando_um);
                        } else if (operante == '*') {
                            operandos.push(operando_um * operando_dois);
                        } else if (operante == '/') {
                            operandos.push(std::round((float)operando_dois / operando_um));
                        }
                    }
                }
            }
        }
        if(operandos.size() == 1 && operadores.empty() && erro == false){
            return true;
        }
        else{
            return false;
        }
    }

    T resultado(void) {
        if(operandos.empty()) {
            return static_cast<T>(0);
        }

        return operandos.top();
    }
};