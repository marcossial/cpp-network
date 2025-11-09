#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET servidor, cliente;
    struct sockaddr_in servidor_addr, cliente_addr;
    int cliente_len = sizeof(cliente_addr);

    // Inicializa a DLL do Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cerr << "Erro ao inicializar Winsock.\n";
        return 1;
    }

    // Cria o socket TCP
    servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor == INVALID_SOCKET) {
        std::cerr << "Erro ao criar o socket.\n";
        WSACleanup();
        return 1;
    }

    servidor_addr.sin_family = AF_INET;
    servidor_addr.sin_addr.s_addr = INADDR_ANY;
    servidor_addr.sin_port = htons(54000); // porta arbitrária

    if (bind(servidor, (struct sockaddr*)&servidor_addr, sizeof(servidor_addr)) == SOCKET_ERROR) {
        std::cerr << "Erro em bind().\n";
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    listen(servidor, 1);
    std::cout << "Servidor aguardando conexões na porta 54000...\n";

    // Aceita um cliente
    cliente = accept(servidor, (struct sockaddr*)&cliente_addr, &cliente_len);
    if (cliente == INVALID_SOCKET) {
        std::cerr << "Erro em accept().\n";
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    std::cout << "Cliente conectado!\n";

    char buffer[512];
    int bytesRecebidos = recv(cliente, buffer, sizeof(buffer), 0);
    if (bytesRecebidos > 0) {
        buffer[bytesRecebidos] = '\0';
        std::cout << "Mensagem recebida: " << buffer << "\n";
        send(cliente, "Mensagem recebida com sucesso!", 30, 0);
    }

    closesocket(cliente);
    closesocket(servidor);
    WSACleanup();
    return 0;
}