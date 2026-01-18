# Builder Pattern - HTML Builder Example

This example demonstrates the Builder design pattern using an HTML element builder.

## File Structure

```
builder/
├── HTMLElement.h       - HTMLElement class declaration
├── HTMLElement.cpp     - HTMLElement class implementation
├── HTMLBuilder.h       - HTMLBuilder class declaration
├── HTMLBuilder.cpp     - HTMLBuilder class implementation
├── main.cpp           - Example usage
└── README.md          - This file
```

## How to Compile

### Option 1: Manual Compilation (Step by Step)

```bash
# Compile each source file to object file
g++ -std=c++23 -c HTMLElement.cpp -o HTMLElement.o
g++ -std=c++23 -c HTMLBuilder.cpp -o HTMLBuilder.o
g++ -std=c++23 -c main.cpp -o main.o

# Link all object files together
g++ -std=c++23 HTMLElement.o HTMLBuilder.o main.o -o main
```

### Option 2: One-Line Compilation

```bash
g++ -std=c++23 HTMLElement.cpp HTMLBuilder.cpp main.cpp -o main
```

### Option 3: All in One (Compile and Run)

```bash
g++ -std=c++23 -c HTMLElement.cpp -o HTMLElement.o && \
g++ -std=c++23 -c HTMLBuilder.cpp -o HTMLBuilder.o && \
g++ -std=c++23 -c main.cpp -o main.o && \
g++ -std=c++23 HTMLElement.o HTMLBuilder.o main.o -o main
./main
```

## How to Run

After compilation, run the executable:

```bash
./main
```

## Expected Output

```
=== Approach 1: Traditional Builder ===
<ul>
  <li>
    Hello
  </li>
  <li>
    World
  </li>
</ul>

=== Approach 2: Fluent Interface ===
<ul>
  <li>
    hello
  </li>
  <li>
    world
  </li>
</ul>

=== Approach 3: Static Factory + Fluent ===
<ul>
  <li>
    First
  </li>
  <li>
    Second
  </li>
</ul>
```

## What the Pattern Demonstrates

### 1. Traditional Builder
```cpp
HTMLBuilder builder("ul");
builder.add_child("li", "Hello");
builder.add_child("li", "World");
cout << builder.str() << endl;
```

### 2. Fluent Interface (Method Chaining)
```cpp
HTMLBuilder fluent_builder{"ul"};
fluent_builder.add_child("li", "hello").add_child("li", "world");
cout << fluent_builder.str() << endl;
```

### 3. Static Factory Method + Fluent Interface
```cpp
auto static_builder = HTMLElement::build("ul")
    .add_child("li", "First")
    .add_child("li", "Second");
cout << static_builder.str() << endl;
```

## Key Concepts

- **Builder Pattern**: Separates object construction from its representation
- **Fluent Interface**: Methods return `*this` to enable method chaining
- **Forward Declaration**: `HTMLBuilder` is forward-declared in `HTMLElement.h`
- **const member functions**: `str()` is const - doesn't modify the object
- **emplace_back**: Constructs elements directly in the vector (efficient!)

## Clean Up

```bash
# Remove object files
rm *.o

# Remove executable
rm main
```
