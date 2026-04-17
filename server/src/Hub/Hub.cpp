/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Hub
*/

#include "Hub.hpp"

myTeams::Team *myTeams::Hub::getTeam(const std::string team_uuid) const
{
    auto it = _teams.find(team_uuid);
    if (it != _teams.end())
        return it->second.get();
    return nullptr;
}