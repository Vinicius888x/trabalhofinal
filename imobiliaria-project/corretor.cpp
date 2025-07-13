// corretor.cpp
#include "corretor.h"

// Inicialização da variável estática nextId
// Começa em 1 para gerar IDs sequenciais a partir de 1
int Corretor::nextId = 1;

// Implementação do construtor da classe Corretor
Corretor::Corretor(const std::string& telefone, bool avaliador, double lat, double lng, const std::string& nome)
    : id(nextId++), nome(nome), telefone(telefone), avaliador(avaliador), lat(lat), lng(lng) {
    // O corpo do construtor está vazio pois todos os membros são inicializados na lista de inicialização
}
