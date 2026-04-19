/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Team
*/

#pragma once

    #include "IContainer.hpp"
    #include "Thread.hpp"

    #include <string>
    #include <map>
    #include <memory>
    #include <uuid/uuid.h>
    #include <vector>

namespace myTeams
{
    class Channel : public IContainer
    {
        public:
            Channel() = default;
            Channel(std::string channel_name, std::string channel_description);
            ~Channel() override = default;

            const Thread *getThread(const std::string &thread_uuid) const;
            const std::map<std::string, std::unique_ptr<Thread>> &getThreads() const { return _threads; }
            void create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description) override;
            void list() const override;
            void info() const override;
            std::string getChannelUuid() const { return _channel_uuid; }
            std::string getChannelName() const { return _channel_name; }
            std::string getChannelDescription() const { return _channel_description; }
            std::map<std::string, std::unique_ptr<Thread>> &getThreads() { return _threads; }
            
            void setChannelUuid(const std::string& uuid) { _channel_uuid = uuid; }
            void setChannelName(const std::string& name) { _channel_name = name; }
            void setChannelDescription(const std::string& desc) { _channel_description = desc; }
        
        private:
            std::string _channel_uuid = "";
            std::string _channel_name = "";
            std::string _channel_description = "";

            std::map<std::string, std::unique_ptr<Thread>> _threads = {};
    };
}