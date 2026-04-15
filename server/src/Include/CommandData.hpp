/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** CommandData
*/

#pragma once

#include <string>
#include <vector>

namespace myTeams
{
    struct CommandData {
        std::string name;
        std::vector<std::string> args;
        int nb_args;
    };
}
