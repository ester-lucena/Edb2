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

    //destrutor: libera a memória
    ~No() {
        delete esquerda;
        delete direita;
    }
};

//comparador para ordernar do menor para o maior na fila
struct Comparador {
    bool operator()(No* a, No* b) const {
        return a -> freq > b -> freq;
    }
};

No* construirArvore(const string& nomeArquivo){
    //leitura da tabela de frequencia
    ifstream arquivo(nomeArquivo);
    if(!arquivo) {
        cout << "Erro ao tentar ler o arquivo!" << endl;
        return nullptr;
    }
    
    //criação da fila
    priority_queue<No*, vector<No*>,Comparador> fila;

    //coloca as informações na fila
    string c;
    int freq;
    while (arquivo >> c >> freq) {
        No* novo = new No(c, freq);
        fila.push(novo);
    }
    
    if (fila.empty()) {
        cout << "Erro: a fila está vazia. O arquivo pode estar vazio ou mal formatado." << endl;
        return nullptr;
    }

    //árvore
    while (fila.size() > 1) {
        //pega e retira os dois menores nós
        No* esquerda = fila.top(); 
        fila.pop();
        No* direita = fila.top(); 
        fila.pop();
        
        //cria o novo nó
        int soma = esquerda -> freq + direita -> freq;
        No* novo = new No(" ", soma);
        
        // liga os filhos à esquerda e à direita
        novo -> esquerda = esquerda;
        novo -> direita = direita; 
        
        //coloca na fila
        fila.push(novo);
    }

    //retorna a raíz, elemento mais frequente
    return fila.top();
}

void gerarCodigos(No* raiz, string codigo, map<string, string>& tabela) {
    if (!raiz) return;

    // folha = símbolo real
    if (!raiz -> esquerda && !raiz -> direita && raiz -> c != " ") {
        tabela[raiz -> c] = codigo;
        return;
    }

    gerarCodigos(raiz->esquerda, codigo + "0", tabela);
    gerarCodigos(raiz->direita, codigo + "1", tabela);
}

int main(){
    string nomeArquivo = "frequencia.txt";
    No* raiz = construirArvore(nomeArquivo);
    
    cout << "Árvore criada com sucesso! Frequência total: " << raiz -> freq << endl;
    
    map<string, string> tabelaCodigos;
    gerarCodigos(raiz, "", tabelaCodigos);

    // cria o arquivo de saída
    string nomeSaida = "codigos_huffman.txt";
    ofstream arquivoSaida(nomeSaida);
    if (!arquivoSaida) {
        cout << "Erro ao criar o arquivo de saída!" << endl;
        delete raiz;
        return 1;
    }

    // grava todos os códigos no arquivo
    for (auto& par : tabelaCodigos) {
        arquivoSaida << par.first << " " << par.second << "\n";
    }

    arquivoSaida.close();
    cout << "Códigos de Huffman salvos em: " << nomeSaida << endl;

    delete raiz;

    return 0;
}