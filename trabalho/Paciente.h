#ifndef PACIENTE_H
#define PACIENTE_H

#include "Pessoa.h"

class Paciente : public Pessoa {
private:
    long int id;
    string diagnostico;

public:
    Paciente() : id(0), diagnostico("não identificado") {
        setnome("no-name");
        setidade(0);
    }

    Paciente(long int id, const string& nome, short int idade, const string& diag) {
        setid(id);
        setnome(nome);
        setidade(idade);
        setdiagnostico(diag);
        cout << "Paciente: " << getnome() << " registrado..." << endl;
    }

    void setid(long int id) { this->id = id; }
    long int getid() const { return id; }

    void setdiagnostico(const string& diag) { diagnostico = diag; }
    string getdiagnostico() const { return diagnostico; }

    void display() const override {
        cout << "Paciente [" << getid() << "]: " << getnome()
             << ", Idade: " << getidade()
             << ", Diagnóstico: " << getdiagnostico() << endl;
    }
};

#endif
