/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Server.hpp"

bool myTeams::Server::_is_running = false;

myTeams::Server::Server() : _network_server(_poll_fds, _nb_clients), _command(_hub, _online_clients, _all_clients), _parser(_command, _online_clients)
{
}

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
                    _parser.handleCommand(_poll_fds.getPollFDs()[i].fd);
            }
        }
    }
    save();
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
            file_team << "Name: " + team.second->getTeamName() + "\nDescription: " + team.second->getTeamDescription() + "\nClients allowed: ";
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
                file_channel << "Name: " + channel.second->getChannelName() + "\nDescription: " + channel.second->getChannelDescription() + "\n";
                file_channel.close();
            } else {
                std::cout << "Erreur lors de la sauvegarde des channels." << std::endl;
            }
            for (const auto &thread : channel.second->getThreads()) {
                std::filesystem::create_directories("Hub/Teams/" + team.second->getTeamUuid() + "/Channels/" + channel.second->getChannelUuid() + "/Threads/" + thread.second->getThreadUuid());
                file_thread.open("Hub/Teams/" + team.second->getTeamUuid() + "/Channels/" + channel.second->getChannelUuid() + "/Threads/" + thread.second->getThreadUuid() + "/data.txt", std::ios::out | std::ios::app);
                if (file_thread.is_open()) {
                    file_thread << "Title: " + thread.second->getThreadTitle() + "\nMessage: " + thread.second->getThreadMessage() + "\n";
                    file_thread.close();
                } else {
                    std::cout << "Erreur lors de la sauvegarde des threads." << std::endl;
                }
                file_replies.open("Hub/Teams/" + team.second->getTeamUuid() + "/Channels/" + channel.second->getChannelUuid() + "/Threads/" + thread.second->getThreadUuid() + "/replies.txt", std::ios::out | std::ios::app);
                if (file_replies.is_open()) {
                    for (const auto &reply : thread.second->getReplies()) {
                        file_replies << "Reply: " + reply.second + "\n";
                    }
                    file_replies.close();
                } else {
                    std::cout << "Erreur lors de la sauvegarde des reponses." << std::endl;
                }
            }
        }
    }
    for (const auto &client : _all_clients) {
        file_users.open("Hub/Users/" + client.second + ".txt", std::ios::out | std::ios::app);
        if (file_users.is_open()) {
            file_users << client.first;
            file_users.close();
        } else {
            std::cout << "Erreur lors de la sauvegarde des users." << std::endl;
            break;
        }
    }
}
