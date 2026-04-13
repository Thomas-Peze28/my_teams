/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** AComponent
*/

#pragma once

    #include <string>

namespace myTeams
{
    class AComponent
    {
        public:
            virtual ~AComponent() = 0;

            virtual void create(std::string content, std::string metadata) = 0;
            virtual void list() const = 0;
            virtual void info() const = 0;
    };
}