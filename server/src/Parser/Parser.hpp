/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Parser
*/

#pragma once

    #include <iostream>
    #include <string>
    #include <sys/socket.h>
    #include <vector>
    #include <sstream>
    #include <map>
    #include <memory>
    #include "Client.hpp"
    #include "Hub.hpp"
    #include "CommandData.hpp"
    #include "Command.hpp"
    #include <cerrno>

    #define BUFFER_SIZE 1024

namespace myTeams
{
    class Parser
    {
        public:
            Parser(Command& command, std::map<int, std::unique_ptr<Client>>& online_clients);
            ~Parser() = default;

            bool isClientDisconnected(int client_socket) const;
            void handleCommand(int client_socket) const;

        private:

            Command &_command;
            std::map<int, std::unique_ptr<Client>>& _online_clients;
            void executeCommand(CommandData& cmd, int client_socket) const;
    };
}