#include <iostream>
#include "HTMLElement.h"
#include "HTMLBuilder.h"

using namespace std;

int main() {
    // Approach 1: Traditional builder usage
    cout << "=== Approach 1: Traditional Builder ===" << endl;
    HTMLBuilder builder("ul");
    builder.add_child("li", "Hello");
    builder.add_child("li", "World");
    cout << builder.str() << endl;

    // Approach 2: Fluent interface (method chaining)
    cout << "=== Approach 2: Fluent Interface ===" << endl;
    HTMLBuilder fluent_builder{"ul"};
    fluent_builder.add_child("li", "hello").add_child("li", "world");
    cout << fluent_builder.str() << endl;

    // Approach 3: Using static factory method with fluent interface
    cout << "=== Approach 3: Static Factory + Fluent ===" << endl;
    HTMLElement static_builder = HTMLElement::build("ul")
        .add_child("li", "First")
        .add_child("li", "Second");
    cout << static_builder.str() << endl;

    return 0;
}
