#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <locale>
#include <codecvt>
#include <cwctype>

using namespace std;

//tabela hard-coded de Huffman(baseada na de frequência)
unordered_map<wstring, wstring> codigosHuffman = {
    //operadores e símbolos mais frequentes
    {L"(", L"0000"}, {L")", L"0001"}, {L";", L"0010"}, {L",", L"0011"}, {L".", L"0100"},
    {L">", L"0101"}, {L"=", L"0110"}, {L"<", L"0111"}, {L"}", L"1000"}, {L"{", L"1001"},
    {L"\"", L"1010"}, {L"#", L"1011"}, {L"&", L"1100"}, {L"-", L"1101"}, {L"*", L"1110"},
    {L"/", L"1111"}, {L"[", L"10000"}, {L"]", L"10001"}, {L":", L"10010"}, {L"!", L"10011"},
    {L"+", L"10100"}, {L"\\", L"10101"}, {L"|", L"10110"}, {L"%", L"10111"},

    //espaços, tabs e quebras de linha
    {L" ", L"1110000"}, {L"\n", L"1110001"}, {L"\t", L"1110010"},

    //palavras-chave mais frequentes
    {L"const", L"11000"}, {L"include", L"11001"}, {L"return", L"11010"}, {L"void", L"11011"},
    {L"if", L"11100"}, {L"typename", L"11101"}, {L"int", L"11110"}, {L"template", L"11111"},
    {L"bool", L"100000"}, {L"auto", L"100001"}, {L"sizeof", L"100010"}, {L"define", L"100011"},
    {L"false", L"100100"}, {L"endif", L"100101"}, {L"this", L"100110"}, {L"size_t", L"100111"},
    {L"static", L"101000"}, {L"using", L"101001"}, {L"true", L"101010"}, {L"char", L"101011"},
    {L"std::string", L"101100"}, {L"class", L"101101"}, {L"nullptr", L"101110"},
    {L"else", L"101111"}, {L"struct", L"110000"}, {L"public", L"110001"},

    //números
    {L"0", L"110010"}, {L"1", L"110011"}, {L"2", L"110100"}, {L"3", L"110101"}, {L"4", L"110110"},
    {L"5", L"110111"}, {L"6", L"111000"}, {L"7", L"111001"}, {L"8", L"111010"}, {L"9", L"111011"},

    //alfabeto
    {L"a", L"111100"}, {L"b", L"111101"}, {L"c", L"1111100"}, {L"d", L"1111101"}, {L"e", L"1111110"},
    {L"f", L"1111111"}, {L"g", L"1000000"}, {L"h", L"1000001"}, {L"i", L"1000010"}, {L"j", L"1000011"},
    {L"k", L"1000100"}, {L"l", L"1000101"}, {L"m", L"1000110"}, {L"n", L"1000111"}, {L"o", L"1001000"},
    {L"p", L"1001001"}, {L"q", L"1001010"}, {L"r", L"1001011"}, {L"s", L"1001100"}, {L"t", L"1001101"},
    {L"u", L"1001110"}, {L"v", L"1001111"}, {L"w", L"1010000"}, {L"x", L"1010001"}, {L"y", L"1010010"},
    {L"z", L"1010011"},

    //acentos básicos
    {L"á", L"1010101"}, {L"é", L"1010110"}, {L"í", L"1010111"}, {L"ó", L"1011000"}, {L"ú", L"1011001"},
    {L"ã", L"1011010"}, {L"õ", L"1011011"}, {L"ç", L"1011100"}, {L"Á", L"1011101"}, {L"É", L"1011110"},
    {L"Í", L"1011111"}, {L"Ó", L"10000000"}, {L"Ú", L"10000001"}, {L"Ç", L"10000010"}
};

//Compressão
void comprimir(string nomeEntrada, string nomeSaida) {
    wifstream entrada(nomeEntrada);
    entrada.imbue(locale(locale(), new codecvt_utf8<wchar_t>()));
    wofstream saida(nomeSaida);
    saida.imbue(locale(locale(), new codecvt_utf8<wchar_t>()));

    if (!entrada.is_open() || !saida.is_open()) {
        cerr << "Erro ao abrir arquivos.\n";
        return;
    }

    wstring token = L"";
    wchar_t c;

    while (entrada.get(c)) {
        if (iswalnum(c) || c == L'_') {
            token += c;
        } else {
            //processa palavra acumulada
            if (!token.empty()) {
                if (codigosHuffman.count(token))
                    saida << codigosHuffman[token] << " ";
                else {
                    for (wchar_t wc : token) {
                        wstring s(1, wc);
                        if (codigosHuffman.count(s))
                            saida << codigosHuffman[s] << " ";
                        else
                            saida << "? ";
                    }
                }
                token.clear();
            }
            //processa símbolo ou espaço/tab/nova linha
            wstring s(1, c);
            if (codigosHuffman.count(s))
                saida << codigosHuffman[s] << " ";
        }
    }

    //processa último token
    if (!token.empty()) {
        if (codigosHuffman.count(token))
            saida << codigosHuffman[token] << " ";
        else {
            for (wchar_t wc : token) {
                wstring s(1, wc);
                if (codigosHuffman.count(s))
                    saida << codigosHuffman[s] << " ";
                else
                    saida << "? ";
            }
        }
    }

    entrada.close();
    saida.close();
    cout << "Arquivo comprimido com sucesso em: " << nomeSaida << endl;
}

//Descompressão
void descomprimir(string nomeEntrada, string nomeSaida) {
    ifstream entrada(nomeEntrada);
    wofstream saida(nomeSaida);
    saida.imbue(locale(locale(), new codecvt_utf8<wchar_t>()));

    if (!entrada.is_open() || !saida.is_open()) {
        cerr << "Erro ao abrir arquivos.\n";
        return;
    }

    //converte tabela para string UTF-8 (inversa)
    unordered_map<string, wstring> inverso;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> conversor;
    for (auto &par : codigosHuffman)
        inverso[conversor.to_bytes(par.second)] = par.first;

    string codigo;
    while (entrada >> codigo) {
        if (inverso.count(codigo))
            saida << inverso[codigo];
        else
            saida << L"?";
    }

    entrada.close();
    saida.close();
    cout << "Arquivo descomprimido com sucesso em: " << nomeSaida << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Uso:\n";
        cout << "  programa -c entrada.txt saida.txt   (comprimir)\n";
        cout << "  programa -d entrada.txt saida.txt   (descomprimir)\n";
        return 1;
    }

    string opcao = argv[1];
    string entrada = argv[2];
    string saida = argv[3];

    if (opcao == "-c")
        comprimir(entrada, saida);
    else if (opcao == "-d")
        descomprimir(entrada, saida);
    else
        cerr << "Opção inválida. Use -c ou -d.\n";

    return 0;
}
