#include "Command.hpp"

bool Command::parseBool(std::string value) {
    if (value == "true" || value == "1") {
        return true;
    } else if (value == "false" || value == "0") {
        return false;
    } else {
        throw std::invalid_argument("Expected a boolean value");
    }
}

int Command::parseInt(std::string value) {
    try {
        return std::stoi(value);
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("Expected an integer value");
    } catch (const std::out_of_range&) {
        throw std::invalid_argument("Integer value out of range");
    }
}

float Command::parseFloat(std::string value) {
    try {
        return std::stof(value);
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("Expected a float value");
    } catch (const std::out_of_range&) {
        throw std::invalid_argument("Float value out of range");
    }
}

std::string Command::startPadding(std::string value, unsigned int length) {
    if (value.size() < length) {
        value.insert(0, length - value.size(), ' ');
    }

    return value;
}

std::string Command::endPadding(std::string value, unsigned int length) {
    if (value.size() < length) {
        value.append(length - value.size(), ' ');
    }

    return value;
}

Command::Command(std::string name, std::string description, std::pair<std::string, std::string> globalArgs, documented_flags_t flags, bool async) {
    this->m_async = async;
    this->m_finished = false;
    this->m_name = name;
    this->m_description = description;
    this->m_globalArgs = globalArgs;
    this->m_flags = flags;
}

void Command::run(TerminalCout& cout, flags_t flags) {
    cout << std::string("Command `" + this->m_name + "` has not been implemented yet");
}