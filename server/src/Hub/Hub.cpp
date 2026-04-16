/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Hub
*/

#include "Hub.hpp"

const myTeams::Team *myTeams::Hub::getTeam(const std::string &team_uuid) const
{
    auto it = _teams.find(team_uuid);
    if (it != _teams.end())
        return it->second.get();
    return nullptr;
}

void myTeams::Hub::create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description)
{
}

void myTeams::Hub::list() const
{
}

void myTeams::Hub::info() const
{
}