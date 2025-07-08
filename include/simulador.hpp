//---------------------------------------------------------------------
// Arquivo      : simulador.hpp
// Conteudo     : header do TAD Simulador
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include <fstream>
#include <iomanip> // Para imprimir saidas

#include "grafo.hpp" // Para topologia de armazens
#include "heap.hpp" // Escalonador
#include "pilha.hpp" // Para rearmazenamento Hanoi

#include "armazem.hpp"
#include "pacote.hpp"
#include "evento.hpp"

class Simulador 
{
public:
    Simulador();
    ~Simulador();
    void leArquivo(std::ifstream& in);
    
    void simulacao();

    Armazem * armazens;
    Pacote * pacotes;

    Grafo * Topologia;
    Heap * Escalonador;

    bool ** matrizAdjAux;

private:
    // Variaveis que dizem respeito aos armazens
    int numArmazens;

    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransporte;

    // Variaveis que dizem respeito aos pacotes
    int numPacotes;
    int numPacotesEntregues;
    int custoRemocao;

    int relogio;
    void AvancaRelogio(int tempo);
    void setRelogio(int tempo);
};

#endif