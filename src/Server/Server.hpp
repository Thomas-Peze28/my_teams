/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#pragma once

    #include <iostream>
    #include <cstdlib>

namespace myTeams
{
    class Server
    {
        private:
            u_int16_t port = 0;
        public:
            Server() = default;
            ~Server() = default;

            bool displayHelp(int argc, char *argv[]) const;
    };
}