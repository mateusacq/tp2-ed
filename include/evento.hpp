//---------------------------------------------------------------------
// Arquivo      : evento.hpp
// Conteudo     : header do TAD Evento
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <iostream>

class Evento {
public:
    Evento();
    Evento(int _tempo, int _tipo, 
        int origem_id, int destino_id, 
        int _idPacote);

    std::string chave;
    int tempo;
    int idPacote;

    int tipo; // 1 = pacote, 2 = transporte

    int origem_id;
    int destino_id;

    bool operator<(const Evento& outro) const;

private:
    void gera_chave();
};

#endif