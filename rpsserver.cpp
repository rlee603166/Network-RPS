
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include "player.h"
#include "game.h"

std::string handshake(int& client_socket, Player& player);
void sendServerMove(int& socket, Player& player);
int getClientMove(int& socket);
std::string determineWinner(const std::string& player1, 
                            const int& player1Move, 
                            const std::string& player2, 
                            const int& player2Move); 
void sendWinner(int& socket, std::string& winner);

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <name> <port>" << std::endl;
        return 1;
    }

    std::string name = argv[1];
    int port = std::stoi(argv[2]);
    Player server(name);
    std::cout << "Waiting for an opponent..." << std::endl;

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Error creating the socket!" << std::endl;
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    serverAddr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))== -1)
    {
        std::cerr << "Error binding the socket!" << std::endl;
        close(server_socket);
        return 1;
    }

    listen (server_socket, 1);
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket < 0)
    {
        std::cerr << "Error accepting connection!" << std::endl;
    }

    // Game Logic
    std::string clientName = handshake(client_socket, server);

    getMove(server);
    sendServerMove(client_socket, server);
    std::cout << "Waiting for " << clientName << " to make a move..." << std::endl;
    int clientMove = getClientMove(client_socket);

    std::string winner = determineWinner(
        server.get_name(), 
        server.get_move(), 
        clientName, 
        clientMove
    );


    sendWinner(client_socket, winner);
    
    countdown();
    std::cout << "Player moves:" << std::endl;    
    encodeMove(server.get_move(), server.get_name());
    encodeMove(clientMove, clientName);
    std::cout << "Winner: " << winner << std::endl;
    
    close(server_socket);
    return (0);
}

std::string handshake(int& client_socket, Player& player)
{
    char client_player[1024];
    memset(client_player, 0, sizeof(client_player));

    recv(client_socket, client_player, sizeof(client_player), 0);
    std::cout << "Opponent found: " << client_player << std::endl;

    std::string server_name = player.get_name();
    send(client_socket, server_name.c_str(), server_name.size(), 0);

    return std::string(client_player);
}

void sendServerMove(int& socket, Player& player)
{
    int move = player.get_move();
    send(socket, &move, sizeof(move), 0);
}

int getClientMove(int& socket)
{
    int move;
    recv(socket, &move, sizeof(move), 0);
    return move;
}

std::string determineWinner(const std::string& player1, 
                            const int& player1Move, 
                            const std::string& player2, 
                            const int& player2Move){ 
    if (player1Move == player2Move) {
        return "It's a draw!";
    }

    // Define the rules for winning
    if ((player1Move == 1 && player2Move == 3) ||
        (player1Move == 3 && player2Move == 2) ||
        (player1Move == 2 && player2Move == 1)) {
        return player1;
    }
    else if ((player2Move == 1 && player1Move == 3) ||
             (player2Move == 3 && player1Move == 2) ||
             (player2Move == 2 && player1Move == 1)) {
        return player2;
    }

    return "Invalid move!";
}

void sendWinner(int& socket, std::string& winner)
{
    send(socket, winner.c_str(), winner.size(), 0);
}
