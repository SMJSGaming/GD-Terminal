#include "CommandExecuter.hpp"

TerminalCout CommandExecuter::m_cout = TerminalCout();

void CommandExecuter::initialize(std::string line) {
    CommandExecuter::m_cout.empty();

    try {
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
                if (CommandExecuter::m_commands.find(word) != CommandExecuter::m_commands.end()) {
                    command = CommandExecuter::m_commands.at(word);
                } else {
                    throw std::invalid_argument("Unknown command: " + word);
                }
            } else if (quote) {
                std::string& flag = global ? globalValue : lastValue;

                CommandExecuter::handleQuotedString(type, word, quote, flag);

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

                CommandExecuter::handleQuotedString(type, word.substr(1), quote = word[0], flag);

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
                } else if (flagWord == "help") {
                    CommandExecuter::create(CommandExecuter::m_commands.at("help"), { { "*", command->m_name } });

                    return;
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
                    } else if (flag == 'h') {
                        CommandExecuter::create(CommandExecuter::m_commands.at("help"), { { "*", command->m_name } });

                        return;
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
            throw std::invalid_argument("Unexpected end of line while looking for matching `" + quote + '`');
        } else {
            CommandExecuter::create(command, flags);
        }
    } catch (const std::invalid_argument& exception) {
        CommandExecuter::m_cout << exception.what();
        CommandExecuter::finished();
    }
}

CommandExecuter* CommandExecuter::create(Command* command, flags_t flags) {
    CommandExecuter* instance = new CommandExecuter(command, flags);

    if (instance) {
        return instance;
    } else {
        CC_SAFE_DELETE(instance);

        return nullptr;
    }
}

void CommandExecuter::handleQuotedString(FlagType type, std::string word, char& quote, std::string& flagValue) {
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

void CommandExecuter::finished() {
    BetterTextArea* history = static_cast<BetterTextArea*>(gd::m_menuLayer->getChildByTag(HISTORY));

    CommandExecuter::m_cout << TerminalCout::endl << TerminalCout::space;
    CommandExecuter::m_cout >> history;

    reposition_elements();
}

CommandExecuter::CommandExecuter(Command* command, flags_t flags) {
    this->m_command = command;
    command->m_finished = false;

    command->run(CommandExecuter::m_cout, flags);

    if (command->m_async) {
        CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
    } else {
        this->finished();
    }
}

void CommandExecuter::update(float) {
    if (this->m_command->m_finished) {
        CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
        this->finished();
    }
}