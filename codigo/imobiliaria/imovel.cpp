#include "imovel.h"
using namespace std;

int Imovel::nextId = 1;

Imovel::Imovel(){
    id = nextId++;
}

void Imovel::settipo(string tipo){
    this->tipo = tipo;
}

void Imovel::setproprietario_id(int proprietario_id){
    this->proprietario_id = proprietario_id;
}

void Imovel::setlat(double lat2){
    lat = lat2;
}

double Imovel::getlat(){
    return lat;
}

void Imovel::setlgt(double lgt2){
    lgt = lgt2;
}

double Imovel::getlgt(){
    return lgt;
}

void Imovel::setendereco(string endereco){
    this->endereco = endereco;
}

void Imovel::setpreco(double preco){
    this->preco = preco;
}

int Imovel::getid(){
    return id;
}