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
            Team() = default;
            Team(std::string team_name, std::string team_description);
            ~Team() override = default;

            bool isAvailableClient(std::string uuid) const;
            const Channel *getChannel(const std::string &channel_uuid) const;
            void create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description) override;
            void list() const override;
            void info() const override;
            std::string getTeamUuid() const { return _team_uuid; }
            std::string getTeamName() const { return _team_name; }
            std::string getTeamDescription() const { return _team_description; }
            std::map<std::string, std::unique_ptr<Channel>> &getChannels() { return _channels; }
            std::vector<std::string> &getAvailableUuids() { return _members; }
            
            std::string getUuid() const { return _team_uuid; }
            std::string getName() const { return _team_name; }
            std::string getDescription() const { return _team_description; }
            std::vector<std::string> getMembers() const { return _members; }
            
            bool isMember(const std::string& uuid) const;
            void addMember(const std::string& uuid);
            void removeMember(const std::string& uuid);
            
            void setTeamUuid(const std::string& uuid) { _team_uuid = uuid; }
            void setTeamName(const std::string& name) { _team_name = name; }
            void setTeamDescription(const std::string& desc) { _team_description = desc; }
            void addAvailableUuid(const std::string& uuid) { _members.push_back(uuid); }
        
        private:
            std::string _team_uuid = "";
            std::string _team_name = "";
            std::string _team_description = "";

            std::vector<std::string> _members = {};
            std::map<std::string, std::unique_ptr<Channel>> _channels = {};
    };
}