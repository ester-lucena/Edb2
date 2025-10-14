#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

//função que processa um arquivo ignorando comentários
void processFile(const string& path, map<string,int>& freq) {
    ifstream arquivo(path);
    if(!arquivo) {
        cerr << "Erro ao abrir arquivo: " << path << endl;
        return;
    }

    string linha;
    bool inBlockComment = false;

    while(getline(arquivo, linha)) {
        string token = "";
        for(size_t i = 0; i < linha.size(); ++i) {
            if(!inBlockComment) {
                if(i + 1 < linha.size() && linha[i]=='/' && linha[i+1]=='/') break;
                if(i + 1 < linha.size() && linha[i]=='/' && linha[i+1]=='*') {
                    inBlockComment = true; ++i; continue;
                }

                if(isalnum(linha[i]) || linha[i]=='_') {
                    token += linha[i];
                } 
                else if(i + 1 < linha.size() && linha[i]==':' && linha[i+1]==':') {
                    token += "::"; ++i;
                }
                else if(!isspace(linha[i])) {
                    if(!token.empty() && token.size() >= 2) freq[token]++; // conta palavras >=2 letras
                    token = "";
                    string s(1, linha[i]);
                    freq[s]++; // símbolos
                }
                else {
                    if(!token.empty() && token.size() >= 2) freq[token]++;
                    token = "";
                }
            } else {
                if(i + 1 < linha.size() && linha[i]=='*' && linha[i+1]=='/') {
                    inBlockComment = false; ++i;
                }
            }
        }
        if(!token.empty() && token.size() >= 2) freq[token]++;
    }

    arquivo.close();
}
//função que percorre pastas recursivamente
void processFolder(const string& folder, map<string,int>& freq) {
    for(const auto& entry : fs::recursive_directory_iterator(folder)) {
        if(entry.is_regular_file()) {
            string ext = entry.path().extension().string();
            if(ext == ".cpp" || ext == ".h") processFile(entry.path().string(), freq);
        }
    }
}

//ordena mapa por valor (frequência) decrescente
vector<pair<string,int>> sortByValueDesc(const map<string,int>& m) {
    vector<pair<string,int>> vec(m.begin(), m.end());
    sort(vec.begin(), vec.end(), [](const pair<string,int>& a, const pair<string,int>& b){
        return a.second > b.second;
    });
    return vec;
}

int main() {
    string folder;
    cout << "Digite a pasta que será analisada: ";
    cin >> folder;

    map<string,int> freq;
    processFolder(folder, freq);

    ofstream saida("frequencia_huffman.txt");
    if(!saida) {
        cout << "Erro ao criar arquivo de saída!" << endl;
        return 1;
    }

    for(auto &p : sortByValueDesc(freq)) {
        if(p.second > 500) saida << p.first << " " << p.second << endl;
    }

    cout << "Tabela de frequência salva em 'frequencia_huffman.txt' com sucesso!" << endl;
    return 0;
}
