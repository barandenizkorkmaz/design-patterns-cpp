#pragma once

#include "HTMLElement.h"
#include <string>

class HTMLBuilder {
private:
    HTMLElement root;

public:
    HTMLBuilder(const std::string& root_name);

    HTMLBuilder& add_child(const std::string& child_name, const std::string& child_text);

    std::string str() const;

    // Conversion operator: allows implicit conversion from HTMLBuilder to HTMLElement
    operator HTMLElement() const;
};
