//---------------------------------------------------------------------
// Arquivo      : pacote.hpp
// Conteudo     : header do TAD Pacote
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <fstream>
#include <iostream>

#include "lista.hpp"

// Estados para a SED
enum EstadoPacote {
    NAO_POSTADO = 1, 
    CHEGOU_ARMAZEM,
    ARMAZENADO, 
    REMOVIDO, 
    EM_TRANSPORTE,
    ENTREGUE
};

class Pacote {
public:
    Pacote();
    Pacote(const Pacote& outro);
    Pacote(int tempoChegada, int id, int origem, int destino);
    Pacote& operator=(const Pacote& outro);
    ~Pacote();

    const int getId();
    const int getTempoChegada();
    const int getOrigem();
    const int getProxArmazem();
    const int getDestino();

    const int getTempoArmazenado();
    const int getTempoEmTransporte();
    const EstadoPacote getEstado();

    Lista * getRota();

    void setId(int id);
    void setTempoChegada(int novaDataHora);
    void setOrigem(int novaOrigem);
    void setDestino(int novoDestino);

    void setTempoArmazenado(int t);
    void setTempoEmTransporte(int t);
    void setEstado(EstadoPacote e);

    void setRota(Lista * rota);

private:
    int id;
    int tempoChegada;
    int origem;
    int destino;

    int tempoArmazenado;
    int tempoEmTransporte;
    EstadoPacote estado; 

    Lista * rota;
};

#endif