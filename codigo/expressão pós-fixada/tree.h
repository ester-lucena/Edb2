#ifndef TREE_H
#define TREE_H
#include <string>

struct Node{
    std::string valor;
    Node *left;
    Node *right;

    Node(std::string valor);
};

bool operador(std::string &operador);
Node *arvore(std::string &expressão);
int posOrdem_calcula(Node *elemento);
void posOrdem_freeArvore(Node *elemento);

#endif