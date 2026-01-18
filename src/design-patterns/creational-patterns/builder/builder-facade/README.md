# Builder Facade Pattern

This example demonstrates the **Builder Facade Pattern** - a variation of the builder pattern that uses multiple builder facades to build different aspects of a complex object.

## What It Does

Creates a `Person` object with address and job information using a fluent, readable interface:

```cpp
Person p = Person::create()
    .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
    .works().at("PragmaSoft").as_a("Consultant").earning(10e6);
```

---

## Project Structure

```
builder-facade/
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # This file
├── Facets.cpp                  # Main program with example usage
├── Person.h                    # Person class definition
├── Person.cpp                  # Person class implementation
├── PersonBuilder.h             # Main builder facade
├── PersonAddressBuilder.h      # Address-specific builder
└── PersonJobBuilder.h          # Job-specific builder
```

---

## Architecture

### 1. Person Class
- Contains address fields (street, postcode, city)
- Contains employment fields (company, position, income)
- Private constructor (can only be created via builder)
- Move semantics enabled

### 2. PersonBuilder (Main Facade)
- Entry point for building
- Returns specialized builders for different aspects

### 3. PersonAddressBuilder
- Builds address-related information
- Methods: `at()`, `with_postcode()`, `in()`

### 4. PersonJobBuilder
- Builds employment-related information
- Methods: `at()`, `as_a()`, `earning()`

---

## Building with CMake

### Quick Start (One Command)

```bash
# Configure, build, and run in one go
cmake -S . -B build && cmake --build build && ./build/bin/builder_facade
```

### Step-by-Step Build

#### 1. Configure the Project

```bash
# Create build directory and configure
cmake -S . -B build
```

**What this does:**
- `-S .` - Source directory is current directory
- `-B build` - Build directory is `build/`
- Generates build files (Makefiles on Linux/Mac, .sln on Windows)

#### 2. Build the Project

```bash
# Build the executable
cmake --build build
```

**Or with specific configuration:**
```bash
# Debug build
cmake --build build --config Debug

# Release build (optimized)
cmake --build build --config Release
```

#### 3. Run the Executable

```bash
# Run from build directory
./build/bin/builder_facade
```

---

## Alternative: Manual Compilation (Without CMake)

### Using g++

```bash
g++ -std=c++23 Facets.cpp Person.cpp -o builder_facade
./builder_facade
```

### Using clang++

```bash
clang++ -std=c++23 Facets.cpp Person.cpp -o builder_facade
./builder_facade
```

---

## Expected Output

```
Person created
street_address: 123 London Road post_code: SW1 1GB city: London company_name: PragmaSoft position: Consultant annual_income: 10000000
Person destroyed
```

---

## How the Pattern Works

### Step-by-Step Execution

1. **Create builder:**
   ```cpp
   Person::create()  // Returns PersonBuilder
   ```

2. **Switch to address builder:**
   ```cpp
   .lives()  // Returns PersonAddressBuilder
   ```

3. **Build address:**
   ```cpp
   .at("123 London Road")
   .with_postcode("SW1 1GB")
   .in("London")
   ```

4. **Switch to job builder:**
   ```cpp
   .works()  // Returns PersonJobBuilder
   ```

5. **Build job info:**
   ```cpp
   .at("PragmaSoft")
   .as_a("Consultant")
   .earning(10e6)
   ```

6. **Implicit conversion to Person:**
   ```cpp
   Person p = ...  // Uses move constructor
   ```

---

## Key C++ Features Used

### 1. Friend Classes
```cpp
friend class PersonBuilder;
friend class PersonAddressBuilder;
friend class PersonJobBuilder;
```
Allows builders to access Person's private members.

### 2. Move Semantics
```cpp
Person(Person&& other)  // Move constructor
Person& operator=(Person&& other)  // Move assignment
```
Efficient transfer of resources without copying.

### 3. Private Constructor
```cpp
private:
    Person() { }  // Can only be created by friend classes
```
Forces use of the builder pattern.

