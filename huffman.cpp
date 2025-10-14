#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

//tabela hard code
unordered_map<string, string> codigosHuffman = {
    // palavras-chave + comuns
    {"int", "0000"}, {"main", "0001"}, {"return", "0010"}, {"if", "0011"},
    {"for", "0100"}, {"while", "0101"}, {"cout", "0110"}, {"else", "0111"},
    {"float", "1000"}, {"double", "1001"}, {"char", "1010"}, {"bool", "1011"},

    //alfabeto
    {"a", "1100"}, {"b", "1101"}, {"c", "1110"}, {"d", "1111"}, {"e", "10000"},
    {"f", "10001"}, {"g", "10010"}, {"h", "10011"}, {"i", "10100"}, {"j", "10101"},
    {"k", "10110"}, {"l", "10111"}, {"m", "11000"}, {"n", "11001"}, {"o", "11010"},
    {"p", "11011"}, {"q", "11100"}, {"r", "11101"}, {"s", "11110"}, {"t", "11111"},
    {"u", "100000"}, {"v", "100001"}, {"w", "100010"}, {"x", "100011"}, {"y", "100100"},
    {"z", "100101"},

    //números
    {"0", "100110"}, {"1", "100111"}, {"2", "101000"}, {"3", "101001"}, {"4", "101010"},
    {"5", "101011"}, {"6", "101100"}, {"7", "101101"}, {"8", "101110"}, {"9", "101111"},

    //operadores e símbolos + comuns
    {";", "110000"}, {"(", "110001"}, {")", "110010"}, {"{", "110011"}, {"}", "110100"},
    {"+", "110101"}, {"-", "110110"}, {"*", "110111"}, {"/", "111000"}, {"=", "111001"},
    {"<", "111010"}, {">", "111011"}, {"==", "111100"}, {"!=", "111101"}
};

//compressão
void comprimir(string nomeArquivoEntrada, string nomeArquivoSaida) {
    ifstream entrada(nomeArquivoEntrada);
    ofstream saida(nomeArquivoSaida, ios::binary);

    if (!entrada.is_open() || !saida.is_open()) {
        cerr << "Erro ao abrir arquivos.\n";
        return;
    }

    string bits = "";
    string token = "";
    char c;

    while (entrada.get(c)) {
        if (isalnum(c)) { //parte de palavra/número
            token += c;
        } else { //símbolo ou separador
            if (!token.empty()) {
                if (codigosHuffman.count(token)) {
                    bits += codigosHuffman[token]; //token definido
                } else {
                    //fallback: cada letra do token
                    for (char ch : token) {
                        string s(1, ch);
                        if (codigosHuffman.count(s))
                            bits += codigosHuffman[s];
                        else
                            cerr << "Aviso: caractere '" << ch << "' não possui código.\n";
                    }
                }
                token.clear();
            }

            //símbolos individuais
            string s(1, c);
            if (codigosHuffman.count(s))
                bits += codigosHuffman[s];
        }
    }

    //último token
    if (!token.empty()) {
        if (codigosHuffman.count(token)) {
            bits += codigosHuffman[token];
        } else {
            for (char ch : token) {
                string s(1, ch);
                if (codigosHuffman.count(s))
                    bits += codigosHuffman[s];
                else
                    cerr << "Aviso: caractere '" << ch << "' não possui código.\n";
            }
        }
    }

    //escreve bits em bytes
    unsigned char byte = 0;
    int bitCount = 0;
    for (char bit : bits) {
        byte = (byte << 1) | (bit - '0');
        bitCount++;
        if (bitCount == 8) {
            saida.put(byte);
            byte = 0;
            bitCount = 0;
        }
    }
    if (bitCount > 0) {
        byte <<= (8 - bitCount);
        saida.put(byte);
    }

    entrada.close();
    saida.close();
    cout << "Arquivo comprimido com sucesso em: " << nomeArquivoSaida << endl;
}

//descompressão
void descomprimir(string nomeArquivoEntrada, string nomeArquivoSaida) {
    ifstream entrada(nomeArquivoEntrada, ios::binary);
    ofstream saida(nomeArquivoSaida);

    if (!entrada.is_open() || !saida.is_open()) {
        cerr << "Erro ao abrir arquivos.\n";
        return;
    }

    //tabela inversa: código -> token
    unordered_map<string, string> inverso;
    for (auto& par : codigosHuffman)
        inverso[par.second] = par.first;

    string bits = "";
    unsigned char byte;
    while (entrada.read((char*)&byte, 1)) {
        for (int i = 7; i >= 0; i--)
            bits += ((byte >> i) & 1) ? '1' : '0';
    }

    string buffer = "";
    for (char bit : bits) {
        buffer += bit;
        if (inverso.count(buffer)) {
            saida << inverso[buffer]; //não precisa adicionar espaço, letras concatenam
            buffer.clear();
        }
    }

    entrada.close();
    saida.close();
    cout << "Arquivo descomprimido com sucesso em: " << nomeArquivoSaida << endl;
}

//escolhe se vai ser compressão ou descompressão
int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Uso: programa -c entrada.txt saida.bin  (comprimir)\n";
        cout << "     programa -d entrada.bin saida.txt  (descomprimir)\n";
        return 1;
    }

    string opcao = argv[1];
    string entrada = argv[2];
    string saida = argv[3];

    if (opcao == "-c") {
        comprimir(entrada, saida);
    } 
    else if (opcao == "-d") {
        descomprimir(entrada, saida);
    } 
    else {
        cout << "Opção inválida. Use -c (compressão) ou -d (descompressão).\n";
    }

    return 0;
}