#include "HTMLElement.h"
#include "HTMLBuilder.h"

HTMLElement::HTMLElement(const std::string& name, const std::string& text)
    : name(name), text(text) {}

std::string HTMLElement::str(int indent) const {
    std::string i(indent_size * indent, ' ');
    std::string result = i + "<" + name + ">\n";

    if (text.size() > 0) {
        result += std::string(indent_size * (indent + 1), ' ') + text + "\n";
    }

    for (const auto& e : elements) {
        result += e.str(indent + 1);
    }

    result += i + "</" + name + ">\n";
    return result;
}

HTMLBuilder HTMLElement::build(const std::string& root_name) {
    return HTMLBuilder{root_name};
}
