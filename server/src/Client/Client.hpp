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
            Client(struct sockaddr_in addr, int socket);
            ~Client() = default;

            int getClientSocket() const { return _client_socket; };

        private:
            struct sockaddr_in _server_addr = {};
            int _client_socket = -1;
            std::string _pseudo = "";
            bool _is_auth = false;
    };
}