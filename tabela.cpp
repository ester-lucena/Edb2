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

    //leitura do arquivo
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
        //mapeamento dos números
        if(isdigit(c)){
            freq_numeros[c]++;
        } 
        //mapeamento dos símbolos
        else if(ispunct(c)){
            freq_simbolos[c]++;
        }
    }

    //desbloqueia o fluxo e volta ao início
    arquivo.clear();
    arquivo.seekg(0, ios::beg);

    //mapeamento das palavras/letras
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

    //criação do arquivo que será escrito a saída
    ofstream saida("frequencia.txt");
    if(!saida){
        cout << "Erro ao criar arquivo de saída!" << endl;
        return 1;
    }
    
    //escrevendo no arquivo de saída
    for(auto &p : freq_palavras){
        saida << p.first << " " << p.second << endl;
    }
    for(auto &p : freq_simbolos){
        saida << p.first << " " << p.second << endl;
    }
    for(auto &p : freq_numeros){
        saida << p.first << " " << p.second << endl;
    }

    cout << "Tabela de frequencia salva em 'frequencia.txt' com sucesso!" << endl;

    return 0;
}