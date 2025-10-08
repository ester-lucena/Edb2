#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

int main(){

    string nome_arquivo;
    cout << "Digite o arquivo que será comprimido (ex: codigo.cpp)" << endl;
    cin >> nome_arquivo;

    ifstream arquivo(nome_arquivo);
    if(!arquivo){
        cout << "Erro ao abrir o arquivo" << endl;
        return 1;
    }

    map<string, int> freq_palavras;
    map<char, int> freq_simbolos;
    map<char, int> freq_numeros;

    string palavra;
    char c;

    while(arquivo.get(c)){
        if(isdigit(c)){
            freq_numeros[c]++;
        } else if(ispunct(c)){
            freq_simbolos[c]++;
        }
    }

    arquivo.clear();
    arquivo.seekg(0, ios::beg);

    while(arquivo >> palavra){
        string limpa = "";
        for(char c : palavra){
            if(isalpha(c)){
                limpa += c;
            }
        }

        if(!limpa.empty()){
            freq_palavras[limpa]++;
        }
    }

    ofstream saida("frequencia.txt");
    if(!saida){
        cout << "Erro ao criar arquivo de saída!" << endl;
        return 1;
    } 
    
    saida << "[PALAVRAS]" << endl;
    for(auto &p : freq_palavras){
        saida << p.first << " " << p.second << endl;
    }
    saida << "[SIMBOLOS]" << endl;
    for(auto &p : freq_simbolos){
        saida << p.first << " " << p.second << endl;
    }
    saida << "[NUMEROS]" << endl;
    for(auto &p : freq_numeros){
        saida << p.first << " " << p.second << endl;
    }

    cout << "Tabela de frewuencia salva em 'frequencia.txt' com sucesso!" << endl;

    return 0;
}