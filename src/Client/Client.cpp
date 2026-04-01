/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Client.hpp"

myTeams::Client::~Client()
{
     if (_serverSocket != -1) {
        close(_serverSocket);
    }
}

bool myTeams::Client::displayHelp(int argc, char *argv[]) const
{
    for (unsigned int i = 0; argv[i] != NULL; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << "USAGE: ./myteams_cli IP PORT" << std::endl;
            std::cout << "IP is the IP address of the server." << std::endl;
            std::cout << "PORT is the port number on which the client connects." << std::endl;
            return true;
        }
    }

    if (argc != 3) {
        std::cout << "USAGE: ./myteams_cli IP PORT" << std::endl;
        return true;
    }
    return false;
}

bool myTeams::Client::connectToServer()
{
    sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(_ip.c_str());
    adress.sin_port = htons(_port);

    if (connect(_serverSocket, (sockaddr *)&adress, sizeof(adress)) == -1) {
        return false;
    }
    return true;
}

void myTeams::Client::initClient(const std::string &ip, u_int16_t port)
{
    _ip = ip;
    _port = port;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1) {
        std::cout << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!connectToServer()) {
        std::cout << "Failed to connect to server" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected to server at " << _ip << ":" << _port << std::endl;
}

void myTeams::Client::run()
{
    _isRunning = true;
    std::cout << "Client is running. Type 'exit' to quit." << std::endl;

    while (_isRunning) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") {
            _isRunning = false;
            std::cout << "Exiting client." << std::endl;
        } else {
    
            // Print the user input to the console
            std::cout << "You entered: " << input << std::endl;

            // Send the user input to the server
            std::string message = input + "\n";
            send(_serverSocket, message.c_str(), message.size(), 0);
        }
    }
}