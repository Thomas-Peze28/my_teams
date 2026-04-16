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

namespace myTeams
{
    class Hub : public IContainer
    {
        public:
            Hub() = default;
            ~Hub() override = default;

            void create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description) override;
            void list() const override;
            void info() const override;
        
            const Team *getTeam(const std::string &team_uuid) const;

        private:
            std::map<std::string, std::unique_ptr<Team>> _teams = {};
    };
}