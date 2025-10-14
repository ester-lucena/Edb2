#include "corretor.h"
using namespace std;

int Corretor::nextId = 1;

Corretor::Corretor(){
    id = nextId++;
}

void Corretor::setnome(string nome1){
    nome = nome1;
}

void Corretor::settelefone(string telefone1){
    telefone = telefone1;
}

void Corretor::setavaliador(int avaliador){
    this->avaliador = avaliador;
}

int Corretor::getavaliador(){
    return avaliador;
}

void Corretor::setlat(double lat1){
    lat = lat1;
}

double Corretor::getlat(){
    return lat;
}

void Corretor::setlgt(double lgt1){
    lgt = lgt1;
}

double Corretor::getlgt(){
    return lgt;
}

int Corretor::getid(){
    return id;
}