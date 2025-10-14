#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cctype>

using namespace std;


//tabela hard-coded de Huffman(baseada na de frequência)
unordered_map<string, string> codigosHuffman = {
    //operadores e símbolos mais frequentes
    {"(", "0000"}, {")", "0001"}, {";", "0010"}, {",", "0011"}, {".", "0100"},
    {">", "0101"}, {"=", "0110"}, {"<", "0111"}, {"}", "1000"}, {"{", "1001"},
    {"\"", "1010"}, {"#", "1011"}, {"&", "1100"}, {"-", "1101"}, {"*", "1110"},
    {"/", "1111"}, {"[", "10000"}, {"]", "10001"}, {":", "10010"}, {"!", "10011"},
    {"+", "10100"}, {"\\", "10101"}, {"|", "10110"}, {"%", "10111"},

    //palavras-chave mais frequentes
    {"const", "11000"}, {"include", "11001"}, {"return", "11010"}, {"void", "11011"},
    {"if", "11100"}, {"typename", "11101"}, {"int", "11110"}, {"template", "11111"},
    {"bool", "100000"}, {"auto", "100001"}, {"sizeof", "100010"}, {"define", "100011"},
    {"false", "100100"}, {"endif", "100101"}, {"this", "100110"}, {"size_t", "100111"},
    {"static", "101000"}, {"using", "101001"}, {"true", "101010"}, {"char", "101011"},
    {"std::string", "101100"}, {"class", "101101"}, {"nullptr", "101110"},
    {"else", "101111"}, {"struct", "110000"}, {"public", "110001"},

    //números
    {"0", "110010"}, {"1", "110011"}, {"2", "110100"}, {"3", "110101"}, {"4", "110110"},
    {"5", "110111"}, {"6", "111000"}, {"7", "111001"}, {"8", "111010"}, {"9", "111011"},

    //alfabeto
    {"a", "111100"}, {"b", "111101"}, {"c", "1111100"}, {"d", "1111101"}, {"e", "1111110"},
    {"f", "1111111"}, {"g", "1000000"}, {"h", "1000001"}, {"i", "1000010"}, {"j", "1000011"},
    {"k", "1000100"}, {"l", "1000101"}, {"m", "1000110"}, {"n", "1000111"}, {"o", "1001000"},
    {"p", "1001001"}, {"q", "1001010"}, {"r", "1001011"}, {"s", "1001100"}, {"t", "1001101"},
    {"u", "1001110"}, {"v", "1001111"}, {"w", "1010000"}, {"x", "1010001"}, {"y", "1010010"},
    {"z", "1010011"}
};

//Compressão
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
        if (isalnum(c) || c == '_') {
            //faz parte de uma palavra/chave
            token += c;
        } else {
            //fim do token (palavra)
            if (!token.empty()) {
                if (codigosHuffman.count(token)) {
                    bits += codigosHuffman[token];
                } else {
                    //fallback: codifica letra por letra
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

            //codifica o símbolo atual (como ; , { } etc)
            string s(1, c);
            if (codigosHuffman.count(s))
                bits += codigosHuffman[s];
        }
    }

    //processa o último token
    if (!token.empty()) {
        if (codigosHuffman.count(token)) {
            bits += codigosHuffman[token];
        } else {
            for (char ch : token) {
                string s(1, ch);
                if (codigosHuffman.count(s))
                    bits += codigosHuffman[s];
            }
        }
    }

    //converte os bits em bytes
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

//Descompressão
void descomprimir(string nomeArquivoEntrada, string nomeArquivoSaida) {
    ifstream entrada(nomeArquivoEntrada, ios::binary);
    ofstream saida(nomeArquivoSaida);

    if (!entrada.is_open() || !saida.is_open()) {
        cerr << "Erro ao abrir arquivos.\n";
        return;
    }

    //cria tabela inversa (código → símbolo)
    unordered_map<string, string> inverso;
    for (auto &par : codigosHuffman)
        inverso[par.second] = par.first;

    string bits = "";
    unsigned char byte;
    while (entrada.read(reinterpret_cast<char*>(&byte), 1)) {
        for (int i = 7; i >= 0; i--)
            bits += ((byte >> i) & 1) ? '1' : '0';
    }

    string buffer = "";
    for (char bit : bits) {
        buffer += bit;
        if (inverso.count(buffer)) {
            saida << inverso[buffer];
            buffer.clear();
        }
    }

    entrada.close();
    saida.close();
    cout << "Arquivo descomprimido com sucesso em: " << nomeArquivoSaida << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Uso:\n";
        cout << "  programa -c entrada.txt saida.bin   (comprimir)\n";
        cout << "  programa -d entrada.bin saida.txt   (descomprimir)\n";
        return 1;
    }

    string opcao = argv[1];
    string entrada = argv[2];
    string saida = argv[3];

    if (opcao == "-c") {
        comprimir(entrada, saida);
    } else if (opcao == "-d") {
        descomprimir(entrada, saida);
    } else {
        cerr << "Opção inválida. Use -c (compressão) ou -d (descompressão).\n";
    }

    return 0;
}
