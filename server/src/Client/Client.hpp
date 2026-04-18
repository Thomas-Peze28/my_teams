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

            // Setters
            void setPseudo(std::string pseudo) { _pseudo = pseudo; };
            void setUuid(std::string uuid) { _uuid = uuid; };
            void setAuth(bool is_auth) { _is_auth = is_auth; };

            void setCurrentTeam(std::string team_uuid) { current_team = team_uuid; };
            void setCurrentChannel(std::string channel_uuid) { current_channel = channel_uuid; };
            void setCurrentThread(std::string thread_uuid) { current_thread = thread_uuid; };

            // Getters
            std::string getPseudo() const { return _pseudo; };
            std::string getUuid() const { return _uuid; };
            bool getAuth() const { return _is_auth; };
            int getSocket() const { return _client_socket; };

            std::string getCurrentTeam() const { return current_team; };
            std::string getCurrentChannel() const { return current_channel; };
            std::string getCurrentThread() const { return current_thread; };
    
        private:
            std::string _pseudo = "";
            std::string _uuid = "";
            bool _is_auth = false;

            int _client_socket = -1;

            std::string current_team = "";
            std::string current_channel = "";
            std::string current_thread = "";
    };
}