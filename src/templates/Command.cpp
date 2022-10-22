#include "Command.hpp"

std::unordered_map<std::string, Command*> Command::commands {};

std::string Command::initialize(std::string line) {
    std::stringstream stream(line);
    flags_t flags;
    Command* command = nullptr;
    char quote = NULL;
    
    for (std::string word; std::getline(stream, word, ' ');) {
        const unsigned int length = word.length();

        if (!command && length) {
            if (Command::commands.find(word) != Command::commands.end()) {
                command = Command::commands[word];
            } else {
                return "Unknown command `" + word + '`';
            }
        } else if (quote) {
            if (word.back() == quote && word[length - 2] != '\\') {
                quote = NULL;
                word = word.substr(0, length - 1);
            }

            flags.rbegin()->second += " " + word;
        } else if (word[0] == '"' || word[0] == '\'' || word[0] == '`') {
            std::string flagValue = flags.rbegin()->second;

            quote = word[0];

            if (flags.size() && !flagValue.size()) {
                flags.rbegin()->second = word.substr(1, length - 1);
            } else {
                flags.insert({ NULL, word.substr(1, length - 1) });
            }
        } else if (word.find("--", 0) == 0) {
            std::string flagWord = word.substr(2, word.length() - 2);

            if (std::find_if(command->flags.begin(), command->flags.end(), [&](const documented_flag_t& flag) {
                return std::get<1>(flag) == flagWord;
            }) != command->flags.end()) {
                flags.insert({ flagWord, "" });
            }
        } else if (word[0] == '-') {
            for (unsigned int i = 1; i < length; i++) {
                if (std::find_if(command->flags.begin(), command->flags.end(), [&](const documented_flag_t& flag) {
                    return std::get<0>(flag) == word[i];
                }) != command->flags.end()) {
                    flags.insert({ std::string(1, word[i]), "" });
                }
            }
        } else if (length) {
            if (flags.size() && !flags.rbegin()->second.size()) {
                flags.rbegin()->second = word;
            } else {
                flags.insert({ NULL, word });
            }
        }
    }

    if (quote) {
        return "Unexpected EOL while looking for matching `" + quote + '`';
    } else {
        return command->run(flags);
    }
}

Command::Command(std::string name, std::string description, documented_flags_t flags) {
    this->name = name;
    this->description = description;
    this->flags = flags;

    Command::commands[name] = this;
}