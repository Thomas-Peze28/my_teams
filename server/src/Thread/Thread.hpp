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
            Thread(std::string thread_name, std::string thread_description);
            ~Thread() override = default;

            void create(__attribute_maybe_unused__ std::string content, __attribute_maybe_unused__ std::string metadata) override {};
            void list() const override {};
            void info() const override {};

            // Getters
            std::string getUuid() const { return _thread_uuid; };
            std::string getName() const { return _thread_name; };
            std::string getDescription() const { return _thread_description; };


        private:
            std::string _thread_uuid = "";
            std::string _thread_name = "";
            std::string _thread_description = "";

            std::vector<std::string> _replies = {};
    };
}