/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#pragma once

    #include <filesystem>
    #include <iostream>
    #include <csignal>
    #include <fstream>
    #include <cerrno>
    #include <map>

    #include "Client.hpp"
    #include "Hub.hpp"
    #include "PollFD.hpp"
    #include "NetworkServer.hpp"
    #include "Parser.hpp"
    #include "Command.hpp"

    extern "C" {
        #include "logging_server.h"
    }

    #define MAX_CLIENTS 1024

namespace myTeams
{
    class Server
    {
        private:
            /*
                Proprieties Network
            */
            PollFD _poll_fds = {};
            unsigned int _nb_clients = 0;
            NetworkServer _network_server;
            static bool _is_running;
            static void signalHandler(int signal);

            /*
                Proprieties Clients
            */
            std::map<int, std::unique_ptr<Client>> _online_clients = {};
            std::map<std::string, std::string> _all_clients = {};

            /*
                Proprieties Application
            */
            Hub _hub;
            Command _command;
            Parser _parser;

        public:
            Server();
            ~Server() = default;

            void runServer();
            void initServer(uint16_t port);
            void disconnectClient(int client_socket);
            bool displayHelp(int argc, char *argv[]) const;
            void save();
            void loadUsers();
            void loadTeams();
            void loadChannels(Team &team, const std::string &channels_path);
            void loadThreads(Channel &channel, const std::string &threads_path);
    };
}
