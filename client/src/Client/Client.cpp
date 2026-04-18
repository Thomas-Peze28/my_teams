/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Client.hpp"

myTeams::Client::Client()
{
}

myTeams::Client::~Client()
{
     if (_serverSocket != -1) {
        close(_serverSocket);
    }
}

bool myTeams::Client::displayHelp(int argc, char *argv[]) const
{
    for (unsigned int i = 0; argv[i] != NULL; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            std::cout << "USAGE: ./myteams_cli IP PORT" << std::endl;
            std::cout << "IP is the IP address of the server." << std::endl;
            std::cout << "PORT is the port number on which the client connects." << std::endl;
            return true;
        }
    }

    if (argc != 3) {
        std::cout << "USAGE: ./myteams_cli IP PORT" << std::endl;
        return true;
    }
    return false;
}

bool myTeams::Client::connectToServer()
{
    sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr(_ip.c_str());
    adress.sin_port = htons(_port);

    if (connect(_serverSocket, (sockaddr *)&adress, sizeof(adress)) == -1) {
        return false;
    }
    return true;
}

void myTeams::Client::initClient(const std::string &ip, uint16_t port)
{
    _ip = ip;
    _port = port;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1) {
        std::cout << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!connectToServer()) {
        std::cout << "Failed to connect to server" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected to server at " << _ip << ":" << _port << std::endl;
}

bool myTeams::Client::handleUserInput()
{
    std::string input;
    std::getline(std::cin, input);

    if (input == "exit") {
        _isRunning = false;
        std::cout << "[INFO] You've been disconnected." << std::endl;
        return true;
    }

    std::string message = input + "\n";
    send(_serverSocket, message.c_str(), message.size(), 0);
    return true;
}

std::vector<std::string> myTeams::Client::extractArgs(const std::string &message)
{
    std::vector<std::string> args;
    size_t pos = 0;

    while ((pos = message.find('\'', pos)) != std::string::npos) {
        size_t endPos = message.find('\'', pos + 1);
        if (endPos == std::string::npos)
            break;
        args.push_back(message.substr(pos + 1, endPos - pos - 1));
        pos = endPos + 1;
    }
    return args;
}

void myTeams::Client::processServerMessage(const std::string &message)
{
    if (message.length() < 3)
        return;

    int code = 0;

    try {
        code = std::stoi(message.substr(0, 3));
    } catch (const std::invalid_argument &e) {
        std::cout << message << std::endl;
        return;
    }

    std::vector<std::string> args = extractArgs(message);

    int code_category = code / 100;

    switch (code_category) {
        case 0:
            break;
        case 1:
            handleUserActions(code, message, args);
            break;
        case 2:
            handleCreations(code, message, args);
            break;
        case 3:
            handleInfos(code, message, args);
            break;
        case 4:
            handleListings(code, message, args);
            break;
        case 5:
            handleErrors(code, message, args);
            break;
        case 6:
            handleEvents(code, message, args);
            break;
        case 9:
            break;
        default:
            std::cout << "[ERROR] Unhandled code: " << message << std::endl;
            break;
    }
}

