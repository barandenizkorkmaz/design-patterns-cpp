# Groovy-Style Builder Pattern

This is an advanced builder pattern implementation that creates a **domain-specific language (DSL)** for building HTML in C++. It's called "Groovy-style" because it mimics the clean, declarative syntax of the Groovy programming language.

## What It Does

Creates HTML using elegant syntax like this:

```cpp
P {
  IMG {"http://pokemon.com/pikachu.png"}
}
```

Which outputs:
```html
<p>
  <img src="http://pokemon.com/pikachu.png"/>
</p>
```

---

## How to Compile and Run

```bash
g++ -std=c++23 main.cpp -o main
./main
```

**Expected Output:**
```html
<p>
<img src="http://pokemon.com/pikachu.png"/>
</p>
```

---

## Architecture Overview

### Key Components

1. **Base `Tag` Class** - Abstract base for all HTML tags
2. **Derived Tag Classes** - Specific implementations (P, IMG, etc.)
3. **Operator Overloading** - Makes printing elegant with `cout <<`
4. **Initializer Lists** - Enables the `{}` syntax for children
5. **Protected Constructors** - Enforces using specific tag types only

---

## Code Breakdown

### 1. Base Tag Class

```cpp
struct Tag {
    std::string name;        // Tag name (e.g., "p", "img")
    std::string text;        // Text content
    std::vector<Tag> children;  // Nested tags
    std::vector<std::pair<std::string, std::string>> attributes;  // Key-value pairs

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag);

protected:
    Tag(const std::string& name, const std::string& text);
    Tag(const std::string& name, const std::vector<Tag>& children);
};
```

**Why protected constructors?**
- You **cannot** create a Tag directly: `Tag t("p", "text");` ❌
- You **can only** create specific tag types like `P`, `IMG`
- Forces proper HTML structure

---

### 2. Output Operator (operator<<)

```cpp
friend std::ostream& operator<<(std::ostream& os, const Tag& tag) {
    os << "<" << tag.name;

    // Print attributes
    for (const auto& att : tag.attributes)
        os << " " << att.first << "=\"" << att.second << "\"";

    // Self-closing tag if no content
    if (tag.children.size() == 0 && tag.text.length() == 0) {
        os << "/>" << std::endl;
    }
    else {
        os << ">" << std::endl;

        if (tag.text.length())
            os << tag.text << std::endl;

        // Recursively print children
        for (const auto& child : tag.children)
            os << child;

        os << "</" << tag.name << ">" << std::endl;
    }

    return os;
}
```

**What it does:**
- Enables `cout << tag` syntax
- Handles self-closing tags (`<img/>`)
- Recursively prints nested children
- Formats attributes properly

---

### 3. The P (Paragraph) Class

```cpp
struct P : Tag {
    // Constructor 1: Text content
    explicit P(const std::string& text)
      : Tag{"p", text}
    {}

    // Constructor 2: Child tags
    P(std::initializer_list<Tag> children)
      : Tag("p", children)
    {}
};
```

**Two constructors allow different usage:**

**Text content:**
```cpp
P{"Hello World"}
// Output: <p>Hello World</p>
```

**Child elements:**
```cpp
P {
    IMG {"pikachu.png"}
}
// Output:
// <p>
//   <img src="pikachu.png"/>
// </p>
```

---

### 4. The IMG (Image) Class

```cpp
struct IMG : Tag {
    explicit IMG(const std::string& url)
      : Tag{"img", ""}
    {
        attributes.emplace_back(make_pair("src", url));
    }
};
```

**Creates image tags:**
```cpp
IMG {"http://example.com/image.png"}
// Output: <img src="http://example.com/image.png"/>
```

---

## The `explicit` Keyword

```cpp
explicit P(const std::string& text)
```

**What it does:** Prevents implicit type conversions.

### Without `explicit`:
```cpp
void print_paragraph(P p) {
    std::cout << p;
}

// This would be allowed (implicit conversion):
print_paragraph("Hello");  // String → P automatically
```

### With `explicit`:
```cpp
// This is NOT allowed:
print_paragraph("Hello");     // ❌ ERROR

// Must be explicit:
print_paragraph(P{"Hello"});  // ✅ OK
```

**Why use it?**
- ✅ Prevents accidental conversions
- ✅ Makes code more readable and intentional
- ✅ Clearer what type is being created

---

## How It Works - Step by Step

### Example:
```cpp
P {
  IMG {"http://pokemon.com/pikachu.png"}
}
```

**Execution flow:**

