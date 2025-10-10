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
    bool operador()(No* a, No* b) const {
        return a.freq > b.freq;
    }
};


int main(){
    //contador de frequência
    ifstream arquivo("frequencia.txt");
    if(!arquivo){
        cout << "Erro ao tentar ler o arquivo!" << endl;
        return 1;
    }
    
    //criação da fila
    priority_queue<No*, vector<No*>,Comparador> fila;

    //coloca as informações na fila
    string c;
    int freq;
    while (arquivo >> c >> freq){
        No* novo = new No(c, freq);
        fila.push(novo);
    }

    //árvore
    while (fila.size() > 1) {
        //retira os dois menores nós
        No* esquerda = fila.top(); fila.pop();
        No* direita = fila.top(); fila.pop();
        //cria o novo nó
        int soma = esquerda->freq + direita->freq;
        No* novo = new No(" ", soma, esquerda, direita);
        //coloca na fila
        fila.push(novo);
    }

    //o último nó é a raíz
    No* raiz = fila.top();
    
    return 0;
}
