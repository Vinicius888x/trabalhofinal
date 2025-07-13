// cliente.cpp
#include "cliente.h"

// Inicialização da variável estática nextId
// Começa em 1 para gerar IDs sequenciais a partir de 1
int Cliente::nextId = 1;

// Implementação do construtor da classe Cliente
Cliente::Cliente(const std::string& telefone, const std::string& nome)
    : id(nextId++), nome(nome), telefone(telefone) {
    // O corpo do construtor está vazio pois todos os membros são inicializados na lista de inicialização
}
