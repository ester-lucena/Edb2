#include "tree.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(){

    string expressão;
    cout << "digite a expressão pósfixada: " << endl;
    getline(cin, expressão);

    try{
        Node *elemento = arvore(expressão);
        int resultado = posOrdem_calcula(elemento);
        cout << "Resultado: " << resultado << endl;
        posOrdem_freeArvore(elemento);
    } catch(const exception& e){
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}