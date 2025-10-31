#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Pessoa.h"
#include <vector>
#include <fstream>

class Leito {
public:
    short int numero;
    bool ocupado;
    long int id_paciente;

    Leito(int n = 0) : numero(n), ocupado(false), id_paciente(0) {}

    void ocupar(const Paciente& p) {
        ocupado = true;
        id_paciente = p.getid();
    }

    void liberar() {
        ocupado = false;
        id_paciente = 0;
    }
};

class Hospital {
private:
    string nome;
    vector<Leito> leitos;
    vector<Paciente> pacientes;

public:
    Hospital(string nome = "Sem Nome", int qtdLeitos = 0) : nome(nome) {
        criarLeitos(qtdLeitos);
    }

    void criarLeitos(int qtd) {
        int inicio = leitos.size() + 1;
        for (int i = 0; i < qtd; ++i)
            leitos.push_back(Leito(inicio + i));
        cout << qtd << " leitos criados." << endl;
    }

    void adicionarLeitos(int qtd) { criarLeitos(qtd); }

    void cadastrarPaciente(const Paciente& p) {
        for (auto& pac : pacientes)
            if (pac.getid() == p.getid()) {
                cout << "ID já cadastrado." << endl;
                return;
            }
        pacientes.push_back(p);
        cout << "Paciente " << p.getnome() << " cadastrado." << endl;
    }

    void internarPaciente(long int idPaciente, int numLeito) {
        if (numLeito < 1 || numLeito > (int)leitos.size()) {
            cout << "Leito inválido." << endl;
            return;
        }
        Leito& l = leitos[numLeito - 1];
        if (l.ocupado) {
            cout << "Leito já ocupado." << endl;
            return;
        }
        for (auto& p : pacientes) {
            if (p.getid() == idPaciente) {
                l.ocupar(p);
                cout << "Paciente " << p.getnome()
                     << " internado no leito " << numLeito << "." << endl;
                return;
            }
        }
        cout << "Paciente não encontrado." << endl;
    }

    void liberarLeito(int numLeito) {
        if (numLeito < 1 || numLeito > (int)leitos.size()) {
            cout << "Leito inválido." << endl;
            return;
        }
        Leito& l = leitos[numLeito - 1];
        if (!l.ocupado) {
            cout << "Leito já está disponível." << endl;
            return;
        }
        l.liberar();
        cout << "Leito " << numLeito << " liberado." << endl;
    }

    void listarLeitos() const {
        cout << "\n=== Lista de Leitos ===\n";
        for (const auto& l : leitos) {
            cout << "Leito " << l.numero << " — "
                 << (l.ocupado ? "Ocupado (Paciente ID " + to_string(l.id_paciente) + ")"
                               : "Disponível")
                 << endl;
        }
    }

    void listarPacientes() const {
        cout << "\n=== Pacientes Cadastrados ===\n";
        if (pacientes.empty()) {
            cout << "Nenhum paciente cadastrado." << endl;
            return;
        }
        for (const auto& p : pacientes) p.display();
    }

    void relatorio() const {
        int ocupados = 0;
        for (const auto& l : leitos)
            if (l.ocupado) ++ocupados;
        cout << "\n--- Relatório ---\n";
        cout << "Total de leitos: " << leitos.size() << endl;
        cout << "Ocupados: " << ocupados << endl;
        cout << "Disponíveis: " << leitos.size() - ocupados << endl;
        cout << "Pacientes cadastrados: " << pacientes.size() << endl;
    }

    void exportarJSON(const string& arquivo) const {
        ofstream f(arquivo);
        f << "{\n  \"pacientes\": [\n";
        for (size_t i = 0; i < pacientes.size(); ++i) {
            f << "    {\"id\": " << pacientes[i].getid()
              << ", \"nome\": \"" << pacientes[i].getnome()
              << "\", \"idade\": " << pacientes[i].getidade()
              << ", \"diagnostico\": \"" << pacientes[i].getdiagnostico()
              << "\"}" << (i + 1 < pacientes.size() ? "," : "") << "\n";
        }
        f << "  ],\n  \"leitos\": [\n";
        for (size_t i = 0; i < leitos.size(); ++i) {
            f << "    {\"numero\": " << leitos[i].numero
              << ", \"ocupado\": " << (leitos[i].ocupado ? "true" : "false")
              << ", \"id_paciente\": " << leitos[i].id_paciente << "}"
              << (i + 1 < leitos.size() ? "," : "") << "\n";
        }
        f << "  ]\n}\n";
        f.close();
        cout << "Dados exportados para " << arquivo << endl;
    }

    void resetar() {
        leitos.clear();
        pacientes.clear();
        cout << "Hospital resetado." << endl;
    }
};

void removerPacienteDoLeito(long int idPaciente) {
    for (auto& l : leitos) {
        if (l.ocupado && l.id_paciente == idPaciente) {
            l.liberar();
            cout << "Paciente " << idPaciente << " recebeu alta e deixou o leito.\n";
            return;
        }
    }
    cout << "Paciente não está internado.\n";
}

#endif
