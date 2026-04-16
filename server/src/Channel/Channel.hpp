/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Channel
*/

#pragma once

    #include "IContainer.hpp"

    #include <vector>
    #include <string>
    #include <map>
    #include <memory>
    #include "Thread.hpp"

namespace myTeams
{
    class Channel : public IContainer
    {
        public:
            Channel() = default;
            ~Channel() override = default;

            const Thread *getThread(const std::string &thread_uuid) const;
            void create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description) override;
            void list() const override;
            void info() const override;
        
        private:
            std::string channel_uuid = "";
            std::string channel_name = "";
            std::string channel_description = "";

            std::map<std::string, std::unique_ptr<Thread>> _threads = {};
    };
}