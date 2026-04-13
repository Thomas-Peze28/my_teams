/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#pragma once

    #include <iostream>
    #include <csignal>
    #include <cerrno>

    #include "Client.hpp"
    #include "PollFD.hpp"
    #include "NetworkServer.hpp"

    #define MAX_CLIENTS 1024

namespace myTeams
{
    class Server
    {
        private:
            PollFD _poll_fds = {};
            NetworkServer _network_server;

            std::vector<std::unique_ptr<Client>> _online_clients = {};

            std::vector<std::pair<std::string, unsigned int>> _all_clients = {};

            static bool _is_running;
            static void signalHandler(int signal);

        public:
            Server();
            ~Server() = default;

            void runServer();
            void initServer(uint16_t port) { _network_server.initNetworkServer(port); }
            bool displayHelp(int argc, char *argv[]) const;
    };
}
