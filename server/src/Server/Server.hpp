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
    #include <map>

    #include "Client.hpp"
    #include "PollFD.hpp"
    #include "NetworkServer.hpp"
    #include "Parser.hpp"
    #include "Hub.hpp"
    #include "Command.hpp"

    #define MAX_CLIENTS 1024

namespace myTeams
{
    class Server
    {
        private:
            PollFD _poll_fds = {};
            unsigned int _nb_clients = 0;
            NetworkServer _network_server;
            Hub _hub = {};
            Command _command;
            Parser _parser;

            // 2 CLIENT [Sojourner, A23DNKDzo0...]
            std::map<int, std::unique_ptr<Client>> _online_clients = {};

            // Sojourner A23DNKDzo0...
            std::map<std::string, std::string> _all_clients = {};

            static bool _is_running;
            static void signalHandler(int signal);

        public:
            Server();
            ~Server() = default;

            void runServer();
            void initServer(uint16_t port) { _network_server.initNetworkServer(port); }
            void disconnectClient(int client_socket);
            bool displayHelp(int argc, char *argv[]) const;
    };
}
