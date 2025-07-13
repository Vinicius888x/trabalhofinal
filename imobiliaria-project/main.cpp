// main.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::sort
#include <map>       // Para std::map
#include <limits>    // Para std::numeric_limits
#include <iomanip>   // Para std::setfill, std::setw

#include "corretor.h"
#include "cliente.h"
#include "imovel.h"
#include "utils.h"

// Função principal do programa
int main() {
    // Desabilita a sincronização de C++ streams com C stdio para otimizar I/O
    std::ios_base::sync_with_stdio(false);
    // Desvincula cin de cout para evitar flush automático e melhorar performance
    std::cin.tie(NULL);

    // --- Leitura dos Corretores ---
    int numCorretores;
    std::cin >> numCorretores;
    std::vector<Corretor> corretores;
    std::vector<Corretor> avaliadores; // Vetor para armazenar apenas os corretores avaliadores
    for (int i = 0; i < numCorretores; ++i) {
        std::string telefone;
        int avaliadorInt; // 1 para sim, 0 para não
        double lat, lng;
        std::string nome;

        std::cin >> telefone >> avaliadorInt >> lat >> lng;
        // Lê o restante da linha para o nome, descartando espaços em branco iniciais
        std::getline(std::cin >> std::ws, nome);

        Corretor c(telefone, (avaliadorInt == 1), lat, lng, nome);
        corretores.push_back(c);
        if (c.avaliador) {
            avaliadores.push_back(c);
        }
    }

    // --- Leitura dos Clientes ---
    int numClientes;
    std::cin >> numClientes;
    std::vector<Cliente> clientes;
    for (int i = 0; i < numClientes; ++i) {
        std::string telefone;
        std::string nome;

        std::cin >> telefone;
        std::getline(std::cin >> std::ws, nome);

        clientes.emplace_back(telefone, nome);
    }

    // --- Leitura dos Imóveis ---
    int numImoveis;
    std::cin >> numImoveis;
    std::vector<Imovel> imoveis;
    for (int i = 0; i < numImoveis; ++i) {
        std::string tipoStr;
        int propId;
        double lat, lng, preco;
        std::string endereco;

        std::cin >> tipoStr >> propId >> lat >> lng >> preco;
        std::getline(std::cin >> std::ws, endereco);

        imoveis.emplace_back(stringToTipoImovel(tipoStr), propId, lat, lng, preco, endereco);
    }

    // Se não houver corretores avaliadores ou imóveis, não há agendamento a fazer
    if (avaliadores.empty() || imoveis.empty()) {
        return 0;
    }

    // --- Passo 1: Distribuir Imóveis (Round-Robin) ---
    // Ordena a lista de imóveis por ID (já estão ordenados se lidos sequencialmente, mas garante)
    std::sort(imoveis.begin(), imoveis.end(), [](const Imovel& a, const Imovel& b) {
        return a.id < b.id;
    });

    // Mapa para armazenar os imóveis atribuídos a cada corretor avaliador
    // A chave é o ID do corretor, o valor é um vetor de imóveis atribuídos
    std::map<int, std::vector<Imovel>> imoveisPorAvaliador;
    for (const auto& avaliador : avaliadores) {
        imoveisPorAvaliador[avaliador.id] = std::vector<Imovel>();
    }

    // Distribui os imóveis aos avaliadores em sequência (Round-Robin)
    for (size_t i = 0; i < imoveis.size(); ++i) {
        int avaliadorIndex = i % avaliadores.size();
        imoveisPorAvaliador[avaliadores[avaliadorIndex].id].push_back(imoveis[i]);
    }

    // Mapa para armazenar a agenda final de cada corretor
    // A chave é o ID do corretor, o valor é um vetor de AgendaEntry
    std::map<int, std::vector<AgendaEntry>> agendaFinal;

    // --- Passo 2: Ordenar a Rota (Vizinho Mais Próximo) ---
    bool firstCorretorPrinted = true; // Flag para controlar a linha em branco entre corretores

    for (const auto& avaliador : avaliadores) {
        // Obtém a lista de imóveis atribuídos ao avaliador atual
        std::vector<Imovel>& imoveisDoAvaliador = imoveisPorAvaliador[avaliador.id];

        // Se o avaliador não tiver imóveis atribuídos, pula para o próximo
        if (imoveisDoAvaliador.empty()) {
            continue;
        }

        // Inicializa o tempo atual para 09:00 (em minutos desde 00:00)
        int currentTimeMinutes = 9 * 60; // 540 minutos
        // Localização atual do corretor (inicialmente, a localização do próprio corretor)
        double currentLat = avaliador.lat;
        double currentLng = avaliador.lng;

        // Vetor para armazenar a agenda deste corretor antes de imprimir
        std::vector<AgendaEntry> corretorAgenda;

        // Vetor para controlar quais imóveis já foram visitados por este corretor
        std::vector<bool> visited(imoveisDoAvaliador.size(), false);
        int visitedCount = 0;

        // Loop enquanto houver imóveis não visitados para este corretor
        while (visitedCount < imoveisDoAvaliador.size()) {
            double minDistance = std::numeric_limits<double>::max(); // Inicializa com valor máximo
            int nearestImovelIndex = -1;

            // Encontra o imóvel não visitado mais próximo do ponto atual
            for (size_t i = 0; i < imoveisDoAvaliador.size(); ++i) {
                if (!visited[i]) {
                    double dist = haversine(currentLat, currentLng, imoveisDoAvaliador[i].lat, imoveisDoAvaliador[i].lng);
                    if (dist < minDistance) {
                        minDistance = dist;
                        nearestImovelIndex = i;
                    }
                }
            }

            // Se nenhum imóvel próximo foi encontrado (erro ou todos visitados)
            if (nearestImovelIndex == -1) {
                break; // Sai do loop
            }

            // Marca o imóvel como visitado
            visited[nearestImovelIndex] = true;
            visitedCount++;

            // Imóvel mais próximo
            const Imovel& proximoImovel = imoveisDoAvaliador[nearestImovelIndex];

            // Calcula o tempo de deslocamento (2 minutos por km)
            int travelTimeMinutes = static_cast<int>(std::round(minDistance * 2));

            // Adiciona o tempo de deslocamento ao relógio
            currentTimeMinutes += travelTimeMinutes;

            // Adiciona a visita à agenda do corretor
            corretorAgenda.emplace_back(currentTimeMinutes, proximoImovel.id);

            // Adiciona 60 minutos (duração da avaliação) ao relógio para a próxima partida
            currentTimeMinutes += 60;

            // Atualiza a localização atual para a localização do imóvel recém-visitado
            currentLat = proximoImovel.lat;
            currentLng = proximoImovel.lng;
        }
        // Adiciona a agenda do corretor ao mapa final
        agendaFinal[avaliador.id] = corretorAgenda;
    }

    // --- Impressão da Saída Padrão ---
    firstCorretorPrinted = true; // Reinicia a flag para a impressão

    // Itera sobre os corretores avaliadores (garante a ordem dos corretores)
    for (const auto& avaliador : avaliadores) {
        // Verifica se este corretor tem agendamentos
        if (agendaFinal.count(avaliador.id) && !agendaFinal[avaliador.id].empty()) {
            // Se não for o primeiro corretor a ser impresso, adiciona uma linha em branco
            if (!firstCorretorPrinted) {
                std::cout << std::endl;
            }
            firstCorretorPrinted = false;

            // Imprime o cabeçalho do corretor
            std::cout << "Corretor " << avaliador.id << std::endl;

            // Ordena os agendamentos deste corretor por horário
            std::sort(agendaFinal[avaliador.id].begin(), agendaFinal[avaliador.id].end());

            // Imprime cada agendamento
            for (const auto& entry : agendaFinal[avaliador.id]) {
                std::cout << formatTime(entry.startTimeMinutes) << " Imóvel " << entry.imovelId << std::endl;
            }
        }
    }

    return 0;
}
