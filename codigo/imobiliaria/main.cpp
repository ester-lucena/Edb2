#define _USE_MATH_DEFINES
#include "corretor.h"
#include "cliente.h"
#include "imovel.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

constexpr double EARTH_R = 6371.0; // Raio da Terra em km

double haversine(double lat1, double lon1, double lat2, double lon2) {
    auto deg2rad = [](double d){ return d * M_PI / 180.0; };
    double dlat = deg2rad(lat2 - lat1);
    double dlon = deg2rad(lon2 - lon1);
    double a = pow(sin(dlat/2), 2) +
               cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
               pow(sin(dlon/2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_R * c;
}

int main(){
    //classe corretor
    int ncorretores, avaliador;
    string nome1, telefone1;
    double lat1, lgt1;
    vector<Corretor> avaliadores;

    cin >> ncorretores;

    for(int i=0; i<ncorretores; i++){
        cin >> telefone1 >> avaliador >> lat1 >> lgt1;
        getline(cin >> ws, nome1);

        Corretor c;
        c.setnome(nome1);
        c.settelefone(telefone1);
        c.setavaliador(avaliador);
        c.setlat(lat1);
        c.setlgt(lgt1);
        if (c.getavaliador() == 1) {
            avaliadores.push_back(c);
        }
    }

    //classe cliente
    int nclientes;
    string nome2, telefone2;
    vector<Cliente> clientes;

    cin >> nclientes;

    for(int i=0; i<nclientes; i++){
        cin >> telefone2;
        getline(cin >> ws, nome2);

        Cliente cl;
        cl.setnome(nome2);
        cl.settelefone(telefone2);
        clientes.push_back(cl);
        
    }

    //classe imoveis
    int nimoveis, proprietario_id;
    string tipo;
    double lat2, lgt2, preco;
    string endereco;
    vector<Imovel> imoveis;

    cin >> nimoveis;

    for(int i=0; i<nimoveis; i++){
        cin >> tipo >> proprietario_id >> lat2 >> lgt2 >> preco;
        getline(cin >> ws, endereco);
        
        Imovel im;
        im.settipo(tipo);
        im.setproprietario_id(proprietario_id);
        im.setlat(lat2);
        im.setlgt(lgt2);
        im.setendereco(endereco);
        im.setpreco(preco);
        imoveis.push_back(im);
     
    }

    //ordena imoveis por id
    sort(imoveis.begin(), imoveis.end(), [](Imovel a, Imovel b){
        return a.getid() < b.getid();
    });
    
    //lista de imóveis para cada avaliador
    vector<vector<Imovel>> distribuidos(avaliadores.size()); 

    //for que distribuí circularmente
    for(size_t i = 0; i < imoveis.size(); ++i){
        size_t idx = i % avaliadores.size(); 
        distribuidos[idx].push_back(imoveis[i]);
    }

    //for para os corretores
    for (size_t i = 0; i < avaliadores.size(); ++i) {
        Corretor corretor = avaliadores[i];
        vector<Imovel>& lista = distribuidos[i];

        vector<bool> visitado(lista.size(), false);
        double at_lat = corretor.getlat();
        double at_lgt = corretor.getlgt();

        int hora = 9, minuto = 0;

        cout << "Corretor " << corretor.getid() << endl;

        //for para os imoveis
        for (size_t j = 0; j < lista.size(); ++j) {
            int prox = -1;
            double min_dist = 1e9;

            //for para encontrar imóvel mais próximo
            for (size_t k = 0; k < lista.size(); ++k) {
                if (!visitado[k]) {
                    double dist = haversine(at_lat, at_lgt, lista[k].getlat(), lista[k].getlgt());
                    if (dist < min_dist) {
                        min_dist = dist;
                        prox = static_cast<int>(k);
                    }
                }
            }

            if (prox == -1) break;

            visitado[prox] = true;

            //calcular tempo de deslocamento
            double tempo_deslocamento = min_dist * 2;
            minuto += static_cast<int>(tempo_deslocamento);
            while (minuto >= 60) {
                minuto -= 60;
                hora += 1;
            }

            cout << setfill('0') << setw(2) << hora << ":"
                << setw(2) << minuto << " Imóvel " << lista[prox].getid() << endl;

            //avaliação dura 1h
            hora += 1;

            //atualiza prox para a localização atual
            at_lat = lista[prox].getlat();
            at_lgt = lista[prox].getlgt();

        }
        //linha em branco entre corretores
        if (i + 1 < avaliadores.size()) {
            cout << '\n'; 
        }
    }

    return 0;
}