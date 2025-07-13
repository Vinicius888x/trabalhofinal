// cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

// Definição da classe Cliente
class Cliente {
public:
    // ID único do cliente, gerado automaticamente
    int id;
    // Nome completo do cliente
    std::string nome;
    // Número de telefone do cliente
    std::string telefone;

    // Construtor da classe Cliente
    // Inicializa um novo objeto Cliente com os dados fornecidos
    Cliente(const std::string& telefone, const std::string& nome);

private:
    // Variável estática para gerar IDs sequenciais para cada cliente
    static int nextId;
};

#endif // CLIENTE_H
