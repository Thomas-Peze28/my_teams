/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

myTeams::Server::Server() : _network_server(_poll_fds, _nb_clients), _command(_online_clients, _all_clients, _hub), _parser(_command)
{
}

bool myTeams::Server::_is_running = false;

bool myTeams::Server::displayHelp(int argc, char *argv[]) const
{
    for (unsigned int i = 0; argv[i] != NULL; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << "USAGE: ./myteams_server PORT" << std::endl;
            std::cout << "PORT is the port number on which the server socket listens." << std::endl;
            return true;
        }
    }
    if (argc != 2) {
        std::cout << "USAGE: ./myteams_server PORT" << std::endl;
        return true;
    }
    return false;
}

void myTeams::Server::disconnectClient(int client_socket)
{
    _online_clients.erase(client_socket);
    _poll_fds.deleteClient(client_socket);
    _nb_clients--;
}

void myTeams::Server::signalHandler(int signal)
{
    if (signal == SIGINT)
        _is_running = false;
}

void myTeams::Server::runServer()
{
    std::signal(SIGINT, signalHandler);
    std::cout << "Server is running on port : " << _network_server.getServerPort() << std::endl;
    _is_running = true;
    while (_is_running)  {
        if (poll(_poll_fds.getPollFDs(), MAX_CLIENTS + 1, 350) < 0)
            continue;
        if (_poll_fds.getPollFDs()[0].revents & POLLIN) {
            std::pair<int, std::unique_ptr<myTeams::Client>> new_client = _network_server.acceptNewConnection();
            if (new_client.first != -1) {
                _nb_clients++;
                _online_clients[new_client.first] = std::move(new_client.second);
            }
        }
        for (unsigned int i = 1; i < MAX_CLIENTS + 1; i++) {
            if (_poll_fds.getPollFDs()[i].fd == -1)
                continue;
            if (_poll_fds.getPollFDs()[i].revents & (POLLHUP | POLLERR | POLLNVAL)) {
                disconnectClient(_poll_fds.getPollFDs()[i].fd);
                continue;
            }
            if (_poll_fds.getPollFDs()[i].revents & POLLIN) {
                if (_parser.isClientDisconnected(_poll_fds.getPollFDs()[i].fd))
                    disconnectClient(_poll_fds.getPollFDs()[i].fd);
                else
                    _parser.handleCommand(*_online_clients[_poll_fds.getPollFDs()[i].fd]);
            }
        }
    }
    save();
}

void myTeams::Server::initServer(uint16_t port)
{
    _network_server.initNetworkServer(port);

    if (!std::filesystem::exists("Hub")) {
        return;
    }
    if (std::filesystem::exists("Hub/Teams")) {
        loadTeams();
    }
    if (std::filesystem::exists("Hub/Users")) {
        loadUsers();
    }
}

void myTeams::Server::loadTeams()
{
    for (const auto& team_entry : std::filesystem::directory_iterator("Hub/Teams")) {
        if (!team_entry.is_directory())
            continue;

        std::string team_uuid = team_entry.path().filename().string();
        std::string team_data_path = team_entry.path().string() + "/data.txt";

        if (!std::filesystem::exists(team_data_path))
            continue;

        auto team = std::make_unique<Team>();
        team->setTeamUuid(team_uuid);
        std::fstream team_file(team_data_path, std::ios::in);

        if (team_file.is_open()) {
            std::string line;
            int line_count = 0;
            while (std::getline(team_file, line)) {
                if (line_count == 0) {
                    team->setTeamName(line);
                } else if (line_count == 1) {
                    team->setTeamDescription(line);
                } else if (line_count == 2) {
                    std::string uuids_line = line;
                    size_t pos = 0;
                    while ((pos = uuids_line.find(' ')) != std::string::npos) {
                        std::string uuid = uuids_line.substr(0, pos);
                        if (!uuid.empty()) {
                            team->addAvailableUuid(uuid);
                        }
                        uuids_line.erase(0, pos + 1);
                    }
                    if (!uuids_line.empty()) {
                        team->addAvailableUuid(uuids_line);
                    }
                }
                line_count++;
            }
            team_file.close();
        }

        std::string channels_path = team_entry.path().string() + "/Channels";
        loadChannels(*team, channels_path);
        _hub.getTeams()[team_uuid] = std::move(team);
    }
}

void myTeams::Server::loadChannels(Team &team, const std::string &channels_path)
{
    if (!std::filesystem::exists(channels_path)) {
        return;
    }

    for (const auto& channel_entry : std::filesystem::directory_iterator(channels_path)) {
        if (!channel_entry.is_directory())
            continue;

        std::string channel_uuid = channel_entry.path().filename().string();
        std::string channel_data_path = channel_entry.path().string() + "/data.txt";

        if (!std::filesystem::exists(channel_data_path))
            continue;

        auto channel = std::make_unique<Channel>();
        channel->setChannelUuid(channel_uuid);

        std::fstream channel_file(channel_data_path, std::ios::in);
        if (channel_file.is_open()) {
            std::string line;
            int line_count = 0;
            while (std::getline(channel_file, line)) {
                if (line_count == 0) {
                    channel->setChannelName(line);
                } else if (line_count == 1) {
                    channel->setChannelDescription(line);
                }
                line_count++;
            }
            channel_file.close();
        }

        std::string threads_path = channel_entry.path().string() + "/Threads";
        loadThreads(*channel, threads_path);
        team.getChannels()[channel_uuid] = std::move(channel);
    }
}

