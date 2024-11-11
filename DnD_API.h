#ifndef DND_API_H
#define DND_API_H

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <sqlite_modern_cpp.h>
#include <iostream>
#include <string>
#include <unordered_map>

class DnDAPI {
public:
    DnDAPI(const std::string& db_file);
    void setupDatabase();
    std::string getRule(int index);
    void displayRules();
    void addRuleToCache(int index, const std::string& content);

private:
    sqlite::database db;
    std::unordered_map<int, std::string> cache;
    static const std::string api_url;
    void fetchAndStoreRule(int index);
};

#endif
