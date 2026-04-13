/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#pragma once

    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <poll.h>
    #include <csignal>
    #include <memory>
    #include <vector>
    #include <cerrno>

    #include "Client.hpp"

    #define MAX_CLIENTS 1024

namespace myTeams
{
    class Server
    {
        private:
            struct sockaddr_in _server_addr = {};
            struct pollfd _poll_fds[MAX_CLIENTS + 1] = {};
            std::vector<std::unique_ptr<Client>> _clients = {};
            int _server_socket = -1;
            unsigned int _client_online = 0;
            static bool _is_running;
            
            static void signalHandler(int signal);

        public:
            Server() = default;
            ~Server() = default;

            void initServer(u_int16_t port);
            void runServer();

            void addNewClient();
            void deleteClient(int client_socket);

            bool displayHelp(int argc, char *argv[]) const;
    };
}
