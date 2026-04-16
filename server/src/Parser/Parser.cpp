/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Parser
*/

#include "Parser.hpp"
#include <unordered_map>
#include <climits>

myTeams::Parser::Parser(Command& command, std::map<int, std::unique_ptr<Client>>& online_clients)
: _command(command),  _online_clients(online_clients)
{
}

bool myTeams::Parser::isClientDisconnected(int client_socket) const
{
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, MSG_PEEK | MSG_DONTWAIT);

    if (bytes_read == 0)
        return true;
    if (bytes_read < 0 && errno == ECONNRESET)
        return true;
    if (bytes_read < 0 && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
        return false;
    return false;
}

void myTeams::Parser::handleCommand(int client_socket) const
{
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes_read <= 0)
        return;

    buffer[bytes_read] = '\0';

    CommandData cmd;
    std::istringstream stream(buffer);

    stream >> cmd.name;
    while (stream >> cmd.args.emplace_back());
    cmd.args.pop_back();
    cmd.nb_args = cmd.args.size();

    executeCommand(cmd, client_socket);
}

void myTeams::Parser::executeCommand(CommandData& cmd, int client_socket) const
{
    using CommandHandler = void (Command::*)(CommandData&, int) const;
    struct CommandSpec {
        CommandHandler handler;
        bool requires_auth;
        int min_args;
        int max_args;
    };

    static const std::unordered_map<std::string, CommandSpec> handlers = {
        {"/help", {&Command::help, false, 0, 0}},
        {"/login", {&Command::login, false, 1, 1}},
        {"/logout", {&Command::logout, true, 0, 0}},
        {"/users", {&Command::users, true, 0, 0}},
        {"/user", {&Command::user, true, 1, 1}},
        {"/send", {&Command::send, true, 2, 2}},
        {"/messages", {&Command::messages, true, 1, 1}},
        {"/subscribe", {&Command::subscribe, true, 1, 1}},
        {"/subscribed", {&Command::subscribed, true, 1, 1}},
        {"/unsubscribe", {&Command::unsubscribe, true, 1, 1}},
        {"/use", {&Command::use, true, 1, 3}},
        {"/create", {&Command::create, true, 1, 2}},
        {"/list", {&Command::list, true, 0, 0}},
        {"/info", {&Command::info, true, 0, 0}},
    };

    auto client_it = _online_clients.find(client_socket);
    auto it = handlers.find(cmd.name);

    if (it == handlers.end()) {
        dprintf(client_socket, "919 UNKNOW COMMAND: %s\n", cmd.name.c_str());
        return;
    }
    if (client_it == _online_clients.end() || client_it->second == nullptr)
        return;
    bool is_authenticated = client_it->second->isAuthenticated();
    if (!is_authenticated && it->second.requires_auth) {
        dprintf(client_socket, "902 UNAUTHORIZED (error: not logged in)\n");
        return;
    }
    if (cmd.nb_args < it->second.min_args || cmd.nb_args > it->second.max_args) {
        dprintf(client_socket, "920 INVALID NUMBERS OF ARGUMENTS FOR COMMAND: %s\n", cmd.name.c_str());
        return;
    }
    (_command.*(it->second.handler))(cmd, client_socket);
}
