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

void myTeams::Command::help(__attribute_maybe_unused__ CommandData& cmd, int client_socket) const
{
    dprintf(client_socket, "Available commands:\n");
    dprintf(client_socket, "/help : show help\n");
    dprintf(client_socket, "/login [”user_name”] : set the user_name used by client\n");
    dprintf(client_socket, "/logout : disconnect the client from the server\n");
    dprintf(client_socket, "/users : get the list of all users that exist on the domain\n");
    dprintf(client_socket, "/user [”user_uuid”] : get details about the requested user\n");
    dprintf(client_socket, "/send [”user_uuid”] [”message_body”] : send a message to specific user\n");
    dprintf(client_socket, "/messages [”user_uuid”] : list all messages exchanged with the specified user\n");
    dprintf(client_socket, "/subscribe [”team_uuid”] : subscribe to the events of a team and its sub directories (enable reception of all events from a team)\n");
    dprintf(client_socket, "/subscribed ?[”team_uuid”] : list all subscribed teams or list all users subscribed to a team\n");
    dprintf(client_socket, "/unsubscribe [”team_uuid”] : unsubscribe from a team\n");
    dprintf(client_socket, "/use ?[”team_uuid”] ?[”channel_uuid”] ?[”thread_uuid”] : Sets the command context to a team/channel/thread\n");
    dprintf(client_socket, "/create : based on the context, create the sub resource (see below)\n");
    dprintf(client_socket, "/list : based on the context, list all the sub resources (see below)\n");
    dprintf(client_socket, "/info : based on the context, display details of the current resource (see below)\n");
}

void myTeams::Command::login(CommandData& cmd, int client_socket) const
{
    const std::string user_pseudo = cmd.args[0];
    if (user_pseudo.empty())
        return;
    for (const auto& [socket, client] : _online_clients)
        if (client && client->getClientPseudo() == user_pseudo) {
            dprintf(client_socket, "900 ALREADY_EXIST (error: user already logged in)\n");
            return;
        }
    auto it = _all_clients.find(user_pseudo);
    if (it == _all_clients.end()) {
        uuid_t uu;
        char uuid_str[37];
        uuid_generate(uu);
        uuid_unparse_lower(uu, uuid_str);
        _all_clients[user_pseudo] = std::string(uuid_str);
        server_event_user_created((std::string(uuid_str)).c_str(), user_pseudo.c_str());
        it = _all_clients.find(user_pseudo);
    }
    const std::string& user_uuid = it->second;
    _online_clients[client_socket]->setClientUuid(user_uuid);
    _online_clients[client_socket]->setClientPseudo(user_pseudo);
    _online_clients[client_socket]->setClientAuth(true);
    dprintf(client_socket, "100 LOGIN %s %s\n", user_uuid.c_str(), user_pseudo.c_str());
    server_event_user_logged_in(user_uuid.c_str());
}

void myTeams::Command::logout(__attribute_maybe_unused__ CommandData& cmd, int client_socket) const
{
    std::string client_uuid = _online_clients[client_socket]->getUuid();
    std::string client_pseudo = _online_clients[client_socket]->getClientPseudo();

    _online_clients[client_socket]->setClientPseudo("");
    _online_clients[client_socket]->setClientUuid("");
    _online_clients[client_socket]->setClientAuth(false);
    server_event_user_logged_out(client_uuid.c_str());
    dprintf(client_socket, "101 LOGOUT %s %s\n", client_pseudo.c_str(), client_uuid.c_str());
}

void myTeams::Command::users(__attribute_maybe_unused__ CommandData& cmd, int client_socket) const
{
    dprintf(client_socket, "000 LIST_START\n");
    for (const auto& [pseudo, uuid] : _all_clients) {
        bool status = false;
        for (const auto& [socket, client] : _online_clients) {
            if (client && client->getUuid() == uuid) {
                status = true;
                break;
            }
        }
        dprintf(client_socket, "103 USERS %s %s %d\n", uuid.c_str(), pseudo.c_str(), status ? 1 : 0);
    }
    dprintf(client_socket, "999 LIST_END\n");
}

void myTeams::Command::user(CommandData& cmd, int client_socket) const
{
    std::string user_uuid = cmd.args[0];

    for (const auto& [pseudo, uuid] : _all_clients) {
        if (uuid == user_uuid) {
            bool status = false;
            for (const auto& [socket, client] : _online_clients) {
                if (client && client->getUuid() == uuid) {
                    status = true;
                    break;
                }
            }
            dprintf(client_socket, "105 USER %s %s %d\n", uuid.c_str(), pseudo.c_str(), status ? 1 : 0);
            return;
        }
    }
    dprintf(client_socket, "904 UNKNOWN_USER_UUID %s (error: user not found)\n", user_uuid.c_str());
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
