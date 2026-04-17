/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Thread
*/

#pragma once

    #include "IContainer.hpp"

    #include <string>
    #include <map>

namespace myTeams
{
    class Thread : public IContainer
    {
        public:
            Thread() = default;
            ~Thread() override = default;

            void create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description) override;
            void list() const override;
            void info() const override;
            std::string getThreadUuid() const { return thread_uuid; }
            std::string getThreadTitle() const { return thread_title; }
            std::string getThreadMessage() const { return thread_message; }
            std::map<std::string, std::string> getReplies() const { return _replies; }

        private:
            std::string thread_uuid = "";
            std::string thread_title = "";
            std::string thread_message = "";

            std::map<std::string, std::string> _replies = {};
    };
}