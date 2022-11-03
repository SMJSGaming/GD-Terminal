#include "Command.hpp"

std::string Command::initialize(std::string line) {
    std::stringstream stream(line);
    Command* command = nullptr;
    flags_t flags { { "*", "" } };
    std::vector<char> quotes { '"', '\'', '`' };
    char quote = NULL;
    bool global = false;

    for (std::string word; std::getline(stream, word, ' ');) {
        const unsigned int length = word.size();

        if (!command && length) {
            if (Command::m_commands.find(word) != Command::m_commands.end()) {
                command = Command::m_commands.at(word);
            } else {
                return "Unknown command `" + word + '`';
            }
        } else if (quote) {
            std::string& flag = global ? flags.at("*") : flags.at(flags.rbegin()->first);
            std::string error = Command::handleQuotedString(word, quote, flag);

            if (!error.empty()) {
                return error;
            } else if (global || quote) {
                flag.append(" ");
            } else if (!quote) {
                global = false;
            }
        } else if (std::count(quotes.begin(), quotes.end(), word[0])) {
            std::reverse_iterator<flags_t::iterator> last = flags.rbegin();
            global = last->second.empty();
            std::string& flag = global ? flags.at(last->first) : flags.at("*");
            std::string error = Command::handleQuotedString(word.erase(0, 1), quote = word[0], flag);

            if (!error.empty()) {
                return error;
            } else if (global || quote) {
                flag.append(" ");
            } else if (!quote) {
                global = false;
            }
        } else if (word.find("--", 0) == 0) {
            std::string flagWord = word.substr(2, word.size() - 2);

            if (std::find_if(command->m_flags.begin(), command->m_flags.end(), [&](const documented_flag_t& flag) {
                return std::get<1>(flag) == flagWord;
            }) != command->m_flags.end()) {
                flags.insert({ flagWord, "" });
            }
        } else if (word[0] == '-') {
            for (const char& flag : word) {
                if (std::find_if(command->m_flags.begin(), command->m_flags.end(), [&](const documented_flag_t& documented_flag) {
                    return std::get<0>(documented_flag) == flag;
                }) != command->m_flags.end()) {
                    flags.insert({ std::string(1, flag), "" });
                }
            }
        } else if (length) {
            std::reverse_iterator<flags_t::iterator> last = flags.rbegin();

            for (const char& quote : quotes) {
                if (word.find(quote) != std::string::npos) {
                    std::stringstream substream(word);
                    unsigned int index = 0;

                    for (std::string quoted; std::getline(substream, quoted, quote);) {
                        if ((index += quoted.size()) < word.size()) {
                            if (quoted.back() != '\\') {
                                return "Unexpected start of quoted string";
                            } else {
                                word.erase(index - 1, 1);
                            }
                        }
                    }
                }
            }

            if (!last->second.size()) {
                flags.at(last->first) = word;
            } else {
                flags.at("*").append(word).append(" ");
            }
        }
    }

    if (quote) {
        std::string error = "Unexpected end of line while looking for matching `";

        error.push_back(quote);

        return error.append("`");
    } else {
        return command->run(flags);
    }
}

std::string Command::handleQuotedString(std::string word, char& quote, std::string& flagValue) {
    std::stringstream stream(word);
    bool escaped = word.size() > 1;
    unsigned int index = 0;

    for (std::string quoted; std::getline(stream, quoted, quote);) {
        index += quoted.size();
        
        if (!escaped) {
            return "Unexpected end of quoted string";
        }

        if (escaped = quoted.back() == '\\') {
            word.erase(index - 1, 1);
        }
    }

    if (!escaped && word.back() == quote) {
        quote = NULL;
        flagValue.append(word.substr(0, word.length() - 1));
    } else {
        flagValue.append(word);
    }

    return "";
}

Command::Command(std::string name, std::string description, documented_flags_t flags) {
    this->m_name = name;
    this->m_description = description;
    this->m_flags = flags;

    Command::m_commands.insert({ this->m_name, this });
}

std::string Command::run(flags_t flags) {
    return "Command `" + this->m_name + "` has not been implemented yet";
}