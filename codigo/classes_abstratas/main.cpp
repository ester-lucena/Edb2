#include <iostream>
#include "funcionario.h"
#include "subclasses.h"

using namespace std;

int main()
{
    Funcionario *lista[10];
    int n;

    cout << "Quantos funcionarios deseja cadastrar?(min 6 - máx 10): ";
    cin >> n;

    while(n<6){
       cout << "número de funcionários insuficiente!(cadastre no mínimo 6 funcionários)" << endl;
       cout << "Quantos funcionarios deseja cadastrar?(min 6 - máx 10): ";
       cin >> n;
    }

    while(n>10){
        cout << "número de funcionários extrapolado!(cadastre no máximo 10 funcionários)" << endl;
        cout << "Quantos funcionarios deseja cadastrar?(min 6 - máx 10): ";
        cin >> n;
    }

    for (int i = 0; i < n; i++)
    {
        string nome;
        int id, salarioBase, tipo;
        cout << "ID: ";
        cin >> id;
        cout << "Nome: ";
        cin >> nome;
        cout << "Salario Base: ";
        cin >> salarioBase;
        cout << "Tipo (1-Desenvolvedor, 2-Gerente, 3-Estagiario): ";
        cin >> tipo;

        if (tipo == 1)
        {
            lista[i] = new Desenvolvedor();
            int projetos;
            cout << "Projetos: ";
            cin >> projetos;

            Desenvolvedor *d = dynamic_cast<Desenvolvedor *>(lista[i]);

            d->setProjetos(projetos);
            d->setID(id);
            d->setNome(nome);
            d->setSalarioBase(salarioBase);
        }
        else if (tipo == 2)
        {
            lista[i] = new Gerente();
            int bonus;
            cout << "Bonus: ";
            cin >> bonus;

            Gerente *g = dynamic_cast<Gerente *>(lista[i]);

            g->setBonusMensal(bonus);
            g->setID(id);
            g->setNome(nome);
            g->setSalarioBase(salarioBase);
        }
        else if (tipo == 3)
        {
            lista[i] = new Estagiario();
            int horas;
            cout << "Horas trabalhadas: ";
            cin >> horas;

            Estagiario *e = dynamic_cast<Estagiario *>(lista[i]);

            e->setHorasTrab(horas);
            e->setID(id);
            e->setNome(nome);
            e->setSalarioBase(salarioBase);
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        lista[i]->exibirInformacoes();
        cout << endl;
    }

    return 0;
}