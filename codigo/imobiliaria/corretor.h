#ifndef CORRETOR_H
#define CORREOR_H
#include <string>

class Corretor{
private:
    static int nextId;
    int id;
    std::string nome;
    std::string telefone;
    int avaliador;
    double lat;
    double lgt;

public:
    Corretor();
    void setnome(std::string nome1);
    void settelefone(std::string telefone1);
    void setavaliador(int avaliador);
    int getavaliador();
    void setlat(double lat1);
    double getlat();
    void setlgt(double lgt1);
    double getlgt();
    int getid();
   
};

#endif