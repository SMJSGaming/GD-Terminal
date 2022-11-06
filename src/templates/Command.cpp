#include "Command.hpp"

void Command::initialize(TerminalCout& cout, std::string line) {
    const std::vector<char> quotes { '"', '\'', '`' };
    std::stringstream stream(line);
    Command* command = nullptr;
    flags_t flags { { "*", "" } };
    std::vector<std::string> keys { "*" };
    std::string& globalValue = flags.at("*");
    FlagType type = FlagType::VOID_TYPE;
    char quote = NULL;
    bool global = false;

    for (std::string word; std::getline(stream, word, ' ');) {
        const unsigned int length = word.size();
        const std::string lastKey = *keys.rbegin();
        std::string& lastValue = flags.at(lastKey);

        if (!command && length) {
            if (Command::m_commands.find(word) != Command::m_commands.end()) {
                command = Command::m_commands.at(word);
            } else {
                throw std::invalid_argument("Unknown command: " + word);
            }
        } else if (quote) {
            std::string& flag = global ? globalValue : lastValue;

            Command::handleQuotedString(type, word, quote, flag);

            if (quote) {
                if (global) {
                    flag.append(" ");
                }
            } else {
                type = FlagType::VOID_TYPE;
                global = false;
            }
        } else if (std::count(quotes.begin(), quotes.end(), word[0])) {
            std::string& flag = (global = lastValue.empty() && lastKey != "*" && type != FlagType::VOID_TYPE) ? lastValue : globalValue;

            Command::handleQuotedString(type, word.substr(1), quote = word[0], flag);

            if (quote) {
                if (global) {
                    flag.append(" ");
                }
            } else {
                type = FlagType::VOID_TYPE;
                global = false;
            }
        } else if (word.find("--", 0) == 0) {
            std::string flagWord = word.substr(2);

            if (std::find_if(command->m_flags.begin(), command->m_flags.end(), [&](const documented_flag_t& flag) {
                if (std::get<2>(flag) == flagWord) {
                    type = std::get<0>(flag);

                    return true;
                } else {
                    return false;
                }
            }) != command->m_flags.end()) {
                flags.insert({ flagWord, "" });
                keys.push_back(flagWord);
            }
        } else if (word[0] == '-') {
            std::string flagWord = word.substr(1);

            for (const char& flag : flagWord) {
                if (std::find_if(command->m_flags.begin(), command->m_flags.end(), [&](const documented_flag_t& documented_flag) {
                    if (std::get<1>(documented_flag) == flag) {
                        type = std::get<0>(documented_flag);

                        return true;
                    } else {
                        return false;
                    }
                }) != command->m_flags.end()) {
                    std::string key(1, flag);

                    flags.insert({ key, "" });
                    keys.push_back(key);
                }
            }
        } else if (length) {
            for (const char& quote : quotes) {
                if (word.find(quote) != std::string::npos) {
                    std::stringstream substream(word);
                    unsigned int index = 0;

                    for (std::string quoted; std::getline(substream, quoted, quote);) {
                        if ((index += quoted.size()) < word.size()) {
                            if (quoted.back() != '\\') {
                                throw std::invalid_argument("Unexpected end of quoted string");
                            } else {
                                word.erase(index - 1, 1);
                            }
                        }
                    }
                }
            }

            switch (type) {
                case FlagType::VOID_TYPE: {
                    if (globalValue.size()) {
                        globalValue.append(" ");
                    }

                    globalValue.append(word);
                } break;
                case FlagType::BOOL_TYPE: {
                    Command::parseBool(word);
                }
                case FlagType::INT_TYPE: {
                    Command::parseInt(word);
                }
                case FlagType::FLOAT_TYPE: {
                    Command::parseFloat(word);
                }
                default: {
                    lastValue.append(word);
                }
            }

            type = FlagType::VOID_TYPE;
        }
    }

    if (quote) {
        cout << "Unexpected end of line while looking for matching `" << quote << '`';
    } else {
        command->run(cout, flags);
    }
}

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
    } catch (const std::invalid_argument& exception) {
        UNUSED(exception);
        throw std::invalid_argument("Expected an integer value");
    } catch (const std::out_of_range& exception) {
        UNUSED(exception);
        throw std::invalid_argument("Integer value out of range");
    }
}

float Command::parseFloat(std::string value) {
    try {
        return std::stof(value);
    } catch (const std::invalid_argument& exception) {
        UNUSED(exception);
        throw std::invalid_argument("Expected a float value");
    } catch (const std::out_of_range& exception) {
        UNUSED(exception);
        throw std::invalid_argument("Float value out of range");
    }
}

void Command::handleQuotedString(FlagType type, std::string word, char& quote, std::string& flagValue) {
    std::stringstream stream(word);
    bool escaped = word.size() > 1;
    unsigned int index = 0;

    for (std::string quoted; std::getline(stream, quoted, quote);) {
        index += quoted.size();
        
        if (!escaped) {
            throw std::invalid_argument("Unexpected end of quoted string");
        }

        if (escaped = quoted.back() == '\\') {
            word.erase(index - 1, 1);
        }
    }

    if (!escaped && word.back() == quote) {
        quote = NULL;
        flagValue.append(word.substr(0, word.length() - 1));

        switch (type) {
            case FlagType::BOOL_TYPE: {
                Command::parseBool(flagValue);
            }
            case FlagType::INT_TYPE: {
                Command::parseInt(flagValue);
            }
            case FlagType::FLOAT_TYPE: {
                Command::parseFloat(flagValue);
            }
        }
    } else {
        flagValue.append(word);
    }
}

Command::Command(std::string name, std::string description, documented_flags_t flags) {
    this->m_name = name;
    this->m_description = description;
    this->m_flags = flags;

    Command::m_commands.insert({ this->m_name, this });
}

void Command::run(TerminalCout& cout, flags_t flags) {
    cout << std::string("Command `" + this->m_name + "` has not been implemented yet");
}