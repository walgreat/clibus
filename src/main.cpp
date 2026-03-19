#include <iostream>
#include <string>
#include "clibus/clibus.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        print_help();
        return 1;
    }

    std::string method = argv[1];
    std::string url = argv[2];
    return fetch_url(url, method);
}
