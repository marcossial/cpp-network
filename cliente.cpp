#include <winsock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in servidor;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cerr << "Erro ao inicializar Winsock.\n";
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Erro ao criar socket.\n";
        WSACleanup();
        return 1;
    }
    
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(54000);

    if (connect(sock, (struct sockaddr*)&servidor, sizeof(servidor)) == SOCKET_ERROR) {
        std::cerr << "Erro ao conectar ao servidor.\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Conectado ao servidor!\n";

    // Envia a mensagem
    const char* msg = "Olá, servidor!";
    send(sock, msg, strlen(msg), 0);
    
    // Recebe a resposta
    char buffer[512];
    int bytesRecebidos = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesRecebidos > 0) {
        buffer[bytesRecebidos] = '\0';
        std::cout << "Servidor respondeu: " << buffer << "\n";
    }
    
    closesocket(sock);
    WSACleanup();
    return 0;
}