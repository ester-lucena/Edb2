#include <iostream>
#include <iomanip>
#include "subclasses.h"

using namespace std;

void Desenvolvedor::setProjetos(int projetos)
{
    quantidadeDeProjetos = projetos;
}

float Desenvolvedor::calcularSalarioFinal()
{
    return salarioBase + (500 * quantidadeDeProjetos);
}

void Desenvolvedor::exibirInformacoes()
{
    cout << "ID: " << getID() << endl;
    cout << "Nome: " << getNome() << endl;
    cout << "Tipo: Desenvolvedor" << endl;
    cout << "Projetos: " << quantidadeDeProjetos << endl;
    cout << "Salário base: " << fixed << setprecision(2) << getSalariobase() << endl;
    cout << "Salário final: " << fixed << setprecision(2) << calcularSalarioFinal() << endl;
}

void Gerente::setBonusMensal(int bonus)
{
    bonusMensal = bonus;
}

float Gerente::calcularSalarioFinal()
{
    return salarioBase + bonusMensal;
}

void Gerente::exibirInformacoes()
{
    cout << "ID: " << getID() << endl;
    cout << "Nome: " << getNome() << endl;
    cout << "Tipo: Gerente" << endl;
    cout << "Bonus: " << bonusMensal << endl;
    cout << "Salário base: " << fixed << setprecision(2) << getSalariobase() << endl;
    cout << "Salário final: " << fixed << setprecision(2) << calcularSalarioFinal() << endl;
}

void Estagiario::setHorasTrab(int horas)
{
    horasTrabalhadas = horas;
}

float Estagiario::calcularSalarioFinal()
{
    return salarioBase * (horasTrabalhadas / 160.0);
}

void Estagiario::exibirInformacoes()
{
    cout << "ID: " << getID() << endl;
    cout << "Nome: " << getNome() << endl;
    cout << "Tipo: Estagiário" << endl;
    cout << "Horas trabalhadas: " << horasTrabalhadas << endl;
    cout << "Salário base: " << fixed << setprecision(2) << getSalariobase() << endl;
    cout << "Salário final: " << fixed << setprecision(2) << calcularSalarioFinal() << endl;
}