#include <steam/api/steam_api.hpp>

#include <steam/helpers/utils.hpp>

#include <fmt/format.h>

int main(int argc, char *argv[]) {

    if(argc > 4)
        steam::addgame(argv[1], argv[2], argv[3], argv[4], argv[5]);
    else
        printf("No suficientes argumentos");
    return EXIT_SUCCESS;
}