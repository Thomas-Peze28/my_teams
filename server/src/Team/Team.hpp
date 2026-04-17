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

namespace myTeams
{
    class Team : public IContainer
    {
        public:
            Team() = default;
            ~Team() override = default;

            bool isAvailableClient(std::string uuid) const;
            const Channel *getChannel(const std::string &channel_uuid) const;
            void create(__attribute_maybe_unused__ std::string team_name, __attribute_maybe_unused__ std::string team_description) override;
            void list() const override;
            void info() const override;
            std::string getTeamUuid() const { return team_uuid; }
            std::string getTeamName() const { return team_name; }
            std::string getTeamDescription() const { return team_description; }
            std::map<std::string, std::unique_ptr<Channel>> &getChannels() { return _channels; }
            std::vector<std::string> &getAvailableUuids() { return _available_uuids; }
            
            void setTeamUuid(const std::string& uuid) { team_uuid = uuid; }
            void setTeamName(const std::string& name) { team_name = name; }
            void setTeamDescription(const std::string& desc) { team_description = desc; }
            void addAvailableUuid(const std::string& uuid) { _available_uuids.push_back(uuid); }
        
        private:
            std::string team_uuid = "";
            std::string team_name = "";
            std::string team_description = "";

            std::map<std::string, std::unique_ptr<Channel>> _channels = {};
            std::vector<std::string> _available_uuids = {};
    };
}