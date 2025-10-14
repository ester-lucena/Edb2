#include "cliente.h"
using namespace std;

int Cliente::nextId = 1;

Cliente::Cliente(){
    id = nextId++;
}

void Cliente::setnome(string nome2){
    nome = nome2;
}

void Cliente::settelefone(string telefone2){
    telefone = telefone2;
}