#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct Node{
    string c;
    int freq;
    Node* right;
    Node* left;

    Node(string c, int freq){
        this -> c = c;
        this -> freq = freq;
        right = nullptr;
        left = nullptr;
    }
};

//comparador para ordernar do menor para o maior na fila
struct Comparador {
    bool operador()(Node* a, Node* b) const {
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
    priority_queue<Node*, vector<Node*>,Comparador> fila;

    //coloca as informações na fila
    string c;
    int freq;
    while (arquivo >> c >> freq){
        Node* novo = new Node(c, freq);
        fila.push(novo);
    }

    while (fila.size() > 1) {
        //retira os menores nós
        Node* left = fila.top(); fila.pop();
        Node* right = fila.top(); fila.pop();
        //cria o novo nó
        int sum = left->freq + right->freq;
        Node* novo = new Node(" ", sum, left, right);
        //coloca na fila
        fila.push(novo);
    }

    //o último nó é a raíz
    Node* root = fila.top();
    
    return 0;
}
