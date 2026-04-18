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
    #include <unordered_map>
    #include <cerrno>

    #include "Client.hpp"
    #include "CommandData.hpp"
    #include "Command.hpp"

    #define BUFFER_SIZE 1024

namespace myTeams
{
    class Parser
    {
        public:
            Parser(Command &command);
            ~Parser() = default;

            bool isClientDisconnected(int client_socket) const;
            void handleCommand(Client& client) const;

            void loadData() {};
            void saveData() {};

        private:
            Command &_command;

            void executeCommand(Client& client, const CommandData& cmd) const;
    };
}