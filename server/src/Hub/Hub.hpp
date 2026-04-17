/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Hub
*/

#pragma once

    #include "IContainer.hpp"
    #include "Team.hpp"

    #include <map>
    #include <memory>

    extern "C" {
        #include "logging_server.h"
    }

namespace myTeams
{
    class Hub : public IContainer
    {
        public:
            Hub() = default;
            ~Hub() override = default;

            void create(__attribute_maybe_unused__ std::string content, __attribute_maybe_unused__ std::string metadata) override {};
            void list() const override {};
            void info() const override {};

            // Getters
            Team *getTeam(const std::string team_uuid) const;
            const std::map<std::string, std::unique_ptr<Team>>& getTeams() const { return _teams; };

        private:
            std::map<std::string, std::unique_ptr<Team>> _teams = {};
    };
}