/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#pragma once

    #include <iostream>
    #include <cstdlib>
    #include <unistd.h>
    #include <vector>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

namespace myTeams
{
    class Client
    {
        private:
            std::string _ip;
            u_int16_t _port = 0;
            int _serverSocket = -1;
            bool _isRunning = false;

            bool connectToServer();
    
        public:
            Client() = default;
            ~Client();

            bool displayHelp(int argc, char *argv[]) const;
            void initClient(const std::string &ip, u_int16_t port);
            void run();
    };
}