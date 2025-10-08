#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    ifstream myfile("texto.txt");
    //myfile.open("texto.txt");
    if(!myfile){
        cerr << "Erro ao abrir o arquivo" << endl;
        return 1;
    }
    stringstream buffer;
    buffer << myfile.rdbuf();
    cout << buffer.str();

    //letras
    //numeros
    //caracteres especiais
    //loops: do - while - for
    //if - else if - else
    //include
    //cout - cin - endl 
    //tipos
    //return
    //std
    

    return 0;
}