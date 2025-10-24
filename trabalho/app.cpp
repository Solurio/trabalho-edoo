#include <iostream> 
#include "hospital.h"

using namespace std;


int main()
{
    std::cout << "apresentando a aplicação do hospital" <<std::endl << std::endl;
    bool desligar = false; 
    int opcao;
    long int id;
    std::string nome;
    short int idade;
    std::string dia;

    Paciente p1;
    Hospital h1;


    while (desligar == false) {
        std:: cout << "pressione 1: para registrar o paciente" <<std::endl; 
        std:: cout << "pressione 2: para registrar o hospital" <<std::endl;
        std:: cout << "pressione 3: para fechar a registrar no leito" << std::endl;
        std:: cout << "pressione 4: fechar a aplicação" << std::endl;
        std:: cin >> opcao;

        switch (opcao){
            case 1: 
             std::cout << "Digite o ID do paciente: ";
             std::cin >> id;
             std::cout << "Digite o nome do paciente: ";
             std::cin >> nome;
             std::cout << "Digite a idade do paciente: ";
             std::cin >> idade;
             std::cout << "Digite o diagnóstico do paciente: ";
             std::cin >> dia;
             p1 = Paciente(id, nome, idade, dia);
             break;

            case 2:
            h1 = Hospital();
            std::cout << "Hospital registrado com 10 leitos." << std::endl;
            break;

            case 3:
            h1.ocupar_leito(p1);
            break;

            case 4 :
            desligar = true;
            break;

            default:
            std::cout << "Opção inválida." << std::endl;
            break;

        }

    }
    
    return 0;
}
