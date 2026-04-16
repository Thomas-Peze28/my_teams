/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** NetworkServer
*/

#pragma once

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <cstdint>
    #include <vector>
    #include <memory>

    #include "Client.hpp"
    #include "PollFD.hpp"

namespace myTeams
{
    class NetworkServer
    {
        public:
            NetworkServer(PollFD &poll_fds, unsigned int &client_online);
            ~NetworkServer() = default;

            void initNetworkServer(uint16_t port);
            std::pair<int, std::unique_ptr<Client>> acceptNewConnection();

            int getServerSocket() const { return _server_socket; };
            uint16_t getServerPort() const { return ntohs(_server_addr.sin_port); };

        private:
            PollFD &_poll_fds;
            int _server_socket = -1;
            unsigned int _client_online = 0;
            struct sockaddr_in _server_addr = {};
    };
}