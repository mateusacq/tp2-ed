//---------------------------------------------------------------------
// Arquivo      : grafo.hpp
// Conteudo     : header da estrutura de dados grafo
// Autor        : Mateus Antinossi Cordeiro Queiroz (mateusacq@ufmg.br)
// Historico    : 2025-07-01 - arquivo criado
//---------------------------------------------------------------------

#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "lista.hpp"
#include "fila.hpp" // Para Grafo::BFS()
#include "pilha.hpp" // Para exibir rotas entre armazens
#include "armazem.hpp" // Para TipoV (tipo do vertice)

#include <string>
#include <fstream> // Para Grafo::leGrafo()
#include <iostream>

typedef struct vertice { // Para algoritmo BFS
    int dist;
    int antecessor;
    char cor; // b = branco, c = cinza, p = preto
} vertice_bfs_s;

using TipoV = Armazem;

class Grafo {
public:
    Grafo(int n);
    Grafo(const Grafo& outro);
    Grafo& operator=(const Grafo& outro);
    ~Grafo();

    void adicionaAresta(TipoV v, TipoV u);
    void removeAresta(TipoV v, TipoV u);
    Lista getAdj(TipoV v);

    void leGrafo(std::ifstream &in, bool ** matriz);
    
    bool grafoVazio();
    void Imprime() const;

    Lista * bfs(TipoV v, TipoV u);

private:
    int numVertices;
    int numArestas;

    Lista * adj;

    // Metodos internos
    bool existeAresta(TipoV v, TipoV u) const;
    bool validaVertice(TipoV v) const;

    Lista * getRota(TipoV v, TipoV u, vertice * vertices);
};

#endif