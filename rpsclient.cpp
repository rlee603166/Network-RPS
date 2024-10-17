
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include "player.h"
#include "game.h"

std::string client_handshake(int& client_socket, Player& player);
int getServerMove(int& client_socket);
void sendMoveToServer(int& socket, Player& player);
std::string getResults(int& socket);


int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <name> <port>" << std::endl;
        return 1;
    }
    std::string player_name = argv[1];
    int port = std::stoi(argv[2]);
    Player client(player_name);

    std::cout << "Waiting for an opponent..." << std::endl;

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        std::cerr << "Error creating the socket..." << std::endl;
    }

    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &clientAddr.sin_addr);

    connect(client_socket, (struct sockaddr*)&clientAddr, sizeof(clientAddr));

    std::string serverName = client_handshake(client_socket, client);
    std::cout << "Waiting for " << serverName << " to make a move..." << std::endl;
    int serverMove = getServerMove(client_socket);

    getMove(client);
    sendMoveToServer(client_socket, client);

    std::string results = getResults(client_socket);

    countdown();
    std::cout << "Player moves:" << std::endl;    
    encodeMove(client.get_move(), client.get_name());
    encodeMove(serverMove, serverName);
    std::cout << "Winner: " << results;

    close(client_socket);
    return (0);
}

std::string client_handshake(int& client_socket, Player& player)
{
    std::string name = player.get_name();
    send(client_socket, name.c_str(), name.size(), 0);

    char server_player[1024];
    memset(server_player, 0, sizeof(server_player));   
    recv(client_socket, server_player, sizeof(server_player), 0);
    std::cout << "Opponent found: " << server_player << std::endl;

    return std::string(server_player);
}

int getServerMove(int& socket)
{
    int move;
    recv(socket, &move, sizeof(move), 0);
    return move;
}

void sendMoveToServer(int& socket, Player& player)
{
    int move = player.get_move();
    send(socket, &move, sizeof(move), 0);
}


std::string getResults(int& socket)
{
    char results[1024];
    recv(socket, results, sizeof(results), 0);
    return std::string(results);
}

