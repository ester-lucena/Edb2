#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H
#include <iostream>
#include <string>

using namespace std;

class Funcionario
{
protected:
    string nome;
    float salarioBase;

private:
    int id;

public:
    string getNome();
    void setNome(string n);
    void setSalarioBase(float s);
    float getSalariobase();
    void setID(int i);
    int getID();

    virtual void exibirInformacoes();
    virtual float calcularSalarioFinal() = 0;
};

#endif