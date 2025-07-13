// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cmath> // Para M_PI e funções matemáticas

// Constante para o raio da Terra em km
constexpr double EARTH_R = 6371.0;

// Função para calcular a distância Haversine entre dois pontos geográficos
// lat1, lon1: Latitude e longitude do primeiro ponto
// lat2, lon2: Latitude e longitude do segundo ponto
// Retorna a distância em quilômetros
double haversine(double lat1, double lon1, double lat2, double lon2);

// Estrutura para representar uma entrada na agenda de um corretor
struct AgendaEntry {
    // Horário de início da avaliação em minutos desde 00:00
    int startTimeMinutes;
    // ID do imóvel a ser avaliado
    int imovelId;

    // Construtor para AgendaEntry
    AgendaEntry(int time, int id) : startTimeMinutes(time), imovelId(id) {}

    // Operador de comparação para ordenar AgendaEntry por startTimeMinutes
    bool operator<(const AgendaEntry& other) const {
        return startTimeMinutes < other.startTimeMinutes;
    }
};

// Função para formatar um tempo em minutos (desde 00:00) para o formato HH:MM
// minutes: O tempo total em minutos
// Retorna uma string no formato "HH:MM"
std::string formatTime(int minutes);

#endif // UTILS_H
