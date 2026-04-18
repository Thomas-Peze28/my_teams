/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Command
*/

#include "Command.hpp"

std::string myTeams::Command::generateUuid() const
{
    uuid_t uuid;
    char uuid_str[37];

    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    return std::string(uuid_str);
}

std::string myTeams::Command::_getUuidFromPseudo(const std::string pseudo) const
{
    for (const auto& pair : _all_clients) {
        if (pair.second == pseudo)
            return pair.first;
    }
    return "";
}

std::unique_ptr<myTeams::Client> myTeams::Command::_getClientFromPseudo(const std::string pseudo) const
{
    for (const auto& pair : _online_clients) {
        if (pair.second->getPseudo() == pseudo)
            return std::make_unique<Client>(*pair.second);
    }
    return nullptr;
}

void myTeams::Command::help(Client &client, __attribute_maybe_unused__ CommandData data) const
{
    dprintf(client.getSocket(), "Available commands:\n");
    dprintf(client.getSocket(), "/help : show help\n");
    dprintf(client.getSocket(), "/login [”user_name”] : set the user_name used by client\n");
    dprintf(client.getSocket(), "/logout : disconnect the client from the server\n");
    dprintf(client.getSocket(), "/users : get the list of all users that exist on the domain\n");
    dprintf(client.getSocket(), "/user [”user_uuid”] : get details about the requested user\n");
    dprintf(client.getSocket(), "/send [”user_uuid”] [”message_body”] : send a message to specific user\n");
    dprintf(client.getSocket(), "/messages [”user_uuid”] : list all messages exchanged with the specified user\n");
    dprintf(client.getSocket(), "/subscribe [”team_uuid”] : subscribe to the events of a team and its sub directories (enable reception of all events from a team)\n");
    dprintf(client.getSocket(), "/subscribed ?[”team_uuid”] : list all subscribed teams or list all users subscribed to a team\n");
    dprintf(client.getSocket(), "/unsubscribe [”team_uuid”] : unsubscribe from a team\n");
    dprintf(client.getSocket(), "/use ?[”team_uuid”] ?[”channel_uuid”] ?[”thread_uuid”] : Sets the command context to a team/channel/thread\n");
    dprintf(client.getSocket(), "/create : based on the context, create the sub resource (see below)\n");
    dprintf(client.getSocket(), "/list : based on the context, list all the sub resources (see below)\n");
    dprintf(client.getSocket(), "/info : based on the context, display details of the current resource (see below)\n");
}

void myTeams::Command::login(Client &client, CommandData data) const
{
    if (client.getAuth()) {
        dprintf(client.getSocket(), "501 ALREADY_EXIST\n");
        return;
    }
    if (_getClientFromPseudo(data.args[0]) != nullptr) {
        dprintf(client.getSocket(), "501 ALREADY_EXIST\n");
        return;
    }
    if (!_getUuidFromPseudo(data.args[0]).empty()) {
        client.setUuid(_getUuidFromPseudo(data.args[0]));
        client.setPseudo(data.args[0]);
        client.setAuth(true);
    } else {
        client.setUuid(generateUuid());
        client.setPseudo(data.args[0]);
        client.setAuth(true);
        _all_clients[client.getUuid()] = client.getPseudo();
        server_event_user_created((std::string(client.getUuid())).c_str(), client.getPseudo().c_str());
    }
    dprintf(client.getSocket(), "100 LOGIN '%s' '%s'\n", client.getUuid().c_str(), client.getPseudo().c_str());
    server_event_user_logged_in(client.getUuid().c_str());
}

void myTeams::Command::logout(Client &client, __attribute_maybe_unused__ CommandData data) const
{
    dprintf(client.getSocket(), "100 LOGOUT '%s' '%s'\n", client.getPseudo().c_str(), client.getUuid().c_str());
    server_event_user_logged_out(client.getUuid().c_str());
    client.setAuth(false);
    client.setPseudo("");
    client.setUuid("");
}

void myTeams::Command::users(Client &client, __attribute_maybe_unused__ CommandData data) const
{
    for (unsigned int i = 0; i < _all_clients.size(); i++) {
        bool is_online = false;
        is_online = _getClientFromPseudo(std::next(_all_clients.begin(), i)->second) != nullptr;
        dprintf(client.getSocket(), "100 USERS '%s' '%s' '%d'\n", std::next(_all_clients.begin(), i)->first.c_str(), std::next(_all_clients.begin(), i)->second.c_str(), is_online ? 1 : 0);
    }
}

