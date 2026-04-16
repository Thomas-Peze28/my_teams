/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

bool myTeams::Server::_is_running = false;

myTeams::Server::Server() : _network_server(_poll_fds, _nb_clients), _command(_hub, _online_clients, _all_clients), _parser(_command, _online_clients)
{
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

void myTeams::Server::disconnectClient(int client_socket)
{
    _online_clients.erase(client_socket);
    _poll_fds.deleteClient(client_socket);
    _nb_clients--;
}

void myTeams::Server::signalHandler(int signal)
{
    if (signal == SIGINT)
        _is_running = false;
}

void myTeams::Server::runServer()
{
    std::signal(SIGINT, signalHandler);
    std::cout << "Server is running on port : " << _network_server.getServerPort() << std::endl;
    _is_running = true;
    while (_is_running)  {
        if (poll(_poll_fds.getPollFDs(), MAX_CLIENTS + 1, 350) < 0)
            continue;
        if (_poll_fds.getPollFDs()[0].revents & POLLIN) {
            std::pair<int, std::unique_ptr<myTeams::Client>> new_client = _network_server.acceptNewConnection();
            if (new_client.first != -1) {
                _nb_clients++;
                _online_clients[new_client.first] = std::move(new_client.second);
            }
        }
        for (unsigned int i = 1; i < MAX_CLIENTS + 1; i++) {
            if (_poll_fds.getPollFDs()[i].fd == -1)
                continue;
            if (_poll_fds.getPollFDs()[i].revents & (POLLHUP | POLLERR | POLLNVAL)) {
                disconnectClient(_poll_fds.getPollFDs()[i].fd);
                continue;
            }
            if (_poll_fds.getPollFDs()[i].revents & POLLIN) {
                if (_parser.isClientDisconnected(_poll_fds.getPollFDs()[i].fd))
                    disconnectClient(_poll_fds.getPollFDs()[i].fd);
                else
                    _parser.handleCommand(_poll_fds.getPollFDs()[i].fd);
            }
        }
    }
}
