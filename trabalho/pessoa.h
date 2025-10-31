#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>
using namespace std;

class Pessoa {
private:
    string nome;
    short int idade;

public:
    Pessoa() : nome("no-name"), idade(0) {}
    Pessoa(const string& nome, short int idade) {
        setnome(nome);
        setidade(idade);
    }
    virtual ~Pessoa() {}

    void setnome(const string& nome) { this->nome = nome; }
    string getnome() const { return nome; }

    void setidade(short int idade) { this->idade = idade; }
    short int getidade() const { return idade; }

    virtual void display() const = 0;
};

#endif