1. **Create IMG:**
   ```cpp
   IMG {"http://pokemon.com/pikachu.png"}
   ```
   - Calls `IMG::IMG(const std::string& url)`
   - Creates Tag with `name = "img"`
   - Adds attribute: `src = "http://pokemon.com/pikachu.png"`

2. **Create P with child:**
   ```cpp
   P { IMG {...} }
   ```
   - Calls `P::P(std::initializer_list<Tag> children)`
   - The `{...}` creates an initializer_list containing the IMG
   - Creates Tag with `name = "p"` and one child

3. **Print using `operator<<`:**
   ```cpp
   std::cout << P {...}
   ```
   - Calls the overloaded `operator<<`
   - Recursively prints the entire structure

**Output:**
```html
<p>
  <img src="http://pokemon.com/pikachu.png"/>
</p>
```

---

## Key C++ Features Used

### 1. Inheritance
```cpp
struct P : Tag  // P inherits from Tag
struct IMG : Tag
```

### 2. Initializer Lists
```cpp
P { IMG {"url"} }
// The {...} is std::initializer_list<Tag>
```

### 3. Friend Functions
```cpp
friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
```
Allows the function to access private/protected members.

### 4. Operator Overloading
```cpp
operator<<  // Makes cout << tag work
```

### 5. Protected Constructors
```cpp
protected:
    Tag(...)  // Can only be called by derived classes
```

### 6. `explicit` Keyword
```cpp
explicit P(const std::string& text)  // Prevents implicit conversions
```

---

## More Usage Examples

### Simple Paragraph
```cpp
P paragraph{"Hello World"};
cout << paragraph;
```
**Output:**
```html
<p>Hello World</p>
```

### Paragraph with Image
```cpp
P with_image {
    IMG {"pikachu.png"}
};
cout << with_image;
```
**Output:**
```html
<p>
  <img src="pikachu.png"/>
</p>
```

### Multiple Children
```cpp
P complex {
    IMG {"image1.png"},
    IMG {"image2.png"}
};
cout << complex;
```
**Output:**
```html
<p>
  <img src="image1.png"/>
  <img src="image2.png"/>
</p>
```

---

## Comparison: Traditional vs Groovy-Style

### Traditional Builder (fluent interface):
```cpp
auto builder = HTMLElement::build("p")
    .add_child("img", "")
    .set_attribute("src", "pikachu.png");
cout << builder.str();
```

### Groovy-Style Builder:
```cpp
cout << P {
    IMG {"pikachu.png"}
};
```

### Advantages of Groovy-Style:
- ✅ More declarative and readable
- ✅ Looks like actual HTML structure
- ✅ Less verbose
- ✅ Type-safe (each tag is its own class)
- ✅ Compile-time safety

### Disadvantages:
- ❌ Need to create a class for each HTML tag type
- ❌ Less flexible (can't create arbitrary tags dynamically)
- ❌ More boilerplate code
- ❌ Harder to add new tags (requires new classes)

---

## Extending the Pattern

To add a new HTML tag, create a new class:

```cpp
struct DIV : Tag {
    explicit DIV(const std::string& text)
      : Tag{"div", text}
    {}

    DIV(std::initializer_list<Tag> children)
      : Tag("div", children)
    {}
};

struct H1 : Tag {
    explicit H1(const std::string& text)
      : Tag{"h1", text}
    {}
};
```

**Usage:**
```cpp
cout << DIV {
    H1 {"Welcome"},
    P {
        IMG {"banner.png"}
    }
};
```

**Output:**
```html
<div>
  <h1>Welcome</h1>
  <p>
    <img src="banner.png"/>
  </p>
</div>
```

---

## Summary

This Groovy-style builder pattern:

1. Creates a **domain-specific language (DSL)** for HTML in C++
2. Uses **inheritance** to model HTML tag hierarchy
3. Uses **initializer lists** for clean `{}` syntax
4. Uses **operator overloading** for elegant printing
5. Uses **protected constructors** to enforce type safety
6. Uses **`explicit`** to prevent unintended conversions

The result is elegant, declarative code that resembles actual HTML structure while maintaining full C++ type safety!

---

## When to Use This Pattern

**Use Groovy-style builder when:**
- ✅ You have a fixed set of types to build (e.g., HTML tags)
- ✅ You want declarative, readable syntax
- ✅ Type safety is important
- ✅ The structure is hierarchical

**Use traditional builder when:**
- ✅ You need dynamic, runtime-determined structures
- ✅ You don't know types ahead of time
- ✅ You need maximum flexibility
- ✅ Adding new types should be easy
