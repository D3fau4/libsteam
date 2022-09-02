#include <steam/helpers/utils.hpp>
#include <steam/api/steam_api.hpp>
#include <algorithm>

namespace steam {

    bool isIntegerString(std::string string) {
        if (string.starts_with('-'))
            string = string.substr(1);

        return std::all_of(string.begin(), string.end(), ::isdigit);
    }


    int addgame(const char *appName, const char *exePath, const char *launchOptions, bool hidden, const char * icon){
        auto users = steam::api::User::getUsers();
        auto appId = steam::api::addGameShortcut(users.front(), appName, exePath, launchOptions, { }, hidden, icon);

        return appId->getAppId();
    }
}