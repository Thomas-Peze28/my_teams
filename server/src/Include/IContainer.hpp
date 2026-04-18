/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** IContainer
*/

#pragma once

    #include <string>

namespace myTeams
{
    class IContainer
    {
        public:
            virtual ~IContainer() = default;

            virtual void create(std::string content, __attribute_maybe_unused__ std::string metadata) = 0;
            virtual void list() const = 0;
            virtual void info() const = 0;
    };
}