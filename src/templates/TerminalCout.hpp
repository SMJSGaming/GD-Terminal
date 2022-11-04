#pragma once

#include <concepts>
#include "../includes.hpp"
#include "BetterTextArea.hpp"

// Not going to support float and bool keys. Simply because you have some screws loose if you use those.
template<class T>
concept SupportedKeyType = std::is_same_v<T, std::string> ||
    std::is_same_v<T, const std::string> ||
    std::is_same_v<T, char> ||
    std::is_same_v<T, const char> ||
    std::is_same_v<T, const char*> ||
    (std::is_integral_v<T> && !std::is_same_v<T, bool>);

template<class T>
concept SupportedType = SupportedKeyType<T> || std::is_floating_point_v<T> || std::is_same_v<T, bool> || std::is_same_v<T, const bool>;

template<class T>
concept IterableContainer = requires(const T& t) {
    t.begin();
    t.end();
    typename T::value_type;
} && SupportedType<typename T::value_type> && !std::is_same_v<T, std::string>;

template<class T>
concept IterableMap = requires(const T& t) {
    t.begin();
    t.end();
    typename T::key_type;
    typename T::mapped_type;
} && SupportedType<typename T::mapped_type> && SupportedKeyType<typename T::key_type>;

struct TerminalCout {
    static const char endl = '\n';
    static const char space = ' ';

    template<class T> requires SupportedType<T>
    friend TerminalCout& operator<<(TerminalCout& cout, T val) {
        cout.m_appendedStream << val;

        return cout;
    }

    template<class T> requires IterableContainer<T>
    friend TerminalCout& operator<<(TerminalCout& cout, const T& iterable) {
        bool first = true;

        cout.m_appendedStream << "[ ";

        for (const auto& val : iterable) {
            if (first) {
                first = false;
            } else {
                cout.m_appendedStream << ", ";
            }

            cout.m_appendedStream << val;
        }

        cout.m_appendedStream << " ]";

        return cout;
    }

    template<class T> requires IterableMap<T>
    friend TerminalCout& operator<<(TerminalCout& cout, const T& map) {
        bool first = true;

        cout.m_appendedStream << "[" << std::endl;

        for (auto& [key, val] : map) {
            if (first) {
                first = false;
            } else {
                cout.m_appendedStream << "," << std::endl;
            }

            cout.m_appendedStream << "  " << "{ " << key << ": " << val << " }";
        }

        cout.m_appendedStream << std::endl << "]";

        return cout;
    }

    friend TerminalCout& operator>>(TerminalCout& cout, BetterTextArea*& textArea) {
        textArea->pushLine(cout.m_appendedStream.str().c_str());

        return cout;
    }
protected:
    std::stringstream m_appendedStream;
};