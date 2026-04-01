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
    class Client
    {
        private:
            u_int16_t port = 0;
        public:
            Client() = default;
            ~Client() = default;

            bool displayHelp(int argc, char *argv[]) const;
    };
}