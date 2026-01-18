#include "HTMLBuilder.h"

HTMLBuilder::HTMLBuilder(const std::string& root_name) {
    root.name = root_name;
}

HTMLBuilder& HTMLBuilder::add_child(const std::string& child_name, const std::string& child_text) {
    root.elements.emplace_back(child_name, child_text);
    return *this;
}

std::string HTMLBuilder::str() const {
    return root.str();
}
