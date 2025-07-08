//---------------------------------------------------------------------
// Arquivo      : lista.cpp
// Conteudo     : implementação da lista
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#include "lista.hpp"

ItemL::ItemL() {
    chave = -1;
}

ItemL::ItemL(ChaveL c) {
    chave = c;
}

void ItemL::SetChave(ChaveL c) {
    chave = c;
}


ChaveL ItemL::GetChave() {
    return chave;
}

CelulaL::CelulaL() {
    item.SetChave(-1);
    prox = nullptr;
}

ItemL CelulaL::GetItem() {
    return item;
}


Lista::Lista() {
    primeiro = new CelulaL();
    ultimo = primeiro;
    tamanho = 0;
}

Lista::Lista(const Lista& outra) {
    primeiro = new CelulaL();
    ultimo = primeiro;
    tamanho = 0;

    CelulaL *p = outra.primeiro->prox;
    while (p != nullptr) {
        this->InsereFinal(p->item);
        p = p->prox;
    }
}

Lista& Lista::operator=(const Lista& outra) {
    if (this == &outra) {
        return *this;
    }

    Limpa();

    CelulaL *p = outra.primeiro->prox;
    while (p != nullptr) {
        this->InsereFinal(p->item);
        p = p->prox;
    }

    return *this;
}

Lista::~Lista() {
    Limpa();
    delete primeiro;
}

CelulaL* Lista::Posiciona(int pos) {
    // Seguranca contra seg fault
    if ( (pos > tamanho + 1) || (pos <= 0) ) {
        std::cerr << "ERRO: Posicao Invalida!";
        return nullptr;
    }
    
    CelulaL *p = primeiro->prox;
    for (int i = 1; i < pos; i++) {
        p = p->prox;
    }

    return p;
}

CelulaL* Lista::PosicionaAnterior(int pos) {
    // Seguranca contra seg fault
    if ( (pos > tamanho + 1) || (pos <= 0) ) {
        std::cerr << "ERRO: Posicao Invalida!";
        return nullptr;
    }
    
    CelulaL *p = primeiro;
    for (int i = 0; i < pos - 1; i++) {
        p = p->prox;
    }

    return p;
}

ItemL Lista::GetItem(int pos) {
    CelulaL *p;
    p = Posiciona(pos);

    if (p == nullptr) {
        // std::cerr << "ERRO: Tentativa de GetItem em posicao invalida.\n";
        return ItemL();
    }

    return p->item;
}

CelulaL* Lista::GetPrimeira() {
    if (Vazia()) {
        CelulaL * celula_erro = new CelulaL();
        return celula_erro;
    }
    return primeiro->prox;
}


void Lista::SetItem(ItemL item, int pos) {
    CelulaL *p;
    p = Posiciona(pos);

    if (p == nullptr) {
        std::cerr << "ERRO: Tentativa de SetItem em posicao invalida.\n";
        return;
    }

    p->item = item;
}

void Lista::InsereInicio(ItemL item) {
    CelulaL *nova = new CelulaL();
    nova->item = item;
    
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;

    // Verificacao para lista vazia
    if (ultimo == primeiro) {
        ultimo = nova;
    }
}

void Lista::InsereFinal(ItemL item) {
    CelulaL *nova = new CelulaL();
    nova->item = item;
    // O novo ultimo sempre aponta para nullptr
    nova->prox = nullptr;

    if (tamanho == 0) {
        primeiro->prox = nova;
    } else {
        ultimo->prox = nova;
    }
    ultimo = nova; // "nova" agora eh o ultimo elemento
    tamanho++;
}

void Lista::InserePosicao(ItemL item, int pos) {
    // Tratamento de casos especiais
    if (pos < 1 || pos > tamanho + 1) {
        std::cerr << "ERRO: Posicao de insercao '" << pos << "' invalida!\n";
        return;
    }
    if (pos == 1) {
        InsereInicio(item);
        return;
    }
    if (pos == tamanho + 1) {
        InsereFinal(item);
        return;
    }

    CelulaL *anterior, *nova = new CelulaL();
    nova->item = item;

    // Posiciona p na celula anterior a posicao onde havera insercao
    anterior = Posiciona(pos - 1);
    if (anterior == nullptr) { // Seguranca extra
        std::cerr << "ERRO Interno: Posiciona() retornou nullptr em InserePosicao()" << std::endl;
        delete nova;
        return;
    }

    nova->prox = anterior->prox;
    anterior->prox = nova;
    tamanho++;
}

