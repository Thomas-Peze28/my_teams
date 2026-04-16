/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Client.hpp"

myTeams::Client::Client()
{
    initRoutes();
}

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

void myTeams::Client::initClient(const std::string &ip, uint16_t port)
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
    client_event_logged_in("1234-uuid-test", "Thomas_Test"); // Exemple de test de la fonction de logging client
}

bool myTeams::Client::handleUserInput()
{
    std::string input;
    std::getline(std::cin, input);

    if (input == "exit") {
        _isRunning = false;
        std::cout << "[INFO] You've been disconnected." << std::endl;
        return true;
    }

    std::string message = input + "\n";
    send(_serverSocket, message.c_str(), message.size(), 0);
    return true;
}

std::vector<std::string> myTeams::Client::extractArgs(const std::string &message)
{
    std::vector<std::string> args;
    size_t pos = 0;

    while ((pos = message.find('\'', pos)) != std::string::npos) {
        size_t endPos = message.find('\'', pos + 1);
        if (endPos == std::string::npos)
            break;
        args.push_back(message.substr(pos + 1, endPos - pos - 1));
        pos = endPos + 1;
    }
    return args;
}

void myTeams::Client::initRoutes()
{
    _routes["100 LOGIN"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2) {
            client_event_logged_in(args[0].c_str(), args[1].c_str());
        }
    };
    _routes["101 LOGOUT"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2) {
            client_event_logged_out(args[0].c_str(), args[1].c_str());
        }
    };
}

void myTeams::Client::processServerMessage(const std::string &message)
{
    std::string key = message;
    size_t quotePos = message.find('\'');
    if (quotePos != std::string::npos) {
        key = message.substr(0, quotePos);
    }
    
    while (!key.empty() && std::isspace(key.back())) {
        key.pop_back();
    }

    if (key == "000 LIST_START" || key == "999 LIST_END" || key == "200 SEND_OK")
        return;

    auto it = _routes.find(key);
    if (it != _routes.end()) {
        std::vector<std::string> args = extractArgs(message);
        it->second(args);
    } else {
        std::cout << "[ERROR] Unhandled message from server: " << message << std::endl;
    }
    
}

bool myTeams::Client::handleServerInput()
{
    std::string buffer(1024, '\0');
    ssize_t bytesRead = recv(_serverSocket, &buffer[0], buffer.size(), 0);

    if (bytesRead > 0) {
        buffer.resize(bytesRead);
        processServerMessage(buffer);
        return true;
    } else if (bytesRead == 0) {
        std::cout << "[INFO] Server closed the connection." << std::endl;
        _isRunning = false;
        return false;
    } else {
        std::cout << "[ERROR] Failed to receive data from server." << std::endl;
        return false;
    }
}

void myTeams::Client::run()
{
    _isRunning = true;
    std::cout << "Client is running. Type 'exit' to quit." << std::endl;

    std::vector<struct pollfd> fds(2);
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = _serverSocket;
    fds[1].events = POLLIN;

    while (_isRunning) {
        int pollResult = poll(fds.data(), fds.size(), -1);

        if (pollResult < 0) {
            std::cerr << "[ERROR] poll have failed." << std::endl;
            break;
        }

        if (fds[0].revents & POLLIN) {
            handleUserInput();
        }

        if (fds[1].revents & POLLIN) {
            handleServerInput();
        }

        if (fds[1].revents & (POLLHUP | POLLERR)) {
            std::cout << "[INFO] Server closed the connection." << std::endl;
            _isRunning = false;
        }
    }
}