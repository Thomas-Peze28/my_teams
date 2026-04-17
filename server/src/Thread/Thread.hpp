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
            
            void setThreadUuid(const std::string& uuid) { thread_uuid = uuid; }
            void setThreadTitle(const std::string& title) { thread_title = title; }
            void setThreadMessage(const std::string& message) { thread_message = message; }
            void addReply(const std::string& reply_uuid, const std::string& reply_msg) { _replies[reply_uuid] = reply_msg; }

        private:
            std::string thread_uuid = "";
            std::string thread_title = "";
            std::string thread_message = "";

            std::map<std::string, std::string> _replies = {};
    };
}