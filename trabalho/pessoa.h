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

    ~Paciente() {}

    void setid(long int id) { this->id = id; }
    long int getid() const { return id; }

    void setdiagnostico(const string& diag) { this->diagnostico = diag; }
    string getdiagnostico() const { return diagnostico; }

    void display() const override {
        cout << "Paciente [" << getid() << "]: " << getnome()
             << ", Idade: " << getidade()
             << ", Diagnóstico: " << getdiagnostico() << endl;
    }
};

class Hospital;

class Medico : public Pessoa {
private:
    string especialidade;
    string crm;

public:
    Medico() : especialidade("não definida"), crm("não informado") {
        setnome("no-name");
        setidade(0);
    }

    Medico(const string& nome, short int idade, const string& especialidade, const string& crm) {
        setnome(nome);
        setidade(idade);
        setespecialidade(especialidade);
        setcrm(crm);
    }

    ~Medico() {}

    void setespecialidade(const string& esp) { this->especialidade = esp; }
    string getespecialidade() const { return especialidade; }

    void setcrm(const string& c) { this->crm = c; }
    string getcrm() const { return crm; }

    void display() const override {
        cout << "Médico: " << getnome()
             << ", Idade: " << getidade()
             << ", Especialidade: " << getespecialidade()
             << ", CRM: " << getcrm() << endl;
    }

    bool avaliarPaciente(long int idPaciente, Hospital& h);
};

#endif

