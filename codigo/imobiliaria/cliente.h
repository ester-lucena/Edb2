#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>

class Cliente{
private:
    static int nextId;
    int id;
    std::string nome;
    std::string telefone;
    
public:
    Cliente();
    void setnome(std::string nome2);
    void settelefone(std::string telefone2);

};

#endif