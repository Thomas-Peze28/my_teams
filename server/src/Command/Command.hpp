/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Command
*/

#pragma once

    #include <iostream>
    #include "Client.hpp"
    #include "Hub.hpp"
    #include "CommandData.hpp"
    #include <map>
    #include <memory>
    #include <uuid/uuid.h>
    #include <functional>

    extern "C" {
    #include "logging_server.h"
    }

namespace myTeams
{
    class Command
    {
        public:
            Command(std::map<int, std::unique_ptr<Client>>& online_clients, std::map<std::string, std::string>& all_clients, Hub& hub) : _online_clients(online_clients), _all_clients(all_clients), _hub(hub) {};
            ~Command() = default;

            void help(Client &client, __attribute_maybe_unused__ CommandData data) const;
            void login(Client &client, CommandData data) const;
            void logout(Client &client, __attribute_maybe_unused__ CommandData data) const;
            void users(Client &client, __attribute_maybe_unused__ CommandData data) const;
            void user(Client &client, CommandData data) const;
            void use(Client &client, CommandData data) const;
            void subscribe(Client &client, CommandData data) const;
            void unsubscribe(Client &client, CommandData data) const;
            void subscribed(Client &client, CommandData data) const;

        private:
            std::map<int, std::unique_ptr<Client>>& _online_clients;
            std::map<std::string, std::string>& _all_clients;
            Hub& _hub;

            std::string _getUuidFromPseudo(const std::string pseudo) const;
            std::unique_ptr<Client> _getClientFromPseudo(const std::string pseudo) const;

            std::string generateUuid() const;
    };
}