//---------------------------------------------------------------------
// Arquivo      : pilha.hpp
// Conteudo     : header da estrutura de dados pilha
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#ifndef PILHA_HPP
#define PILHA_HPP

#include <iostream> // Para mensagens de erro

using ChaveP = int;

class ItemP {
public:
    ItemP();
    ItemP(ChaveP c);
    
    void SetChave(ChaveP c);
    ChaveP GetChave();

private:
    ChaveP chave;

    friend class CelulaP;

};

class CelulaP {
public:
    CelulaP();

private:
    ItemP item;
    CelulaP * prox;

    friend class Pilha;
    friend class Grafo; // Para BFS
};

class Pilha {
public:
    Pilha();
    Pilha(Pilha& outra);
    Pilha& operator=(Pilha& outra);
    ~Pilha();

    void Empilha(ItemP item);
    ItemP Desempilha();
    
    void Limpa();
    bool Vazia();

    void Imprime() const;
    int getTamanho() const;

private:
    CelulaP * topo;
    int tamanho;

    friend class Grafo; // Para BFS()

};

#endif 