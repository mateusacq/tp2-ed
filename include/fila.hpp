//---------------------------------------------------------------------
// Arquivo      : fila.hpp
// Conteudo     : header da estrutura de dados Fila
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#ifndef FILA_H
#define FILA_H

#include <iostream> // Para mensagens de erro

using TipoChave = int;

class TipoItem  {
public:
    TipoItem();
    TipoItem(TipoChave c);
    void SetChave(TipoChave c);
    TipoChave GetChave();
    
private:
    TipoChave chave;

    friend class TipoCelula;
};

class TipoCelula {
public:
    TipoCelula();

private:
    TipoItem item;
    TipoCelula * prox;

    friend class Fila;
};

class Fila {
public:
    Fila();
    Fila(const Fila& outra); // Construtor de copia
    Fila& operator=(const Fila& outra);
    ~Fila();

    void Enfileira(TipoItem item);
    TipoItem Desenfileira();

    void Imprime() const;

    void Limpa();
    bool Vazia();

private:
    TipoCelula* frente;
    TipoCelula* tras;

    int tamanho;
};

#endif