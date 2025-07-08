//---------------------------------------------------------------------
// Arquivo      : grafo.cpp
// Conteudo     : implementação de grafo
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#include "grafo.hpp"

#define INFINITY __INT_MAX__


Grafo::Grafo(int n) {
    numVertices = n;
    numArestas = 0;
    adj = new Lista[n];
}

Grafo::Grafo(const Grafo& outro) 
: numVertices(outro.numVertices), numArestas(outro.numArestas)
{
    adj = new Lista[numVertices];

    for (int i = 0; i < numVertices; i++) {
        adj[i] = outro.adj[i];
    }
}

Grafo& Grafo::operator=(const Grafo& outro) {
    if (this == &outro) {
        return *this;
    }

    if (adj != nullptr) {
        delete[] adj;
    }

    numVertices = outro.numVertices;
    numArestas = outro.numArestas;
    
    if (numVertices > 0) {
        adj = new Lista[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adj[i] = outro.adj[i];
        }
    } else {
        adj = nullptr;
    }
    
    return *this;
}

Grafo::~Grafo() {
    delete[] adj;
}

bool Grafo::validaVertice(TipoV v) const {
    return v.id >= 0 && v.id < numVertices;
}

bool Grafo::existeAresta(TipoV v, TipoV u) const {
    if ( !validaVertice(v) || !validaVertice(u) ) {
        return false;
    }
 
    return adj[v.id].Pesquisa(u.id) != -1;
}

Lista Grafo::getAdj(TipoV v) {
    return adj[v.id];
}

void Grafo::adicionaAresta(TipoV v, TipoV u) {
    if ( validaVertice(v) && validaVertice(u) ) {
        if ( !existeAresta(v, u) ){ // Evita arestas multiplas
            int v_id = v.id;
            int u_id = u.id;
            
            adj[v_id].InsereFinal(u_id);
            adj[u_id].InsereFinal(v_id);

            numArestas++;
        } else {
            std::cerr << "AVISO: Aresta (" 
            << v.id << ", " << u.id << ")"
            << "ja existe.\n";
        }
    } else {
        std::cerr << "ERRO: vertice(s) invalido(s) ao adicionar aresta.\n";
    }
}

void Grafo::removeAresta(TipoV v, TipoV u) {
    if ( !validaVertice(v) || !validaVertice(u) ) {
        std::cerr << "ERRO: vertice(s) invalido(s) ao remover aresta.\n";
        return;
    }
    if ( existeAresta(v, u) ) {
        int v_pos = adj[u.id].Pesquisa(v.id);
        int u_pos = adj[v.id].Pesquisa(u.id);
        
        if ( v_pos != -1 && u_pos != -1 ) {
            adj[u.id].RemovePosicao(v_pos);
            adj[v.id].RemovePosicao(u_pos);

            numArestas--;
        } else 
            std::cerr << "ERRO INTERNO: vertices nao localizaos na adjacencia\n";
    } else 
        std::cerr << "ERRO: aresta nao encontrada!\n";
}

// Leitura do grafo a partir de matriz de adjacencia
void Grafo::leGrafo(std::ifstream &in, bool ** matrizAdjAux) {
    bool b;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            b = matrizAdjAux[i][j];
            if (b) {
                Armazem u, v;
                u.setId(i);
                v.setId(j);
                if (!existeAresta(u, v)) {
                    adicionaAresta(u, v);
                }

            }
        }
    }
}

bool Grafo::grafoVazio() {
    bool vazio = true;

    for (int i = 0; i < numVertices; i++) {
        if (!adj[i].Vazia()) {
            vazio = false;
        }
    }

    return vazio;
}

void Grafo::Imprime() const {
    std::cout << "GRAFO:\n"
    << "(numVertices = " << numVertices << ")\n"
    << "(numArestas = " << numArestas << ")\n";

    for (int i = 0; i < numVertices; i++) {
        std::cout << i << ": ";
        adj[i].Imprime();
    }
}

Lista * Grafo::bfs(TipoV v, TipoV u) {
    if ( !validaVertice(v) || !validaVertice(u) ) {
        std::cerr << "ERRO: vertices invalidos para BFS.\n";
        return new Lista();
    } else {
        // Inicializa vetores 
        vertice * vertices = new vertice[numVertices];
        Fila fila;

        for (int i = 0; i < numVertices; i ++) {
            vertices[i].cor = 'b';
            vertices[i].dist = INFINITY;
            vertices[i].antecessor = -1;
        }

        // Visita vertice de origem
        vertices[v.id].cor = 'c';
        vertices[v.id].dist = 0;
        fila.Enfileira(v.id);

        while ( !fila.Vazia() ) {
            int atual = fila.Desenfileira().GetChave();

            // Exibe rota se a visitação chegou ao vertice de destino
            if (atual == u.id) {
                // std::cout << "Rota encontrada entre armazens " 
                // << v.id << " e " << u.id << ":\n";
                Lista * Rota = getRota(v, u, vertices);

                delete[] vertices;
                return Rota;
            }

            // Visita vizinhos do vertice atual
            CelulaL* vizinhoAtual = adj[atual].GetPrimeira();
            while (vizinhoAtual != nullptr) {
                int vizinhoAtualID = vizinhoAtual->item.GetChave();

                if (vertices[vizinhoAtualID].cor == 'b') {
                    vertices[vizinhoAtualID].cor = 'c';
                    vertices[vizinhoAtualID].dist = vertices[atual].dist + 1;
                    vertices[vizinhoAtualID].antecessor = atual;

                    fila.Enfileira(vizinhoAtualID);
                }
                vizinhoAtual = vizinhoAtual->prox;
            }
            vertices[atual].cor = 'p';
        }
        delete[] vertices;
        
        std::cout << "Não existe rota entre " << v.id << " e " << u.id << ".\n";
        return new Lista();
    }
}

Lista * Grafo::getRota(TipoV v, TipoV u, vertice * vertices) {
    Pilha rota;
    int atual = u.id;
    // int distancia = vertices[u.id].dist;

    // Constroi a rota (caminho otimo do destino para a origem reconstruido)
    while ( atual != -1 ) {
        rota.Empilha(atual);
        atual = vertices[atual].antecessor;
    }

    if (rota.Vazia() || rota.topo->item.GetChave() != v.id) {
        std::cerr << "ERRO INTERNO: Falha na reconstrução do caminho BFS.\n";
        return new Lista();
    }

    Lista * lista_rota = new Lista();
    while ( !rota.Vazia() ) {
        ItemL item(rota.Desempilha().GetChave());
        lista_rota->InsereFinal(item);
        // std::cout << item.GetChave() << " -> ";
    }
    // std::cout << std::endl;

    return lista_rota;
}