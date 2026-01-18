#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct HTMLElement {
    string name;
    string text;
    vector<HTMLElement> elements;
    const size_t indent_size = 2;

    HTMLElement() = default;
    HTMLElement(const string& name, const string& text) : name(name), text(text) {}

    string str(int indent = 0) const {
        string i(indent_size * indent, ' ');
        string result = i + "<" + name + ">\n";
        if (text.size() > 0) {
            result += string(indent_size * (indent + 1), ' ') + text + "\n";
        }

        for (const auto& e : elements) {
            result += e.str(indent + 1);
        }

        result += i + "</" + name + ">\n";
        return result;
    }
};

struct HTMLBuilder {
    HTMLElement root;

    HTMLBuilder(const string& root_name) {
        root.name = root_name;
    }

    void add_child(const string& child_name, const string& child_text) {
        root.elements.emplace_back(child_name, child_text);
    }

    string str() const {
        return root.str();
    }
};

int main() {
    HTMLBuilder builder("ul");
    builder.add_child("li", "Hello");
    builder.add_child("li", "World");
    cout << builder.str() << endl;
    return 0;
};