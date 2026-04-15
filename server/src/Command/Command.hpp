/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Command
*/

#pragma once

    #include <iostream>
    #include "Hub.hpp"
    #include "Client.hpp"
    #include "CommandData.hpp"
    #include <map>
    #include <memory>

namespace myTeams
{
    class Command
    {
        public:
            Command(Hub &hub, std::map<int, std::unique_ptr<Client>>& online_clients, std::map<std::string, std::string>& all_clients);
            ~Command() = default;

            void help(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void login(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void logout(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void users(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void user(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void send(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void messages(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void subscribe(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void subscribed(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void unsubscribe(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void use(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void create(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void list(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;
            void info(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const;

        private:
            Hub &_hub;
            std::map<int, std::unique_ptr<Client>>& _online_clients;
            std::map<std::string, std::string>& _all_clients;
    };
}