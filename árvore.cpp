#include <iostream>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

struct No{
    string c;
    int freq;
    No* direita;
    No* esquerda;

    No(string c, int freq){
        this -> c = c;
        this -> freq = freq;
        direita = nullptr;
        esquerda = nullptr;
    }
};

//comparador para ordernar do menor para o maior na fila
struct Comparador {
    bool operador(Node &a, Node &b){
        return a.freq > b.freq;
    }
};

int main(){
    ifstream freq("frequencia.txt");
    if(!freq){
        cout << "Erro ao tentar ler o arquivo!" << endl;
        return 1;
    }

    priority_queue<Node, vector<Node>,Comparador> fila;

    return 0;
}
