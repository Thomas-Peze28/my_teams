/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Channel
*/

#include "Channel.hpp"


myTeams::Channel::Channel(std::string channel_name, std::string channel_description)
{
    uuid_t uuid;
    char uuid_str[37];

    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    this->_channel_uuid = std::string(uuid_str);
    this->_channel_name = channel_name;
    this->_channel_description = channel_description;
}

myTeams::Thread *myTeams::Channel::getThread(const std::string thread_uuid) const
{
    auto it = _threads.find(thread_uuid);
    if (it != _threads.end())
        return it->second.get();
    return nullptr;
}