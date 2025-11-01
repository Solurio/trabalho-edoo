#ifndef HOSPITAL_H
#define HOSPITAL_H

// Hospital.h
// Define Leito e Hospital.
// FunçÕes: CriarLeitos, cadastrarPaciente,
// internarPaciente, liberarLeito, listarLeitos, listarPacientes,
// relatorio, exportarJSON, resetar.
// Adiciona getPacientes() (necessário para main) e
// removerPacienteDoLeito() (método usado por Medico::avaliarPaciente).

#include "Paciente.h"
#include <vector>
#include <fstream>
#include <iostream>

class Leito {
public:
    short int numero;     // número do leito (identificador)
    bool ocupado;         // se um paciente ocupa esse leito (1 paciente por leito)
    long int id_paciente; // id do paciente que está no leito (0 = nenhum)

    // Construtor livre. Define número e estado inicial
    Leito(int n = 0) : numero(n), ocupado(false), id_paciente(0) {}

    // Ocupar leito com um paciente (usa getid do Paciente)
    void ocupar(const Paciente& p) {
        ocupado = true;
        id_paciente = p.getid();
    }

    // Liberar leito
    void liberar() {
        ocupado = false;
        id_paciente = 0;
    }
};

class Hospital {
private:
    std::string nome;
    std::vector<Leito> leitos;
    std::vector<Paciente> pacientes;

public:
    // Construtor
    Hospital(std::string nome = "Sem Nome", int qtdLeitos = 0) : nome(nome) {
        criarLeitos(qtdLeitos);
    }

    // Acesso direto (necessário para a interface do main)
    // Retorna referência ao vetor de pacientes
    std::vector<Paciente>& getPacientes() { return pacientes; }

    // Cria 'qtd' novos leitos, numerando sequencialmente
    void criarLeitos(int qtd) {
        int inicio = static_cast<int>(leitos.size()) + 1;
        for (int i = 0; i < qtd; ++i)
            leitos.push_back(Leito(inicio + i));
        std::cout << qtd << " leitos criados." << std::endl;
    }

    // Adiciona leitos (wrapper)
    void adicionarLeitos(int qtd) { criarLeitos(qtd); }

    // Cadastra paciente (verifica ID duplicado)
    void cadastrarPaciente(const Paciente& p) {
        for (const auto& pac : pacientes)
            if (pac.getid() == p.getid()) {
                std::cout << "ID já cadastrado." << std::endl;
                return;
            }
        pacientes.push_back(p);
        std::cout << "Paciente " << p.getnome() << " cadastrado." << std::endl;
    }

    // Interna um paciente em um leito específico (1 paciente por leito)
    void internarPaciente(long int idPaciente, int numLeito) {
        if (numLeito < 1 || numLeito > static_cast<int>(leitos.size())) {
            std::cout << "Leito inválido." << std::endl;
            return;
        }
        Leito& l = leitos[numLeito - 1];
        if (l.ocupado) {
            std::cout << "Leito já ocupado." << std::endl;
            return;
        }
        for (const auto& p : pacientes) {
            if (p.getid() == idPaciente) {
                l.ocupar(p);
                std::cout << "Paciente " << p.getnome()
                          << " internado no leito " << numLeito << "." << std::endl;
                return;
            }
        }
        std::cout << "Paciente não encontrado." << std::endl;
    }

    // Libera um leito pelo número
    void liberarLeito(int numLeito) {
        if (numLeito < 1 || numLeito > static_cast<int>(leitos.size())) {
            std::cout << "Leito inválido." << std::endl;
            return;
        }
        Leito& l = leitos[numLeito - 1];
        if (!l.ocupado) {
            std::cout << "Leito já está disponível." << std::endl;
            return;
        }
        l.liberar();
        std::cout << "Leito " << numLeito << " liberado." << std::endl;
    }

    // Método usado pelo Médico para remover paciente do leito (dar alta)
    void removerPacienteDoLeito(long int idPaciente) {
        for (auto& l : leitos) {
            if (l.ocupado && l.id_paciente == idPaciente) {
                l.liberar();
                std::cout << "Paciente " << idPaciente << " recebeu alta e deixou o leito." << std::endl;
                return;
            }
        }
        std::cout << "Paciente não está internado." << std::endl;
    }

    // Lista de leitos (informações)
    void listarLeitos() const {
        std::cout << "\n=== Lista de Leitos ===\n";
        for (const auto& l : leitos) {
            std::cout << "Leito " << l.numero << " — "
                      << (l.ocupado ? "Ocupado (Paciente ID " + std::to_string(l.id_paciente) + ")" : "Disponível")
                      << std::endl;
        }
    }

    // Lista de pacientes (chama o display() de cada paciente)
    void listarPacientes() const {
        std::cout << "\n=== Pacientes Cadastrados ===\n";
        if (pacientes.empty()) {
            std::cout << "Nenhum paciente cadastrado." << std::endl;
            return;
        }
        for (const auto& p : pacientes) p.display();
    }

    // Relatório simples
    void relatorio() const {
        int ocupados = 0;
        for (const auto& l : leitos)
            if (l.ocupado) ++ocupados;
        std::cout << "\n--- Relatório ---\n";
        std::cout << "Total de leitos: " << leitos.size() << std::endl;
        std::cout << "Ocupados: " << ocupados << std::endl;
        std::cout << "Disponíveis: " << leitos.size() - ocupados << std::endl;
        std::cout << "Pacientes cadastrados: " << pacientes.size() << std::endl;
    }

    // Exporta estado atual (pacientes + leitos) para JSON simples
    void exportarJSON(const std::string& arquivo) const {
        std::ofstream f(arquivo);
        f << "{\n  \"pacientes\": [\n";
        for (size_t i = 0; i < pacientes.size(); ++i) {
            f << "    {\"id\": " << pacientes[i].getid()
              << ", \"nome\": \"" << pacientes[i].getnome()
              << "\", \"idade\": " << pacientes[i].getidade()
              << ", \"diagnostico\": \"" << pacientes[i].getdiagnostico()
              << "\"}" << (i + 1 < patients_count(pacientes) ? "," : "") << "\n";
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
        std::cout << "Dados exportados para " << arquivo << std::endl;
    }

    // Reset (volta ao estado inicial)
    void resetar() {
        leitos.clear();
        pacientes.clear();
        std::cout << "Hospital resetado." << std::endl;
    }

private:
    // serve para evitar warnings
    static size_t patients_count(const std::vector<Paciente>& v) { return v.size(); }
};

#endif
