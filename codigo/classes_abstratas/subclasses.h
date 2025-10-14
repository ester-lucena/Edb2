#ifndef SUBCLASSES_H
#define SUBCLASSES_H
#include <iostream>
#include <string>
#include "funcionario.h"

using namespace std;

class Desenvolvedor : public Funcionario
{

private:
    int quantidadeDeProjetos;

public:
    void setProjetos(int projetos);
    float calcularSalarioFinal();
    void exibirInformacoes();
};

class Gerente : public Funcionario
{

private:
    float bonusMensal;

public:
    void setBonusMensal(int bonus);
    float calcularSalarioFinal();
    void exibirInformacoes();
};

class Estagiario : public Funcionario
{

private:
    int horasTrabalhadas;

public:
    void setHorasTrab(int horas);
    float calcularSalarioFinal();
    void exibirInformacoes();
};

#endif