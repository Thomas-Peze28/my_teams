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
    #include <cerrno>

namespace myTeams
{
    class Parser
    {
        public:
            Parser() = default;
            ~Parser() = default;

            void handleCommand(int client_socket) const;
            bool isClientDisconnected(int client_socket) const;
    };
}