ItemL Lista::RemoveInicio() {
    if (tamanho == 0) {
        std::cerr << "ERRO: Lista vazia! RemoveInicio\n";

        return ItemL();
    }

    CelulaL *removida = primeiro->prox;
    primeiro->prox = removida->prox;
    tamanho--;

    if (tamanho == 0) {
        ultimo = primeiro;
    }
    
    ItemL aux = removida->item;
    delete removida;

    return aux;
}

ItemL Lista::RemoveFinal() {
    if (tamanho == 0) {
        std::cerr << "ERRO: Lista vazia! RemoveFinal\n";
        
        return ItemL();
    }

    ItemL aux = ultimo->item;

    if (tamanho == 1) {
        delete ultimo;
        primeiro->prox = nullptr;
        ultimo = primeiro;
        tamanho = 0;
        return aux;
    }

    // Posiciona na celula anterior a ultima
    CelulaL *p = Posiciona(tamanho - 1);

    delete ultimo;
    p->prox = nullptr;
    ultimo = p;
    tamanho--;

    return aux;
}

ItemL Lista::RemovePosicao(int pos) {
    if (tamanho == 0) {
        std::cerr << "ERRO: Lista vazia! RemovePosicao\n";
        
        ItemL item_erro;
        return item_erro;
    }
    if (pos < 1 || pos > tamanho) {
        std::cerr << "ERRO: Posicao de remocao invalida!\n";
        return ItemL();
    }
    if (pos == 1) {
        return RemoveInicio();
    }
    if (pos == tamanho) {
        return RemoveFinal();
    }

    CelulaL *anterior = Posiciona(pos - 1);
    CelulaL *removida = anterior->prox;
    anterior->prox = removida->prox;
    
    tamanho--;
    ItemL aux = removida->item;
    delete removida;

    return aux;
}

// Pesquisa pela posicao de um item na lista
int Lista::Pesquisa(ChaveL c) {
    if (tamanho == 0) {
        // std::cerr << "ERRO: Lista vazia! Pesquisa\n";
        return -1;
    }
    
    int pos = 1;
    bool encontrou = false;
    CelulaL * p = primeiro->prox;
    while (p != nullptr) {
        if (p->item.GetChave() == c) {
            encontrou = true;
            break;
        }
        p = p->prox;
        pos++;
    }

    // Se nao encontrar nada, retorna -1, valor do construtor padrao de aux
    return encontrou ? pos : -1;
}

void Lista::Imprime() {
    // Informacao interna, utilidade para debug
    // std::cout << "LISTA: (tamanho = " << tamanho << "):\n";

    if (tamanho == 0) {
        std::cerr << "Vazia\n";
        return;
    } else {
        CelulaL * p = primeiro->prox;
        int pos = 1;

        while (p != nullptr) {
            std::cout 
            // << "pos " << pos 
            /* << " item " */ << p->item.GetChave()
            << " -> "; 

            p = p->prox;
            pos++;
        }

        std::cout << "NULL\n"; // Indica o fim da lista
    }

    // ##### Informações internas (para debug) #####
    // std::cout << "ITENS: "
    // << "primeiro: " << primeiro->item.GetChave()
    // << " ultimo: " << ultimo->item.GetChave() 
    // << std::endl;
    
    // std::cout << "  primeiro (sentinela): " << primeiro << " -> " << primeiro->prox << std::endl;
    // std::cout << "  ultimo: " << ultimo << " -> " << ultimo->prox << std::endl;
    // std::cout << "  Item da sentinela: " << primeiro->item.GetChave() << std::endl;
    // std::cout << "  Item do ultimo: " << ultimo->item.GetChave() << std::endl;
}

void Lista::Limpa() {
    CelulaL *p;


    p = primeiro->prox;
    while ( p!= nullptr) {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro ->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
}

bool Lista::Vazia() {
    return tamanho == 0;
}