#include "tree.h"
#include <stack>
#include <sstream>

using namespace std;

Node::Node(string valor){
    this -> valor = valor;
    left = nullptr;
    right = nullptr;
}

bool operador(string &operador){
    return operador == "+" || operador == "-" || operador == "*" || operador == "/";
}

Node *arvore(string &expressão){
    stack<Node*> stk;
    stringstream str(expressão);
    string valor;

    while(str >> valor){
        if(!operador(valor)){
            stk.push(new Node(valor));
        } else{
            if(stk.size() < 2){
                throw runtime_error("expressão inválida!");
            } 

            Node *right = stk.top(); 
            stk.pop();

            Node *left = stk.top();
            stk.pop();

            Node *opNode = new Node(valor);
            opNode -> left = left;
            opNode -> right = right;
            stk.push(opNode); 
        }
    }
    if(stk.size() != 1){
        throw runtime_error("expressão inválida!");
    }

    return stk.top();
}

int posOrdem_calcula(Node *elemento){
    if(elemento == nullptr){
        throw runtime_error("árvore vazia!");
    }

    if(!operador(elemento -> valor)){
        return stoi(elemento -> valor);
    }

    int left_v = posOrdem_calcula(elemento -> left);
    int right_v = posOrdem_calcula(elemento -> right);

    if(elemento -> valor == "+") return left_v + right_v;
    if(elemento -> valor == "-") return left_v - right_v;
    if(elemento -> valor == "*") return left_v * right_v;
    if(elemento -> valor == "/") {
        if(right_v == 0) throw runtime_error("Erro, divisão por zero!");
        return left_v / right_v;
    }

    throw runtime_error("operador inválido!");
}

void posOrdem_freeArvore(Node *elemento){
    if(elemento == nullptr) return;
    posOrdem_freeArvore(elemento -> left);
    posOrdem_freeArvore(elemento -> right);
    delete elemento;
}