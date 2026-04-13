/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

bool myTeams::Server::_is_running = false;

void myTeams::Server::signalHandler(int signal)
{
    if (signal == SIGINT)
        _is_running = false;
}

bool myTeams::Server::displayHelp(int argc, char *argv[]) const
{
    for (unsigned int i = 0; argv[i] != NULL; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << "USAGE: ./myteams_server PORT" << std::endl;
            std::cout << "PORT is the port number on which the server socket listens." << std::endl;
            return true;
        }
    }
    if (argc != 2) {
        std::cout << "USAGE: ./myteams_server PORT" << std::endl;
        return true;
    }
    return false;
}

void myTeams::Server::initServer(u_int16_t port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    int opt = 1;

    if (fd == -1)
        return;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        close(fd);
        return;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(fd);
        return;
    }
    if (listen(fd, 10) == -1) {
        close(fd);
        return;
    }
    _server_socket = fd;
    _server_addr = addr;
    _poll_fds[0].fd = _server_socket;
    _poll_fds[0].events = POLLIN;
    for (int i = 1; i <= MAX_CLIENTS; i++) {
        _poll_fds[i].fd = -1;
        _poll_fds[i].events = 0;
    }
}

void myTeams::Server::addNewClient()
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = -1;

    client_fd = accept(_server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0)
        return;
    if (_client_online >= MAX_CLIENTS) {
        close(client_fd);
        return;
    }
    for (int i = 1; i <= MAX_CLIENTS; i++) {
        if (_poll_fds[i].fd == -1) {
            _poll_fds[i].fd = client_fd;
            _poll_fds[i].events = POLLIN;
            _clients.emplace_back(std::make_unique<Client>(client_addr, client_fd));
            _client_online++;
            return;
        }
    }
    close(client_fd);
}

void myTeams::Server::deleteClient(int client_socket)
{
    for (unsigned int i = 1; i <= MAX_CLIENTS; i++)
        if (_poll_fds[i].fd == client_socket) {
            _poll_fds[i].fd = -1;
            _poll_fds[i].events = 0;
        }
    for (unsigned int j = 0; j < _clients.size(); j++)
        if (_clients[j]->getClientSocket() == client_socket) {
            close(client_socket);
            _clients.erase(_clients.begin() + j);
            if (_client_online > 0)
                _client_online--;
            return;
        }
    close(client_socket);
}

void myTeams::Server::runServer()
{
    std::signal(SIGINT, signalHandler);

    std::cout << "Server is running on port : " << ntohs(_server_addr.sin_port) << std::endl;
    _is_running = true;
    while (_is_running) {
        if (poll(_poll_fds, MAX_CLIENTS + 1, -1) < 0) {
            if (errno == EINTR)
                continue;
            continue;
        }
        if (_poll_fds[0].revents & POLLIN)
            addNewClient();
        for (unsigned int i = 1; i <= MAX_CLIENTS; i++) {
            if (_poll_fds[i].fd == -1)
                continue;
            if (_poll_fds[i].revents & (POLLHUP | POLLERR | POLLNVAL)) {
                deleteClient(_poll_fds[i].fd);
                continue;
            }
            if (_poll_fds[i].revents & POLLIN) {
                int bytes_read = 0;
                char buffer[1024];
                bytes_read = read(_poll_fds[i].fd, buffer, sizeof(buffer) - 1);
                if (bytes_read <= 0) {
                    deleteClient(_poll_fds[i].fd);
                    continue;
                }
                buffer[bytes_read] = '\0';
                dprintf(_poll_fds[i].fd, "MESSAGE: %s\n", buffer);
            }
        }
    }
    std::cout << "LE NOMBRE DE CLIENS : " << _client_online << std::endl;
    for (unsigned int i = 1; i <= MAX_CLIENTS; i++) {
        if (_poll_fds[i].fd != -1) {
            close(_poll_fds[i].fd);
            _poll_fds[i].fd = -1;
        }
    }
    if (_server_socket != -1)
        close(_server_socket);
    std::cout << "Server is shutting down" << std::endl;
}