void myTeams::Command::user(Client &client, CommandData data) const
{
    std::string uuid = data.args[0];
    std::string pseudo = _all_clients.find(uuid)->second;
    if (pseudo.empty()) {
        dprintf(client.getSocket(), "500 UNKNOWN_USER '%s'\n", uuid.c_str());
        return;
    }
    bool is_online = _getClientFromPseudo(pseudo) != nullptr;
    dprintf(client.getSocket(), "100 USER '%s' '%s' '%d'\n", uuid.c_str(), pseudo.c_str(), is_online ? 1 : 0);
}

void myTeams::Command::use(Client &client, CommandData data) const
{
    std::string team_uuid = data.args.size() > 0 ? data.args[0] : "";
    std::string channel_uuid = data.args.size() > 1 ? data.args[1] : "";
    std::string thread_uuid = data.args.size() > 2 ? data.args[2] : "";

    if (_hub.getTeam(team_uuid) == nullptr) {
        dprintf(client.getSocket(), "500 UNKNOWN_TEAM '%s'\n", team_uuid.c_str());
        return;
    } else if (_hub.getTeam(team_uuid)->isMember(client.getUuid()) == false) {
        dprintf(client.getSocket(), "502 UNAUTHORIZED\n");
        return;
    } else if (!channel_uuid.empty() && _hub.getTeam(team_uuid)->getChannel(channel_uuid) == nullptr) {
        dprintf(client.getSocket(), "500 UNKNOWN_CHANNEL '%s'\n", channel_uuid.c_str());
        return;
    } else if (!thread_uuid.empty()) {
        auto *channel = _hub.getTeam(team_uuid)->getChannel(channel_uuid);
        if (channel == nullptr || channel->getThread(thread_uuid) == nullptr) {
            dprintf(client.getSocket(), "500 UNKNOWN_THREAD '%s'\n", thread_uuid.c_str());
            return;
        }
    }
    client.setCurrentTeam(team_uuid);
    client.setCurrentChannel(channel_uuid);
    client.setCurrentThread(thread_uuid);
    dprintf(client.getSocket(), "800 CONTEXT_SET\n");
}

void myTeams::Command::subscribe(Client &client, CommandData data) const
{
    std::string team_uuid = data.args[0];

    if (_hub.getTeam(team_uuid) == nullptr) {
        dprintf(client.getSocket(), "500 UNKNOWN_TEAM '%s'\n", team_uuid.c_str());
        return;
    } else if (_hub.getTeam(team_uuid)->isMember(client.getUuid()) == true) {
        dprintf(client.getSocket(), "501 ALREADY_EXIST\n");
        return;
    }
    _hub.getTeam(team_uuid)->addMember(client.getUuid());
    dprintf(client.getSocket(), "100 SUB_OK '%s' '%s'\n", client.getUuid().c_str(), team_uuid.c_str());
    server_event_user_subscribed(team_uuid.c_str(), client.getUuid().c_str());
}

void myTeams::Command::unsubscribe(Client &client, CommandData data) const
{
    std::string team_uuid = data.args[0];

    if (_hub.getTeam(team_uuid) == nullptr) {
        dprintf(client.getSocket(), "500 UNKNOWN_TEAM '%s'\n", team_uuid.c_str());
        return;
    } else if (_hub.getTeam(team_uuid)->isMember(client.getUuid()) == false) {
        dprintf(client.getSocket(), "502 UNAUTHORIZED\n");
        return;
    }
    _hub.getTeam(team_uuid)->removeMember(client.getUuid());
    dprintf(client.getSocket(), "100 UNSUB_OK '%s' '%s'\n", client.getUuid().c_str(), team_uuid.c_str());
    server_event_user_unsubscribed(team_uuid.c_str(), client.getUuid().c_str());
}

void myTeams::Command::subscribed(Client &client, CommandData data) const
{
    if (data.args.empty()) {
        dprintf(client.getSocket(), "000 LIST_START\n");
        for (const auto& team : _hub.getTeams()) {
            if (team.second && team.second->isMember(client.getUuid())) {
                dprintf(client.getSocket(), "100 SUB_TEAMS '%s' '%s' '%s'\n", team.second->getUuid().c_str(), team.second->getName().c_str(), team.second->getDescription().c_str());
            }
        }
        dprintf(client.getSocket(), "999 LIST_END\n");
    } else {
        std::string team_uuid = data.args[0];
        auto *team = _hub.getTeam(team_uuid);
        if (team == nullptr) {
            dprintf(client.getSocket(), "500 UNKNOWN_TEAM '%s'\n", team_uuid.c_str());
            return;
        }
        for (const auto& member_uuid : team->getMembers()) {
            const auto user = _all_clients.find(member_uuid);
            const std::string user_name = user != _all_clients.end() ? user->second : "";
            const int status = _getClientFromPseudo(user_name) != nullptr ? 1 : 0;

            dprintf(client.getSocket(), "100 SUB_USERS '%s' '%s' '%d'\n", member_uuid.c_str(), user_name.c_str(), status);
        }
    }
}