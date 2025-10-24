#ifndef HOSPITAL_H
#define HOSPITAL_H
#include "paciente.h"
#include <vector> 

using namespace std;


class Leito {
    public:
    long int id_paciente;
    bool ocupado;
   

    Leito() : id_paciente(0), ocupado(false) {};
    ~Leito() {};

    void registrar_leito (Paciente a) {
        this->id_paciente = a.getid() ;
        this->ocupado = true;
    }
};

class Hospital
{
    private:
    std::string hospital_name;
    std::vector<Leito> leitos;

    public:
    Hospital(): hospital_name("qualquer"), leitos(10) {} ;
    ~Hospital() {};

    void ocupar_leito (const Paciente& a) {
        for (Leito& leito : leitos) { // size_t i = 0; i < leitos.size(); ++i
            if (!leito.ocupado) {
                leito.registrar_leito(a);
                std::cout << "Paciente alocado em leito com ID: " << leito.id_paciente << std::endl;
                return; }
            else std::cout << "Nenhum leito disponível para o paciente ID: " << a.getid() << std::endl;

        }

    }



};





#endif