void myTeams::Client::handleUserActions(int code, const std::string &msg, const std::vector<std::string> &args)
{
    if (code == 100) {
        if (msg.find("LOGIN") != std::string::npos && args.size() >= 2) {
            client_event_logged_in(args[0].c_str(), args[1].c_str());
        }
        else if (msg.find("LOGOUT") != std::string::npos && args.size() >= 2) {
            client_event_logged_out(args[0].c_str(), args[1].c_str());
        }
        else if (msg.find("USERS") != std::string::npos && args.size() >= 3) {
            client_print_users(args[0].c_str(), args[1].c_str(), std::stoi(args[2]));
        }
        else if (msg.find("USER ") != std::string::npos && args.size() >= 3) {
            client_print_user(args[0].c_str(), args[1].c_str(), std::stoi(args[2]));
        }
        else if (msg.find("MSGS") != std::string::npos && args.size() >= 3) {
            client_private_message_print_messages(args[0].c_str(), (time_t)std::stol(args[1]), args[2].c_str());
        }
        else if (msg.find("SUB_OK") != std::string::npos && args.size() >= 2) {
            client_print_subscribed(args[0].c_str(), args[1].c_str());
        }
        else if (msg.find("UNSUB_OK") != std::string::npos && args.size() >= 2) {
            client_print_unsubscribed(args[0].c_str(), args[1].c_str());
        }
        else if (msg.find("SUB_TEAMS") != std::string::npos && args.size() >= 3) {
            client_print_teams(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("SUB_USERS") != std::string::npos && args.size() >= 3) {
            client_print_users(args[0].c_str(), args[1].c_str(), std::stoi(args[2]));
        }
        else {
            std::cout << "[ERROR] Unhandled 1xx code: " << msg << std::endl;
        }
    }
}

void myTeams::Client::handleCreations(int code, const std::string &msg, const std::vector<std::string> &args)
{
    if (code == 200) {
        if (msg.find("TEAM_CREATED") != std::string::npos && args.size() >= 3) {
            client_print_team_created(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("CHANNEL_CREATED") != std::string::npos && args.size() >= 3) {
            client_print_channel_created(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("THREAD_CREATED") != std::string::npos && args.size() >= 5) {
            client_print_thread_created(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str(), args[4].c_str());
        }
        else if (msg.find("REPLY_CREATED") != std::string::npos && args.size() >= 4) {
            client_print_reply_created(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str());
        }
        else {
            std::cout << "[ERROR] Unhandled 2xx code: " << msg << std::endl;
        }
    }
}

void myTeams::Client::handleInfos(int code, const std::string &msg, const std::vector<std::string> &args)
{
    if (code == 300) {
        if (msg.find("USER_INFO") != std::string::npos && args.size() >= 3) {
            client_print_user(args[0].c_str(), args[1].c_str(), std::stoi(args[2]));
        }
        else if (msg.find("TEAM_INFO") != std::string::npos && args.size() >= 3) {
            client_print_team(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("CHANNEL_INFO") != std::string::npos && args.size() >= 3) {
            client_print_channel(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("REPLY_INFO") != std::string::npos && args.size() >= 4) {
            client_print_thread(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), "", args[3].c_str());
        }
        else {
            std::cout << "[ERROR] Unhandled 3xx code: " << msg << std::endl;
        }
    }
}

void myTeams::Client::handleListings(int code, const std::string &msg, const std::vector<std::string> &args)
{
    if (code == 400) {
        if (msg.find("LIST_TEAM") != std::string::npos && args.size() >= 3) {
            client_print_teams(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("LIST_CHANNEL") != std::string::npos && args.size() >= 3) {
            client_team_print_channels(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("LIST_THREAD") != std::string::npos && args.size() >= 5) {
            client_channel_print_threads(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str(), args[4].c_str());
        }
        else if (msg.find("LIST_REPLY") != std::string::npos && args.size() >= 4) {
            client_thread_print_replies(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str());
        }
        else {
            std::cout << "[ERROR] Unhandled 4xx code: " << msg << std::endl;
        }
    }
}

void myTeams::Client::handleErrors(int code, const std::string &msg, const std::vector<std::string> &args)
{
    const char *arg1 = nullptr;

    if (args.empty()) {
        arg1 = "";
    } else {
        arg1 = args[0].c_str();
    }

    if (code == 500) {
        if (msg.find("UNKNOWN_USER") != std::string::npos) {
            client_error_unknown_user(arg1);
        }
        else if (msg.find("UNKNOWN_TEAM") != std::string::npos) {
            client_error_unknown_team(arg1);
        }
        else if (msg.find("UNKNOWN_CHANNEL") != std::string::npos) {
            client_error_unknown_channel(arg1);
        }
        else if (msg.find("UNKNOWN_THREAD") != std::string::npos) {
            client_error_unknown_thread(arg1);
        }
        else if (msg.find("ALREADY_EXIST") != std::string::npos) {
            client_error_already_exist();
        }
        else if (msg.find("UNAUTHORIZED") != std::string::npos) {
            client_error_unauthorized();
        }
        else {
            std::cout << "[ERROR] Unhandled 5xx error: " << msg << std::endl;
        }
    }
}

void myTeams::Client::handleEvents(int code, const std::string &msg, const std::vector<std::string> &args)
{
    if (code == 600) {
        if (msg.find("EVT_LOGGED_IN") != std::string::npos && args.size() >= 2) {
            client_event_logged_in(args[0].c_str(), args[1].c_str());
        }
        else if (msg.find("EVT_LOGGED_OUT") != std::string::npos && args.size() >= 2) {
            client_event_logged_out(args[0].c_str(), args[1].c_str());
        }
        else if (msg.find("EVT_MSG_RECEIVED") != std::string::npos && args.size() >= 2) {
            client_event_private_message_received(args[0].c_str(), args[1].c_str());
        }
        else if (msg.find("EVT_TEAM_CREATED") != std::string::npos && args.size() >= 3) {
            client_event_team_created(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("EVT_CHAN_CREATED") != std::string::npos && args.size() >= 3) {
            client_event_channel_created(args[0].c_str(), args[1].c_str(), args[2].c_str());
        }
        else if (msg.find("EVT_THREAD_CREATED") != std::string::npos && args.size() >= 5) {
            client_event_thread_created(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str(), args[4].c_str());
        }
        else if (msg.find("EVT_REPLY_CREATED") != std::string::npos && args.size() >= 5) {
            client_event_thread_reply_received(args[0].c_str(), args[1].c_str(), args[2].c_str(), args[4].c_str());
        }
        else {
            std::cout << "[ERROR] Unhandled 6xx event: " << msg << std::endl;
        }
    }
}

bool myTeams::Client::handleServerInput()
{
    std::string buffer(1024, '\0');
    ssize_t bytesRead = recv(_serverSocket, &buffer[0], buffer.size(), 0);

    if (bytesRead > 0) {
        buffer.resize(bytesRead);
        std::stringstream ss(buffer);
        std::string line;
        while (std::getline(ss, line, '\n')) {
            if (!line.empty()) {
                processServerMessage(line);
            }
        }
        return true;
    } else if (bytesRead == 0) {
        std::cout << "[INFO] Server closed the connection." << std::endl;
        _isRunning = false;
        return false;
    } else {
        std::cout << "[ERROR] Failed to receive data from server." << std::endl;
        return false;
    }
}

void myTeams::Client::run()
{
    _isRunning = true;
    std::cout << "Client is running. Type 'exit' to quit." << std::endl;

    std::vector<struct pollfd> fds(2);
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = _serverSocket;
    fds[1].events = POLLIN;

    while (_isRunning) {
        int pollResult = poll(fds.data(), fds.size(), -1);

        if (pollResult < 0) {
            std::cerr << "[ERROR] poll have failed." << std::endl;
            break;
        }

        if (fds[0].revents & POLLIN) {
            handleUserInput();
        }

        if (fds[1].revents & POLLIN) {
            handleServerInput();
        }

        if (fds[1].revents & (POLLHUP | POLLERR)) {
            std::cout << "[INFO] Server closed the connection." << std::endl;
            _isRunning = false;
        }
    }
}