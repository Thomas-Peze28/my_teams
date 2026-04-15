/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Command
*/

#include "Command.hpp"

myTeams::Command::Command(Hub &hub, std::map<int, std::unique_ptr<Client>>& online_clients, std::map<std::string, std::string>& all_clients)
: _hub(hub), _online_clients(online_clients), _all_clients(all_clients)
{
}

void myTeams::Command::help(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Help command executed." << std::endl;
}

void myTeams::Command::login(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Login command executed." << std::endl;
}

void myTeams::Command::logout(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Logout command executed." << std::endl;
}

void myTeams::Command::users(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Users command executed." << std::endl;
}

void myTeams::Command::user(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "User command executed." << std::endl;
}

void myTeams::Command::send(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Send command executed." << std::endl;
}

void myTeams::Command::messages(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Messages command executed." << std::endl;
}

void myTeams::Command::subscribe(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Subscribe command executed." << std::endl;
}

void myTeams::Command::subscribed(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Subscribed command executed." << std::endl;
}

void myTeams::Command::unsubscribe(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Unsubscribe command executed." << std::endl;
}

void myTeams::Command::use(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Use command executed." << std::endl;
}

void myTeams::Command::create(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Create command executed." << std::endl;
}

void myTeams::Command::list(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "List command executed." << std::endl;
}

void myTeams::Command::info(__attribute_maybe_unused__ CommandData& cmd, __attribute_maybe_unused__ int client_socket) const
{
    std::cout << "Info command executed." << std::endl;
}
