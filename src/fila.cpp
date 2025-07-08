//---------------------------------------------------------------------
// Arquivo      : fila.cpp
// Conteudo     : implementação da estrutura de dados Fila
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#include "fila.hpp"

TipoItem::TipoItem() {
    chave = -1;
}

TipoItem::TipoItem(TipoChave c) {
    chave = c;
}

void TipoItem::SetChave(TipoChave c) {
    chave = c;
}


TipoChave TipoItem::GetChave() {
    return chave;
}

TipoCelula::TipoCelula() {
    item.SetChave(-1);
    prox = nullptr;
}


Fila::Fila() {
    frente = new TipoCelula();
    tras = frente;
    tamanho = 0;
}

Fila::Fila(const Fila& outra) {
    frente = new TipoCelula();
    tras = frente;
    tamanho = 0;

    TipoCelula* p = outra.frente->prox;
    while (p != nullptr) {
        this->Enfileira(p->item);
        p = p->prox;
    }
}

Fila& Fila::operator=(const Fila& outra) {
    // Protecao contra autoatribuicao
    if (&outra == this) {
        return *this;
    }
    
    // Previne vazamento de memoria para o caso 
    // do objeto a esquerda possuir algum dado
    Limpa(); 

    TipoCelula* p = outra.frente->prox;
    while (p != nullptr) {
        this->Enfileira(p->item);
        p = p->prox;
    }

    return *this;
}

Fila::~Fila() {
    Limpa();
    delete frente;
}

void Fila::Enfileira(TipoItem item) {
    TipoCelula *nova = new TipoCelula();
    nova->item = item;
    nova->prox = nullptr; // O novo no deve sempre apontar para NULL, pois eh o ultimo

    tras->prox = nova;
    tras = nova;

    tamanho++;
}

TipoItem Fila::Desenfileira() {
    TipoCelula *removida = frente->prox;
    TipoItem aux;

    if (tamanho == 0) {
        std::cerr << "Fila esta vazia!\n";
        aux.SetChave(-1);
        return aux;
    }

    aux = frente->prox->item;
    frente->prox = removida->prox;

    if (frente->prox == nullptr) {
        tras = frente; // Caso em que a lista ficou vazia e so restou a sentinela
    }

    delete removida;
    tamanho--;
    return aux;
}

void Fila::Limpa() {
    TipoCelula *p = frente->prox;

    while (p != nullptr) {
        TipoCelula * temp = p->prox;
        delete p;
        p = temp;
    }

    frente->prox = nullptr;
    tamanho = 0;
    tras = frente;
}

bool Fila::Vazia() {
    return tamanho == 0;
}

void Fila::Imprime() const {
    std::cout << "FILA (tamanho: " << tamanho << "): ";
    if (tamanho == 0) {
        std::cout << " Vazia\n";
    } else {
        TipoCelula * p = frente->prox;
        while (p != nullptr) {
            std::cout << p->item.GetChave() << " ";
            p = p->prox;
        }
        std::cout << std::endl;
    }
    // Utilidades para debug:
    // std::cout << "Frente (sentinela): endereco " << frente << ", valor: " << frente->item.GetChave() << ", prox: " << frente->prox << std::endl;
    // std::cout << "Tras (sentinela): endereco " << tras << ", valor: " << tras->item.GetChave() << ", prox: " << tras->prox << std::endl;
}