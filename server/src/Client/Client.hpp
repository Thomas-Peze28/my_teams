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
            std::string getUuid() const { return uuid; };
            bool isAuthenticated() const { return _is_auth; };

        private:
            int _client_socket = -1;
            std::string uuid = "";
            std::string _pseudo = "";
            bool _is_auth = false;

            std::string current_team = "";
            std::string current_channel = "";
            std::string current_thread = "";
    };
}