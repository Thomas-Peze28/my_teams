/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Parser
*/

#include "Parser.hpp"

myTeams::Parser::Parser(Command &command) : _command(command)
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

void myTeams::Parser::handleCommand(Client& client) const
{
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read = recv(client.getSocket(), buffer, sizeof(buffer) - 1, 0);

    if (bytes_read <= 0)
        return;

    buffer[bytes_read] = '\0';

    CommandData cmd;
    std::istringstream stream(buffer);
    std::string arg;

    stream >> cmd.name;
    while (stream >> arg)
        cmd.args.push_back(arg);
    cmd.nb_args = cmd.args.size();

    executeCommand(client, cmd);
}

void myTeams::Parser::executeCommand(Client& client, const CommandData& cmd) const
{
    using CommandHandler = void (Command::*)(Client&, CommandData) const;

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
        {"/use", {&Command::use, true, 1, 1}},
        {"/subscribe", {&Command::subscribe, true, 1, 1}},
        {"/unsubscribe", {&Command::unsubscribe, true, 1, 1}},
        {"/subscribed", {&Command::subscribed, true, 0, 1}}
    };

    const auto it = handlers.find(cmd.name);
    if (it == handlers.end()) {
        dprintf(client.getSocket(), "919 UNKNOWN COMMAND: %s\n", cmd.name.c_str());
        return;
    }
    if (it->second.requires_auth && !client.getAuth()) {
        dprintf(client.getSocket(), "401 UNAUTHORIZED : you must be logged in to use this command\n");
        return;
    }
    if (cmd.nb_args < it->second.min_args || cmd.nb_args > it->second.max_args) {
        dprintf(client.getSocket(), "400 BAD REQUEST : wrong number of arguments for command %s\n", cmd.name.c_str());
        return;
    }
    (_command.*(it->second.handler))(client, cmd);
}