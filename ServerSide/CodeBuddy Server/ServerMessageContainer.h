#pragma once
#include <string>
#include <cstring>

class ServerMessageContainer {
private:
    char _type{};
    std::string _Message{};

public:
    ServerMessageContainer() {}

    ServerMessageContainer(char type, const std::string& Message) : _type(type), _Message(Message) {}

    int getSize() {
        return _Message.size() + sizeof(int) + sizeof(char);
    }

    std::string getMess() {
        return _Message;
    }

    ServerMessageContainer(const char* buff) {
        _type = buff[0];
        int length;
        memcpy(&length, &buff[1], sizeof(int));
        _Message = std::string(buff + sizeof(int) + sizeof(char), length);
    }

    void cutFront(int i) {
        _Message = _Message.substr(2);
    }

    char getType() {
        return _type;
    }

    std::string getWholeString() {
        std::string buffer{};
        buffer += _type;
        int length = _Message.size();
        buffer.append(reinterpret_cast<char*>(&length), sizeof(int));
        buffer += _Message;
        return buffer;
    }
};