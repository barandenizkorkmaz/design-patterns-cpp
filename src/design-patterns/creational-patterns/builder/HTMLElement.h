#pragma once

#include <string>
#include <vector>

// Forward declaration
class HTMLBuilder;

class HTMLElement {
private:
    std::string name;
    std::string text;
    std::vector<HTMLElement> elements;
    const size_t indent_size = 2;

    // Allow HTMLBuilder to access private members
    friend class HTMLBuilder;

public:
    HTMLElement() = default;
    HTMLElement(const std::string& name, const std::string& text);

    std::string str(int indent = 0) const;

    // Static factory method that returns a builder
    static HTMLBuilder builder(const std::string& root_name);
};
