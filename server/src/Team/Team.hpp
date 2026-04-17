/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Team
*/

#pragma once

    #include "IContainer.hpp"
    #include "Channel.hpp"

    #include <string>
    #include <map>
    #include <memory>
    #include <uuid/uuid.h>
    #include <vector>
    #include <algorithm>

namespace myTeams
{
    class Team : public IContainer
    {
        public:
            Team(std::string team_name, std::string team_description);
            ~Team() override = default;

            void create(__attribute_maybe_unused__ std::string content, __attribute_maybe_unused__ std::string metadata) override {};
            void list() const override {};
            void info() const override {};

            //Setters
            void addMember(const std::string user_uuid) { _members.push_back(user_uuid); };
            void removeMember(const std::string user_uuid) { _members.erase(std::remove(_members.begin(), _members.end(), user_uuid), _members.end()); };

            // Getters
            std::string getUuid() const { return _team_uuid; };
            std::string getName() const { return _team_name; };
            std::string getDescription() const { return _team_description; };
            const std::vector<std::string>& getMembers() const { return _members; };
            Channel *getChannel(const std::string channel_uuid) const;
            bool isMember(const std::string user_uuid) const;


        private:
            std::string _team_uuid = "";
            std::string _team_name = "";
            std::string _team_description = "";

            std::vector<std::string> _members = {};
            std::map<std::string, std::unique_ptr<Channel>> _channels = {};
    };
}