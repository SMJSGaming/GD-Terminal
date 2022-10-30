#include "Command.hpp"

std::string Command::initialize(std::string line) {
    std::stringstream stream(line);
    Command* command = nullptr;
    char quote = NULL;
    flags_t flags { { "*", "" } };

    // TODO: Check for syntax errors in quotes
    // TODO: Handle 1 word quoted strings
    // TODO: Remove escapes

    for (std::string word; std::getline(stream, word, ' ');) {
        const unsigned int length = word.length();

        if (!command && length) {
            if (Command::m_commands.find(word) != Command::m_commands.end()) {
                command = Command::m_commands.at(word);
            } else {
                return "Unknown command `" + word + '`';
            }
        } else if (quote) {
            std::string error = Command::handleQuotedString(word, quote, flags.at(flags.rbegin()->first).append(" "));

            if (!error.empty()) {
                return error;
            }
        } else if (word[0] == '"' || word[0] == '\'' || word[0] == '`') {
            std::reverse_iterator<flags_t::iterator> last = flags.rbegin();
            std::string error = Command::handleQuotedString(word.erase(0, 1), quote = word[0], last->second.empty() ? flags.at(last->first) : flags.at("*"));

            if (!error.empty()) {
                return error;
            }
        } else if (word.find("--", 0) == 0) {
            std::string flagWord = word.substr(2, word.length() - 2);

            if (std::find_if(command->m_flags.begin(), command->m_flags.end(), [&](const documented_flag_t& flag) {
                return std::get<1>(flag) == flagWord;
            }) != command->m_flags.end()) {
                flags.insert({ flagWord, "" });
            }
        } else if (word[0] == '-') {
            for (unsigned int i = 1; i < length; i++) {
                if (std::find_if(command->m_flags.begin(), command->m_flags.end(), [&](const documented_flag_t& flag) {
                    return std::get<0>(flag) == word[i];
                }) != command->m_flags.end()) {
                    flags.insert({ std::string(1, word[i]), "" });
                }
            }
        } else if (length) {
            std::reverse_iterator<flags_t::iterator> last = flags.rbegin();

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
        std::cout << stream.eof() << std::endl;
        index += quoted.size();
        
        if (!escaped) {
            return "Unexpected end of string";
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