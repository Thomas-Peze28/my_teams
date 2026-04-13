/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** PoolFD
*/

#include "PollFD.hpp"


myTeams::PollFD::~PollFD()
{
    for (unsigned int i = 1; i <= MAX_CLIENTS; i++) {
        if (_poll_fds[i].fd != -1) {
            close(_poll_fds[i].fd);
            _poll_fds[i].fd = -1;
        }
    }
}

void myTeams::PollFD::deleteClient(int client_socket)
{
    for (unsigned int i = 1; i <= MAX_CLIENTS; i++)
        if (_poll_fds[i].fd == client_socket && _poll_fds[i].fd != -1) {
            close(_poll_fds[i].fd);
            _poll_fds[i].fd = -1;
            _poll_fds[i].events = 0;
            return;
        }
}

bool myTeams::PollFD::addNewClient(int client_socket)
{
    for (unsigned int i = 1; i <= MAX_CLIENTS; i++)
        if (_poll_fds[i].fd == -1) {
            _poll_fds[i].fd = client_socket;
            _poll_fds[i].events = POLLIN;
            return true;
        }
    return false;
}

void myTeams::PollFD::initPollFD(int server_socket)
{
    _poll_fds[0].fd = server_socket;
    _poll_fds[0].events = POLLIN;
    for (int i = 1; i <= MAX_CLIENTS; i++) {
        _poll_fds[i].fd = -1;
        _poll_fds[i].events = 0;
    }
}