/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Client
*/

#pragma once

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <string>

namespace myTeams
{
    class Client
    {
        public:
            Client(int socket);
            ~Client() = default;

            int getClientSocket() const { return _client_socket; };
            int getUuid() const { return uuid; };

        private:
            int _client_socket = -1;
            int uuid = 0;
            std::string _pseudo = "";
            bool _is_auth = false;
    };
}