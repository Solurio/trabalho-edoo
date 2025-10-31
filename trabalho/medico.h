#ifndef MEDICO_H
#define MEDICO_H

#include "Pessoa.h"
#include "Paciente.h"
#include "Hospital.h"

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

    void setespecialidade(const string& esp) { especialidade = esp; }
    string getespecialidade() const { return especialidade; }

    void setcrm(const string& c) { crm = c; }
    string getcrm() const { return crm; }

    void avaliarPaciente(Hospital& h, Paciente& p) {
        if (p.getdiagnostico() == "saudável") {
            h.removerPacienteDoLeito(p.getid());
        } else {
            cout << "Paciente " << p.getnome() << " ainda precisa de tratamento." << endl;
        }
    }

    void display() const override {
        cout << "Médico: " << getnome()
             << ", Idade: " << getidade()
             << ", Especialidade: " << getespecialidade()
             << ", CRM: " << getcrm() << endl;
    }
};

#endif
