/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Team
*/

#include "Team.hpp"

myTeams::Team::Team(std::string team_name, std::string team_description)
{
    uuid_t uuid;
    char uuid_str[37];

    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    this->_team_uuid = std::string(uuid_str);
    this->_team_name = team_name;
    this->_team_description = team_description;
}

const myTeams::Channel *myTeams::Team::getChannel(const std::string &channel_uuid) const
{
    auto it = _channels.find(channel_uuid);
    if (it != _channels.end())
        return it->second.get();
    return nullptr;
}

bool myTeams::Team::isMember(const std::string &user_uuid) const
{
    for (const auto& member : _members) {
        if (member == user_uuid)
            return true;
    }
    return false;
}

void myTeams::Team::addMember(const std::string& uuid)
{
    if (!isMember(uuid)) {
        _members.push_back(uuid);
    }
}

void myTeams::Team::removeMember(const std::string& uuid)
{
    auto it = std::find(_members.begin(), _members.end(), uuid);
    if (it != _members.end()) {
        _members.erase(it);
    }
}
void myTeams::Team::create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description)
{
}

void myTeams::Team::list() const
{
}

void myTeams::Team::info() const
{
}