### 4. Fluent Interface
```cpp
PersonAddressBuilder& at(const std::string& address) {
    person.street_address = address;
    return *this;  // Returns reference for chaining
}
```

### 5. Operator Overloading
```cpp
friend std::ostream& operator<<(std::ostream& os, const Person& obj)
```
Enables printing with `cout << person`.

---

## Design Pattern Benefits

### ✅ Advantages:

1. **Separation of Concerns**: Address and job building are separate
2. **Fluent API**: Natural, readable syntax
3. **Type Safety**: Can't mix address and job methods inappropriately
4. **Flexibility**: Easy to add more builder facades
5. **Encapsulation**: Person construction is controlled

### ⚠️ Considerations:

1. **Complexity**: More classes than simple builder
2. **Learning Curve**: Need to understand facade relationships
3. **Friend Classes**: Breaks encapsulation slightly

---

## CMake Commands Reference

### Clean Build
```bash
# Remove build directory and rebuild
rm -rf build
cmake -S . -B build
cmake --build build
```

### Build with Verbose Output
```bash
cmake --build build --verbose
```

### Specify Generator (Optional)
```bash
# Use Ninja (faster)
cmake -S . -B build -G Ninja
cmake --build build

# Use Unix Makefiles
cmake -S . -B build -G "Unix Makefiles"
cmake --build build

# Use Xcode (macOS)
cmake -S . -B build -G Xcode
cmake --build build
```

### Build Types
```bash
# Debug (with debugging symbols)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Release (optimized)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# RelWithDebInfo (optimized + debug symbols)
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build
```

---

## Extending the Pattern

### Adding a New Facade (e.g., PersonContactBuilder)

1. **Create PersonContactBuilder.h:**
```cpp
#pragma once
#include "PersonBuilder.h"

class PersonContactBuilder : public PersonBuilderBase {
public:
    PersonContactBuilder(Person& person) : PersonBuilderBase(person) {}

    PersonContactBuilder& email(const std::string& email) {
        person.email = email;
        return *this;
    }

    PersonContactBuilder& phone(const std::string& phone) {
        person.phone = phone;
        return *this;
    }
};
```

2. **Add fields to Person.h:**
```cpp
class Person {
    std::string email, phone;
    friend class PersonContactBuilder;
};
```

3. **Add method to PersonBuilder:**
```cpp
PersonContactBuilder contact() {
    return PersonContactBuilder{person};
}
```

4. **Use it:**
```cpp
Person p = Person::create()
    .lives().at("123 Main St")
    .contact().email("john@example.com").phone("555-1234")
    .works().at("Company");
```

---

## Comparison with Other Builder Patterns

| Pattern | Example | Use Case |
|---------|---------|----------|
| **Simple Builder** | `builder.set_name("x").set_age(30)` | Single builder, simple objects |
| **Fluent Builder** | `HTMLElement::build("ul").add_child(...)` | Single builder, method chaining |
| **Builder Facade** | `.lives().at(...).works().at(...)` | Multiple aspects, complex objects |
| **Groovy-Style** | `P { IMG {"url"} }` | Declarative syntax, DSL |

---

## Troubleshooting

### Issue: CMake not found
```bash
# Install CMake
# macOS:
brew install cmake

# Ubuntu/Debian:
sudo apt-get install cmake

# Arch:
sudo pacman -S cmake
```

### Issue: Wrong C++ standard
```bash
# Check compiler version
g++ --version
clang++ --version

# C++23 requires:
# - GCC 11+
# - Clang 12+
# - MSVC 2022+
```

### Issue: Build fails
```bash
# Clean and rebuild
rm -rf build
cmake -S . -B build
cmake --build build --verbose
```

---

## Summary

The Builder Facade Pattern:
- Uses **multiple specialized builders** for different aspects of an object
- Provides a **fluent, domain-specific interface**
- Enforces **controlled construction** through private constructors
- Demonstrates **advanced C++ features** like friend classes, move semantics, and fluent APIs

This pattern is ideal for building complex objects with multiple, distinct aspects that benefit from being configured separately.