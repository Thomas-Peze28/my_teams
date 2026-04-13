/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** PoolFD
*/

#pragma once

    #include <unistd.h>
    #include <poll.h>

    #define MAX_CLIENTS 1024

namespace myTeams
{
    class PollFD
    {
        public:
            PollFD() = default;
            ~PollFD();

            bool addNewClient(int client_sokcet);
            void deleteClient(int client_socket);
            void initPollFD(int server_socket);

            struct pollfd *getPollFDs() { return _poll_fds; }

        private:
            struct pollfd _poll_fds[MAX_CLIENTS + 1] = {};
    };
}