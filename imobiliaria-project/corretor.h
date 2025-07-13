// corretor.h
#ifndef CORRETOR_H
#define CORRETOR_H

#include <string>

// Definição da classe Corretor
class Corretor {
public:
    // ID único do corretor, gerado automaticamente
    int id;
    // Nome completo do corretor
    std::string nome;
    // Número de telefone do corretor
    std::string telefone;
    // Indica se o corretor é um avaliador (true) ou não (false)
    bool avaliador;
    // Latitude da localização inicial do corretor
    double lat;
    // Longitude da localização inicial do corretor
    double lng;

    // Construtor da classe Corretor
    // Inicializa um novo objeto Corretor com os dados fornecidos
    Corretor(const std::string& telefone, bool avaliador, double lat, double lng, const std::string& nome);

private:
    // Variável estática para gerar IDs sequenciais para cada corretor
    static int nextId;
};

#endif // CORRETOR_H
