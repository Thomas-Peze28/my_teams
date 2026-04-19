/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Team
*/

#pragma once

    #include "IContainer.hpp"

    #include <string>
    #include <map>
    #include <memory>
    #include <uuid/uuid.h>
    #include <vector>

namespace myTeams
{
    class Thread : public IContainer
    {
        public:
            Thread() = default;
            Thread(std::string thread_name, std::string thread_description);
            ~Thread() override = default;

            void create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description) override;
            void list() const override;
            void info() const override;
            std::string getThreadUuid() const { return _thread_uuid; }
            std::string getThreadName() const { return _thread_name; }
            std::string getThreadDescription() const { return _thread_description; }
            std::map<std::string, std::string> getReplies() const { return _replies; }
            
            void setThreadUuid(const std::string& uuid) { _thread_uuid = uuid; }
            void setThreadName(const std::string& name) { _thread_name = name; }
            void setThreadDescription(const std::string& description) { _thread_description = description; }
            void addReply(const std::string& reply_uuid, const std::string& reply_msg) { _replies[reply_uuid] = reply_msg; }

        private:
            std::string _thread_uuid = "";
            std::string _thread_name = "";
            std::string _thread_description = "";

            std::map<std::string, std::string> _replies = {};
    };
}