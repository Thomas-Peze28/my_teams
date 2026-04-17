/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Thread
*/

#include "Thread.hpp"

myTeams::Thread::Thread(std::string thread_name, std::string thread_description)
{
    uuid_t uuid;
    char uuid_str[37];

    uuid_generate(uuid);
    uuid_unparse(uuid, uuid_str);
    this->_thread_uuid = std::string(uuid_str);
    this->_thread_name = thread_name;
    this->_thread_description = thread_description;
}