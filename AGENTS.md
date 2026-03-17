# AGENTS.md - clibus Development Guide

This file provides guidelines and commands for agents working on the clibus codebase.

## Project Structure

```
clibus/
├── include/clibus/     # Public headers
│   ├── i_http_client.h
│   └── http_client.h
├── src/                # Source code
│   ├── clibus.cpp
│   ├── clibus.h
│   ├── http_client.cpp
│   └── main.cpp
├── test/               # Test code
│   ├── clibus_test.cpp
│   └── mock_http_client.h
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
cmake --build .              # Build everything
cmake --build . --target clibus       # Build main executable
cmake --build . --target clibus_core # Build core library
cmake --build . --target clibus_test  # Build test executable
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
| Classes | PascalCase | `HttpClient`, `IHttpClient` |
| Functions | camelCase | `print_help()`, `createHttpClient()` |
| Variables | camelCase | `base_url`, `response_body` |
| Constants | kCamelCase | `kMaxRetries` |
| Headers | snake_case | `http_client.h`, `i_http_client.h` |
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

### Interfaces

- Define interfaces in headers with `I` prefix (e.g., `IHttpClient`)
- Use abstract base classes with virtual destructor
- Provide factory functions for creation (e.g., `createHttpClient()`)
- Return interfaces via `std::unique_ptr<IInterface>`

### Error Handling

- Use return codes or result types for error conditions
- Avoid exceptions unless absolutely necessary
- Provide error messages in `HttpResponse.error` field

### Testing

- Test files go in `test/` directory
- Use Google Test (gtest) framework
- Mock interfaces with hand-written mocks in `test/mock_*.h`
- Test naming: `TEST(ClassName, MethodName_Behavior)`

### Dependencies

- **httplib**: HTTP client library (header-only)
- **gtest**: Testing framework (via FetchContent)
- All dependencies are managed via CMake FetchContent

### Import Guidelines

```cpp
// Order: standard lib → third-party → project
#include <string>
#include <memory>

#include "httplib.h"

#include "clibus/http_client.h"
#include "clibus/i_http_client.h"
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
