#include <steam/helpers/utils.hpp>

#include <algorithm>

namespace steam {

    bool isIntegerString(std::string string) {
        if (string.starts_with('-'))
            string = string.substr(1);

        return std::all_of(string.begin(), string.end(), ::isdigit);
    }


    void addgame(const std::string &appName, const std::fs::path &exePath, const std::string &launchOptions = "", const std::vector<std::string> &tags = { }, bool hidden = false, std::string icon = ""){
        auto users = steam::api::User::getUsers();
        auto appId = steam::api::addGameShortcut(users.front(), appName, exePath, launchOptions, tags, hidden, icon);
    }
}