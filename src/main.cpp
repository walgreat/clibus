#include <iostream>
#include "clibus/clibus.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    std::string url = argv[1];
    return fetch_url(url);
}
