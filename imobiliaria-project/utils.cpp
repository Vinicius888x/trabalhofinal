// utils.cpp
#include "utils.h"
#include <iomanip> // Para std::setfill e std::setw
#include <sstream> // Para std::stringstream

// Implementação da função Haversine
double haversine(double lat1, double lon1, double lat2, double lon2) {
    // Lambda para converter graus para radianos
    auto deg2rad = [](double d){ return d * M_PI / 180.0; };

    // Diferença de latitudes e longitudes em radianos
    double dlat = deg2rad(lat2 - lat1);
    double dlon = deg2rad(lon2 - lon1);

    // Fórmula Haversine
    double a = std::pow(std::sin(dlat/2), 2) +
               std::cos(deg2rad(lat1)) * std::cos(deg2rad(lat2)) *
               std::pow(std::sin(dlon/2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return EARTH_R * c; // Distância em km
}

// Implementação da função formatTime
std::string formatTime(int minutes) {
    // Calcula as horas e minutos
    int hours = minutes / 60;
    int mins = minutes % 60;

    // Usa stringstream para formatar a saída com zeros à esquerda
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setfill('0') << std::setw(2) << mins;
    return ss.str();
}
