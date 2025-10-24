#ifndef PACIENTE_H
#define PACIENTE_H
#include <string>
#include <iostream>

using namespace std;


class Paciente {
    private:
    long int id;
    std::string nome;
    short int idade;
    std::string diagnostico;

    public:
    Paciente() : id(0), nome("qualquer"), idade(0), diagnostico("não identificado") {}
    ~Paciente() {}; 

    Paciente(long int id ,const string& nome, short int idade, const string& diag) {
        setid(id);
        setnome(nome);
        setidade(idade);
        setdiagnostico(diag);
        std::cout <<"paciente: " <<nome<< " registrado..."<<std::endl;

    }

    void setid (long int id) {
        this->id = id;
    }

    long int getid () const {
        return id;
    }

    void setnome (const string& nome ) {
        this->nome = nome;
    }
    void setidade (int idade) {
        this->idade = idade;
    }
    void setdiagnostico (const string& diagnostico) {
        this->diagnostico = diagnostico;
    }
};



#endif