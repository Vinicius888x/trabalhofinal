// imovel.h
#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>

// Enumeração para os tipos de imóvel
enum class TipoImovel {
    Casa,
    Apartamento,
    Terreno
};

// Função para converter uma string para o enum TipoImovel
TipoImovel stringToTipoImovel(const std::string& tipoStr);

// Definição da classe Imovel
class Imovel {
public:
    // ID único do imóvel, gerado automaticamente
    int id;
    // Tipo do imóvel (Casa, Apartamento, Terreno)
    TipoImovel tipo;
    // ID do proprietário do imóvel (referencia um Cliente)
    int proprietarioId;
    // Latitude da localização do imóvel
    double lat;
    // Longitude da localização do imóvel
    double lng;
    // Preço do imóvel
    double preco;
    // Endereço completo do imóvel
    std::string endereco;

    // Construtor da classe Imovel
    // Inicializa um novo objeto Imovel com os dados fornecidos
    Imovel(TipoImovel tipo, int proprietarioId, double lat, double lng, double preco, const std::string& endereco);

private:
    // Variável estática para gerar IDs sequenciais para cada imóvel
    static int nextId;
};

#endif // IMOVEL_H