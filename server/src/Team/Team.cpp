/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Team
*/

#include "Team.hpp"

const myTeams::Channel *myTeams::Team::getChannel(const std::string &channel_uuid) const
{
    auto it = _channels.find(channel_uuid);
    if (it != _channels.end())
        return it->second.get();
    return nullptr;
}

bool myTeams::Team::isAvailableClient(std::string uuid) const
{
    for (const std::string& available_uuid : _available_uuids) {
        if (available_uuid == uuid)
            return true;
    }
    return false;
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