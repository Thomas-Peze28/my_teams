/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Channel
*/

#include "Channel.hpp"

const myTeams::Thread *myTeams::Channel::getThread(const std::string &thread_uuid) const
{
    auto it = _threads.find(thread_uuid);
    if (it != _threads.end())
        return it->second.get();
    return nullptr;
}

void myTeams::Channel::create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description)
{
}

void myTeams::Channel::list() const
{
}

void myTeams::Channel::info() const
{
}