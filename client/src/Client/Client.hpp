/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#pragma once

    #include <iostream>
    #include <cstdlib>
    #include <vector>
    #include <map>
    #include <functional>
    #include <string>
    #include <cstdint>

    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <poll.h>

    extern "C" {
        #include "logging_client.h"
    }

namespace myTeams
{
    class Client
    {
        private:
            std::string _ip;
            uint16_t _port = 0;
            int _serverSocket = -1;
            bool _isRunning = false;

            bool connectToServer();
            bool handleServerInput();
            bool handleUserInput();
            void processServerMessage(const std::string &message);
            std::vector<std::string> extractArgs(const std::string &message);

            std::map<std::string, std::function<void(const std::vector<std::string>&)>> _routes;
            void initRoutes();

        public:
            Client();
            ~Client();

            bool displayHelp(int argc, char *argv[]) const;
            void initClient(const std::string &ip, uint16_t port);
            void run();
    };
}