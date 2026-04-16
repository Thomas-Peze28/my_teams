/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Server
*/

#include "Client.hpp"

myTeams::Client::Client()
{
    initRoutes();
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

void myTeams::Client::initRoutes()
{
    // ==========================================
    // 100-199 : USER MANAGEMENT
    // ==========================================
    _routes["100 LOGIN"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2)
            client_event_logged_in(args[0].c_str(), args[1].c_str());
    };
    _routes["101 LOGOUT"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2)
            client_event_logged_out(args[0].c_str(), args[1].c_str());
    };
    _routes["103 USERS"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_users(args[0].c_str(), args[1].c_str(), std::stoi(args[2]));
    };
    _routes["105 USER"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_user(args[0].c_str(), args[1].c_str(), std::stoi(args[2]));
    };

    // ==========================================
    // 200-299 : MESSAGE MANAGEMENT
    // ==========================================
    _routes["201 MSGS"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_private_message_print_messages(args[0].c_str(), (time_t)std::stol(args[1]), args[2].c_str());
    };

    // ==========================================
    // 300-399 : SUBSCRIPTION MANAGEMENT
    // ==========================================
    _routes["300 SUB_OK"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2)
            client_print_subscribed(args[0].c_str(), args[1].c_str());
    };
    _routes["301 UNSUB_OK"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2)
            client_print_unsubscribed(args[0].c_str(), args[1].c_str());
    };
    _routes["302 SUB_TEAMS"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_teams(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };
    _routes["303 SUB_USERS"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_users(args[0].c_str(), args[1].c_str(), std::stoi(args[2]));
    };

    // ==========================================
    // 400-499 : TEAM MANAGEMENT
    // ==========================================
    _routes["400 TEAM_CREATED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_team_created(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };
    _routes["401 TEAM"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_teams(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };
    _routes["402 USER_INFO"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_user(args[0].c_str(), args[1].c_str(), std::stoi(args[2]));
    };

    // ==========================================
    // 500-599 : CHANNEL MANAGEMENT
    // ==========================================
    _routes["500 CHANNEL_CREATED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_channel_created(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };
    _routes["501 CHANNEL"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_team_print_channels(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };
    _routes["502 TEAM_INFO"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_team(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };

    // ==========================================
    // 600-699 : THREAD MANAGEMENT
    // ==========================================
    _routes["600 THREAD_CREATED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 5)
            client_print_thread_created(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str(), args[4].c_str());
    };
    _routes["601 THREAD"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 5)
            client_channel_print_threads(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str(), args[4].c_str());
    };
    _routes["602 CHANNEL_INFO"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_print_channel(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };

    // ==========================================
    // 700-799 : REPLY MANAGEMENT
    // ==========================================
    _routes["700 REPLY_CREATED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 4)
            client_print_reply_created(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str());
    };
    _routes["701 REPLY"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 4)
            client_thread_print_replies(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str());
    };
    _routes["702 THREAD_INFO"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 5)
            client_print_thread(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str(), args[4].c_str());
    };

    // ==========================================
    // 950-959 : EVENT NOTIFICATIONS
    // ==========================================
    _routes["950 USER_LOGGED_IN"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2)
            client_event_logged_in(args[0].c_str(), args[1].c_str());
    };
    _routes["951 USER_LOGGED_OUT"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2)
            client_event_logged_out(args[0].c_str(), args[1].c_str());
    };
    _routes["952 PRIVATE_MESSAGE_RECEIVED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 2)
            client_event_private_message_received(args[0].c_str(), args[1].c_str());
    };
    _routes["953 TEAM_CREATED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_event_team_created(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };
    _routes["954 CHANNEL_CREATED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 3)
            client_event_channel_created(args[0].c_str(), args[1].c_str(), args[2].c_str());
    };
    _routes["955 THREAD_CREATED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 5)
            client_event_thread_created(args[0].c_str(), args[1].c_str(), (time_t)std::stol(args[2]), args[3].c_str(), args[4].c_str());
    };
    _routes["956 REPLY_CREATED"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 4)
            client_event_thread_reply_received(args[0].c_str(), args[1].c_str(), args[2].c_str(), args[3].c_str());
    };

    // ==========================================
    // 900-918 : ERROR CODE REFERENCE
    // ==========================================
    _routes["900 ALREADY_EXIST"] = [](const std::vector<std::string> &) {
            client_error_already_exist();
        };
    _routes["901 UNAUTHORIZED"] = [](const std::vector<std::string> &) {
            client_error_unauthorized();
        };
    _routes["902 UNAUTHORIZED"] = [](const std::vector<std::string> &) {
            client_error_unauthorized();
        };
    _routes["903 UNKNOWN_USER"] = [](const std::vector<std::string> &) {
            client_error_unknown_user("");
        };
    _routes["904 UNKNOWN_USER_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_user(args[0].c_str());
    };
    _routes["905 UNKNOWN_USER_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_user(args[0].c_str());
    };
    _routes["906 UNAUTHORIZED"] = [](const std::vector<std::string> &) {
        client_error_unauthorized();
    };
    _routes["907 UNKNOWN_USER_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_user(args[0].c_str());
    };
    _routes["908 UNAUTHORIZED"] = [](const std::vector<std::string> &) {
        client_error_unauthorized();
    };
    _routes["909 UNKNOWN_TEAM_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_team(args[0].c_str());
    };
    _routes["910 UNKNOWN_TEAM_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_team(args[0].c_str());
    };
    _routes["911 UNKNOWN_TEAM_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_team(args[0].c_str());
    };
    _routes["912 UNKNOWN_TEAM_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_team(args[0].c_str());
    };
    _routes["913 UNKNOWN_CHANNEL_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_channel(args[0].c_str());
    };
    _routes["914 UNKNOWN_CHANNEL_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_channel(args[0].c_str());
    };
    _routes["915 UNKNOWN_CHANNEL_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_channel(args[0].c_str());
    };
    _routes["916 UNKNOWN_THREAD_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_thread(args[0].c_str());
    };
    _routes["917 UNKNOWN_THREAD_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_thread(args[0].c_str());
    };
    _routes["918 UNKNOWN_THREAD_UUID"] = [](const std::vector<std::string> &args) {
        if (args.size() >= 1)
            client_error_unknown_thread(args[0].c_str());
    };

    // ==========================================
    // QUIET ROUTES
    // ==========================================
    _routes["000 LIST_START"] = [](const std::vector<std::string> &) {};
    _routes["999 LIST_END"] = [](const std::vector<std::string> &) {};
    _routes["001 Welcome to MyTeams!"] = [](const std::vector<std::string> &) {};
    _routes["002 *help menu*"] = [](const std::vector<std::string> &) {};
    _routes["200 SEND_OK"] = [](const std::vector<std::string> &) {};
    _routes["800 CONTEXT_SET"] = [](const std::vector<std::string> &) {};
}

void myTeams::Client::processServerMessage(const std::string &message)
{
    std::string key = message;
    size_t quotePos = message.find('\'');
    if (quotePos != std::string::npos) {
        key = message.substr(0, quotePos);
    }
    
    while (!key.empty() && std::isspace(key.back())) {
        key.pop_back();
    }

    auto it = _routes.find(key);
    if (it != _routes.end()) {
        std::vector<std::string> args = extractArgs(message);
        it->second(args);
    } else {
        std::cout << "[ERROR] Unhandled message from server: " << message << std::endl;
    }
    
}

bool myTeams::Client::handleServerInput()
{
    std::string buffer(1024, '\0');
    ssize_t bytesRead = recv(_serverSocket, &buffer[0], buffer.size(), 0);

    if (bytesRead > 0) {
        buffer.resize(bytesRead);
        processServerMessage(buffer);
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