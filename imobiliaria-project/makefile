# Makefile para o projeto Imobiliária

# Compilador C++
CXX = g++

# Flags de compilação:
# -std=c++11: Usa o padrão C++11
# -Wall: Habilita todos os warnings
# -Wextra: Habilita warnings extras
# -pedantic: Exige conformidade estrita com o padrão C++
# -O2: Otimização de nível 2
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O2

# Arquivos fonte (.cpp) do projeto
SRCS = main.cpp corretor.cpp cliente.cpp imovel.cpp utils.cpp

# Nome do executável final
TARGET = imobiliaria

# Regra principal para construir o executável
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regra para limpar os arquivos gerados pela compilação
clean:
	rm -f $(TARGET)
