// imovel.cpp
#include "imovel.h"
#include <stdexcept> // Para std::runtime_error

// Inicialização da variável estática nextId
// Começa em 1 para gerar IDs sequenciais a partir de 1
int Imovel::nextId = 1;

// Implementação da função para converter string para TipoImovel
TipoImovel stringToTipoImovel(const std::string& tipoStr) {
    if (tipoStr == "Casa") {
        return TipoImovel::Casa;
    } else if (tipoStr == "Apartamento") {
        return TipoImovel::Apartamento;
    } else if (tipoStr == "Terreno") {
        return TipoImovel::Terreno;
    } else {
        // Lança uma exceção se o tipo de imóvel for inválido
        throw std::runtime_error("Tipo de imóvel inválido: " + tipoStr);
    }
}

// Implementação do construtor da classe Imovel
Imovel::Imovel(TipoImovel tipo, int proprietarioId, double lat, double lng, double preco, const std::string& endereco)
    : id(nextId++), tipo(tipo), proprietarioId(proprietarioId), lat(lat), lng(lng), preco(preco), endereco(endereco) {
    // O corpo do construtor está vazio pois todos os membros são inicializados na lista de inicialização
}
