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

            void setClientPseudo(std::string pseudo) { _pseudo = pseudo; };
            void setClientUuid(std::string uuid) { _uuid = uuid; };
            void setClientAuth(bool is_auth) { _is_auth = is_auth; };
            void setCurrentTeam(std::string team_uuid) { current_team = team_uuid; };
            void setCurrentChannel(std::string channel_uuid) { current_channel = channel_uuid; };
            void setCurrentThread(std::string thread_uuid) { current_thread = thread_uuid; };
        

            int getClientSocket() const { return _client_socket; };
            std::string getClientPseudo() const { return _pseudo; };
            std::string getUuid() const { return _uuid; };
            bool isAuthenticated() const { return _is_auth; };
            std::string getCurrentTeam() const { return current_team; };
            std::string getCurrentChannel() const { return current_channel; };
            std::string getCurrentThread() const { return current_thread; };

        private:
            int _client_socket = -1;
            std::string _uuid = "";
            std::string _pseudo = "";
            bool _is_auth = false;

            std::string current_team = "";
            std::string current_channel = "";
            std::string current_thread = "";
    };
}