# AGENTS.md - clibus Development Guide

This file provides guidelines and commands for agents working on the clibus codebase.

## Project Structure

```
clibus/
├── include/clibus/     # Public headers
│   └── clibus.h
├── src/                # Source code
│   ├── clibus.cpp
│   └── main.cpp
├── test/               # Test code
│   └── clibus_test.cpp
├── external/          # External dependencies
│   ├── cpp-httplib-0.38.0/
│   └── googletest-1.17.0/
├── build/              # Build output (gitignored)
└── CMakeLists.txt
```

## Build Commands

### Full Build (from project root)

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

### Build Targets

```bash
cmake --build .                  # Build everything
cmake --build . --target clibus           # Build main executable
cmake --build . --target clibus_core     # Build core library
cmake --build . --target clibus_test     # Build test executable
```

### Running the Application

```bash
./build/clibus
```

### Running Tests

```bash
# Using ctest (discovers tests automatically via gtest_discover_tests)
cd build
ctest --output-on-failure

# Or run test executable directly
./build/clibus_test
```

### Running a Single Test

```bash
# Method 1: Using gtest filter
./build/clibus_test --gtest_filter=PrintHelpTest.PrintsClibus

# Method 2: Using ctest with regex
cd build
ctest -R PrintHelpTest
```

### Clean Build

```bash
rm -rf build && mkdir build && cd build && cmake .. && cmake --build .
```

## Code Style Guidelines

### General Principles

- **No comments** unless explicitly required by the user
- Use **4 spaces** for indentation (no tabs)
- Keep lines under **100 characters** when practical
- Use **C++14** standard

### Naming Conventions

| Element | Style | Example |
|---------|-------|---------|
| Classes | PascalCase | `HttpClient`, `MyClass` |
| Functions | snake_case | `print_help()`, `create_client()` |
| Variables | snake_case | `base_url`, `response_body` |
| Constants | kCamelCase | `kMaxRetries` |
| Headers | snake_case | `http_client.h`, `my_class.h` |
| Namespaces | snake_case | `clibus`, `testing` |

### File Organization

**Headers** (`include/clibus/`):
- One class per file when possible
- Include guards: `CLIBUS_<FILE_NAME>_H`
- Order: standard lib → third-party → project headers
- Use `#include "clibus/xxx.h"` for project headers

**Sources** (`src/`):
- Implementation files paired with headers

### Types

- Use `std::string` instead of C-style strings
- Use `std::unique_ptr` for ownership, `std::shared_ptr` for shared ownership
- Use `const` wherever possible (const parameters, const member functions)
- Prefer value semantics unless performance requires references

### Error Handling

- Use return codes or result types for error conditions
- Avoid exceptions unless absolutely necessary

### Testing

- Test files go in `test/` directory
- Use Google Test (gtest) framework
- Test naming: `TEST(TestSuite, MethodName_Behavior)`
- Use `extern` declarations to access library functions from tests:
  ```cpp
  extern void print_help();
  ```

### Dependencies

- **httplib**: HTTP client library (header-only), located in `external/cpp-httplib-0.38.0/`
- **gtest**: Testing framework, located in `external/googletest-1.17.0/`
- Dependencies are managed via external directories, NOT FetchContent

### Import Guidelines

```cpp
// Order: standard lib → third-party → project
#include <string>
#include <memory>

#include "httplib.h"

#include "clibus/clibus.h"
```

### Class Definition Order

1. Public types/constants
2. Public constructors/destructor
3. Public methods
4. Protected members (if any)
5. Private members (if any)

### Gtest Usage

```cpp
#include <gtest/gtest.h>

// Use gtest_main provided by gtest_main library
// Do NOT write main() in test files
TEST(TestSuite, TestName) {
    // Arrange
    // Act
    // Assert
    EXPECT_EQ(actual, expected);
}
```

### CMake Best Practices

- Always check if external directories exist before adding subdirectories
- Use `find_package` first, fallback to local external directories
- Add include directories conditionally based on existence
- Use target-specific includes when possible instead of global `include_directories`

### Adding New Source Files

When adding new source files:

1. Add header to `include/clibus/`
2. Add implementation to `src/`
3. Update `CMakeLists.txt` - add source to `add_library` or `add_executable`
4. Rebuild: `cmake --build .`

### Adding Tests

1. Add test file to `test/` directory
2. Use `extern` to declare functions from clibus_core
3. Link against `clibus_core` and `gtest_main` in CMakeLists.txt
4. Tests are automatically discovered via `gtest_discover_tests`
