#ifndef MEDICO_H
#define MEDICO_H

// Medico.h
// Classe concreta: Medico.
// Define o método avaliarPaciente(Hospital&, Paciente&).
// O método consulta o diagnóstico do paciente; se for "saudável",
// chama Hospital::removerPacienteDoLeito(id).

#include "Pessoa.h"
#include "Paciente.h"
#include "Hospital.h" // necessário para chamar removerPacienteDoLeito

#include <string>
#include <iostream>

class Medico : public Pessoa {
private:
    std::string especialidade;
    std::string crm;

public:
    // Construtor
    Medico() : especialidade("não definida"), crm("não informado") {
        setnome("no-name");
        setidade(0);
    }

    // Construtor com parâmetros
    Medico(const std::string& nome, short int idade, const std::string& especialidade, const std::string& crm) {
        setnome(nome);
        setidade(idade);
        setespecialidade(especialidade);
        setcrm(crm);
    }

    // Get/Set
    void setespecialidade(const std::string& esp) { especialidade = esp; }
    std::string getespecialidade() const { return especialidade; }

    void setcrm(const std::string& c) { crm = c; }
    std::string getcrm() const { return crm; }

    // Método avalia paciente e dá alta se 'saudável'
    void avaliarPaciente(Hospital& h, Paciente& p) {

        if (p.getdiagnostico() == "saudável") {
            h.removerPacienteDoLeito(p.getid());
            std::cout << "Médico " << getnome() << " avaliou: Paciente está saudável. Alta concedida.\n";
        } else {
            std::cout << "Médico " << getnome() << " avaliou: Paciente ainda necessita de tratamento.\n";
        }
    }

    // Implementa display
    void display() const override {
        std::cout << "Médico: " << getnome()
                  << ", Idade: " << getidade()
                  << ", Especialidade: " << getespecialidade()
                  << ", CRM: " << getcrm() << std::endl;
    }
};

#endif
