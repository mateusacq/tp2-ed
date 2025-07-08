//---------------------------------------------------------------------
// Arquivo      : pilha.cpp
// Conteudo     : implementação da estrutura de dados pilha
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#include "pilha.hpp"

ItemP::ItemP() {
    chave = -1;
}

ItemP::ItemP(ChaveP c) {
    chave = c;
}

void ItemP::SetChave(ChaveP c) {
    chave = c;
}

ChaveP ItemP::GetChave() {
    return chave;
}

CelulaP::CelulaP() {
    item.SetChave(-1);
    prox = nullptr;
}

Pilha::Pilha() {
    topo = nullptr;
    tamanho = 0;
}

Pilha::Pilha(Pilha& outra) {
    topo = nullptr;
    tamanho = 0;

    if (outra.Vazia()) {
        return;
    }

    // Pilha temporaria que tera os elementos desempilhados
    // (logo, na ordem inversa, do topo para baixo)
    Pilha tempPilhaInversa; 
    CelulaP *p = outra.topo;

    while (p != nullptr) {
        tempPilhaInversa.Empilha(p->item);
        p = p->prox;
    }

    while (!tempPilhaInversa.Vazia()) {
        this->Empilha( tempPilhaInversa.Desempilha() );
    }
}

Pilha& Pilha::operator=(Pilha& outra) {
    // Protecao contra autoatribuicao
    if (&outra == this) {
        return *this;
    }

    Limpa();

    if (outra.Vazia()) {
        return *this;
    }

    Pilha tempPilhaInversa;
    CelulaP * p = outra.topo;

    while (p != nullptr) {
        tempPilhaInversa.Empilha(p->item);
        p = p->prox;
    }

    while (!tempPilhaInversa.Vazia()) {
        this->Empilha( tempPilhaInversa.Desempilha() );
    }

    return *this;
}

Pilha::~Pilha() {
    Limpa();
}

void Pilha::Empilha(ItemP item) {
    CelulaP * nova = new CelulaP();
    nova->item = item;

    nova->prox = topo;
    topo = nova;
    tamanho++;
}

ItemP Pilha::Desempilha() {
    ItemP aux;

    if (tamanho == 0) {
        std::cerr << "Pilha esta vazia!\n";
        aux.SetChave(-1);
        return aux;    
    }

    aux = topo->item;

    CelulaP * removida;
    removida = topo;
    topo = topo->prox;
    delete removida;
    tamanho--;

    return aux;
}

void Pilha::Limpa() {
    while (!Vazia()) {
        Desempilha();
    }
}

bool Pilha::Vazia() {
    return tamanho ==0;
}

void Pilha::Imprime() const {
    std::cout << "PILHA (tamanho: " << tamanho << "): ";
    if (tamanho == 0) {
        std::cout << "Vazia\n";
    } else {
        CelulaP * p = topo;
        while (p != nullptr) {
            std::cout << p->item.GetChave() << " -> ";
            p = p->prox;
        }
        std::cout << "NULL" <<  " (topo para base)\n"; // Indica o fim da pilha
    }

    // Utilidades para debug:
   
    if (topo != nullptr) {
        std::cout << "Topo: endereco " << topo << ", valor: " << topo->item.GetChave() << ", prox: " << topo->prox << std::endl;
    } else {
        std::cout << "Topo: nullptr\n";
    }
}

int Pilha::getTamanho() const {
    return this->tamanho;
}