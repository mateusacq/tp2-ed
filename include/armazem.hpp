//---------------------------------------------------------------------
// Arquivo      : armazem.hpp
// Conteudo     : header do TAD Armazém
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "pilha.hpp" // Para armazenamento "Hanoi"
#include "pacote.hpp"

#include <string>
#include <iostream> // Para leitura de dados
#include <fstream>

class Grafo; // Forward declaration, para friend class

class Armazem {
public:
    Armazem();
    Armazem(const Armazem& outro);
    Armazem(int id, int numPacotes, int numArmazens);
    Armazem& operator=(const Armazem& outro);
    ~Armazem();

    const int getId();
    const int getNumPacotes();

    void setId(int id);
    void setNumPacotes(int n);

    void armazenaPacote(Pacote &p);
    int recuperaPacote(int secao_id);
    bool secaoVazia(int secao_id);
    
private:
    Pilha * secoes;
    int numPacotes;
    int numArmazens;
    int id;

    friend class Grafo; // Para topologia
};

#endif