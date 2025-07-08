#include "simulador.hpp"

#include <iostream>
#include <fstream> // Para ler arquivos
#include <string>

int main(int argc, char* argv[]) {
    // Le arquivo de entrada
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo>\n";
        return 1;    
    }
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "ERRO: falha ao abrir o arquivo." << std::endl;
        return 1;
    }

    // Inicializa simulador de eventos
    Simulador simulador;
    
    // Recebe os dados do arquivo de entrada
    simulador.leArquivo(in);

    simulador.simulacao();

    return 0;
}