void myTeams::Server::loadThreads(Channel &channel, const std::string &threads_path)
{
    if (!std::filesystem::exists(threads_path)) {
        return;
    }

    for (const auto& thread_entry : std::filesystem::directory_iterator(threads_path)) {
        if (!thread_entry.is_directory())
            continue;

        std::string thread_uuid = thread_entry.path().filename().string();
        std::string thread_data_path = thread_entry.path().string() + "/data.txt";
        std::string replies_path = thread_entry.path().string() + "/replies.txt";

        if (!std::filesystem::exists(thread_data_path))
            continue;

        auto thread = std::make_unique<Thread>();
        thread->setThreadUuid(thread_uuid);

        std::fstream thread_file(thread_data_path, std::ios::in);
        if (thread_file.is_open()) {
            std::string line;
            int line_count = 0;
            while (std::getline(thread_file, line)) {
                if (line_count == 0) {
                    thread->setThreadTitle(line);
                } else if (line_count == 1) {
                    thread->setThreadMessage(line);
                }
                line_count++;
            }
            thread_file.close();
        }

        if (std::filesystem::exists(replies_path)) {
            std::fstream replies_file(replies_path, std::ios::in);
            if (replies_file.is_open()) {
                std::string line;
                int reply_count = 0;
                while (std::getline(replies_file, line)) {
                    std::string reply_uuid = "reply_" + std::to_string(reply_count++);
                    thread->addReply(reply_uuid, line);
                }
                replies_file.close();
            }
        }

        channel.getThreads()[thread_uuid] = std::move(thread);
    }
}

void myTeams::Server::loadUsers()
{
    for (const auto& user_entry : std::filesystem::directory_iterator("Hub/Users")) {
        if (!user_entry.is_regular_file())
            continue;

        std::string filename = user_entry.path().filename().string();
        if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".txt") {
            std::string user_uuid = filename.substr(0, filename.length() - 4);

            std::fstream file(user_entry.path().string(), std::ios::in);
            if (file.is_open()) {
                std::string user_pseudo;
                if (std::getline(file, user_pseudo)) {
                    _all_clients[user_pseudo] = user_uuid;
                }
                file.close();
            }
        }
    }
}

void myTeams::Server::save()
{
    std::fstream file_team;
    std::fstream file_channel;
    std::fstream file_thread;
    std::fstream file_replies;
    std::fstream file_users;

    for (const auto &team : _hub.getTeams()) {
        std::filesystem::create_directories("Hub/Teams/" + team.second->getTeamUuid());
        file_team.open("Hub/Teams/" + team.second->getTeamUuid() + "/data.txt", std::ios::out | std::ios::app);
        if (file_team.is_open()) {
            file_team << team.second->getTeamName() + "\n" + team.second->getTeamDescription() + "\n";
            for (const auto &uuid : team.second->getAvailableUuids()) {
                file_team << uuid << " ";
            }
            file_team << "\n";
            file_team.close();
        } else {
            std::cout << "Erreur lors de la sauvegarde des teams." << std::endl;
        }
        for (const auto &channel : team.second->getChannels()) {
            std::filesystem::create_directories("Hub/Teams/" + team.second->getTeamUuid() + "/Channels/" + channel.second->getChannelUuid());
            file_channel.open("Hub/Teams/" + team.second->getTeamUuid() + "/Channels/" + channel.second->getChannelUuid() + "/data.txt", std::ios::out | std::ios::app);
            if (file_channel.is_open()) {
                file_channel << channel.second->getChannelName() + "\n" + channel.second->getChannelDescription() + "\n";
                file_channel.close();
            } else {
                std::cout << "Erreur lors de la sauvegarde des channels." << std::endl;
            }
            for (const auto &thread : channel.second->getThreads()) {
                std::filesystem::create_directories("Hub/Teams/" + team.second->getTeamUuid() + "/Channels/" + channel.second->getChannelUuid() + "/Threads/" + thread.second->getThreadUuid());
                file_thread.open("Hub/Teams/" + team.second->getTeamUuid() + "/Channels/" + channel.second->getChannelUuid() + "/Threads/" + thread.second->getThreadUuid() + "/data.txt", std::ios::out | std::ios::app);
                if (file_thread.is_open()) {
                    file_thread << thread.second->getThreadTitle() + "\n" + thread.second->getThreadMessage() + "\n";
                    file_thread.close();
                } else {
                    std::cout << "Erreur lors de la sauvegarde des threads." << std::endl;
                }
                file_replies.open("Hub/Teams/" + team.second->getTeamUuid() + "/Channels/" + channel.second->getChannelUuid() + "/Threads/" + thread.second->getThreadUuid() + "/replies.txt", std::ios::out | std::ios::app);
                if (file_replies.is_open()) {
                    for (const auto &reply : thread.second->getReplies()) {
                        file_replies << reply.second + "\n";
                    }
                    file_replies.close();
                } else {
                    std::cout << "Erreur lors de la sauvegarde des reponses." << std::endl;
                }
            }
        }
    }
    for (const auto &client : _all_clients) {
        file_users.open("Hub/Users/" + client.first + ".txt", std::ios::out | std::ios::app);
        if (file_users.is_open()) {
            file_users << client.second;
            file_users.close();
        } else {
            std::cout << "Erreur lors de la sauvegarde des users." << std::endl;
            break;
        }
    }
}
