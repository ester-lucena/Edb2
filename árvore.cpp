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