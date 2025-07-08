//---------------------------------------------------------------------
// Arquivo      : lista.hpp
// Conteudo     : header da estrutura de dados Lista
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream> // Para mensagens de erro

// tipo das chaves da lista (ChaveL)
using ChaveL = int;

// classe dos itens da lista (ItemL)
class ItemL {
public: 
    ItemL();
    ItemL(ChaveL c);
    void SetChave(ChaveL c);
    ChaveL GetChave();

private:
    ChaveL chave;
    friend class CelulaL;
};

class CelulaL {
public:
    CelulaL();
    ItemL GetItem();

private:
    ItemL item;
    CelulaL * prox;

    friend class Lista;
    friend class Grafo; // Para BFS()
};

class Lista {
public:
    Lista();
    Lista(const Lista& outra); // Construtor de copia
    Lista& operator=(const Lista& outra);
    ~Lista();

    ItemL GetItem(int pos);
    CelulaL* GetPrimeira();
    void SetItem(ItemL, int pos);
    
    void InsereInicio(ItemL item);
    void InsereFinal(ItemL item);
    void InserePosicao(ItemL item, int pos);

    ItemL RemoveInicio();
    ItemL RemoveFinal();
    ItemL RemovePosicao(int pos);

    int Pesquisa(ChaveL c);
    void Imprime();
    void Limpa();
    bool Vazia();

private:
    CelulaL * primeiro;
    CelulaL * ultimo;
    CelulaL * Posiciona(int pos);
    CelulaL * PosicionaAnterior(int pos);

    int tamanho;
};

#endif