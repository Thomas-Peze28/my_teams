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
            Channel(std::string channel_name, std::string channel_description);
            ~Channel() override = default;

            void create(__attribute_maybe_unused__ std::string content, __attribute_maybe_unused__ std::string metadata) override {};
            void list() const override {};
            void info() const override {};
            
            // Getters
            std::string getUuid() const { return _channel_uuid; };
            std::string getName() const { return _channel_name; };
            std::string getDescription() const { return _channel_description; };
            Thread *getThread(const std::string thread_uuid) const;

        private:
            std::string _channel_uuid = "";
            std::string _channel_name = "";
            std::string _channel_description = "";

            std::map<std::string, std::unique_ptr<Thread>> _threads = {};
    };
}