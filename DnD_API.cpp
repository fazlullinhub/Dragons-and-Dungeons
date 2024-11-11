#include "DnD_API.h"

const std::string DnDAPI::api_url = "https://api.open5e.com/rules/";

DnDAPI::DnDAPI(const std::string& db_file) : db(db_file) {
    setupDatabase();
}

void DnDAPI::setupDatabase() {
    db << "CREATE TABLE IF NOT EXISTS rules (id INTEGER PRIMARY KEY, content TEXT);";
}

std::string DnDAPI::getRule(int index) {
    auto it = cache.find(index);
    if (it != cache.end()) {
        return it->second; 
    }

    fetchAndStoreRule(index); 
    return cache[index]; 
}

void DnDAPI::fetchAndStoreRule(int index) {
    auto response = cpr::Get(cpr::Url{ api_url + std::to_string(index) });

    if (response.status_code != 200) {
        std::cerr << "Error fetching rule: " << response.error.message << std::endl;
        return;
    }

    auto json_response = nlohmann::json::parse(response.text);

    std::string ruleContent = json_response["content"];
    addRuleToCache(index, ruleContent);
}

void DnDAPI::addRuleToCache(int index, const std::string& content) {
    db << "INSERT INTO rules (id, content) VALUES (?, ?);", index, content;

    cache[index] = content; 
}

void DnDAPI::displayRules() {
    int index = 1; 
    std::string rule;
    while (true) {
        rule = getRule(index);
        if (rule.empty()) {
            break;
        }
        std::cout << "Rule " << index << ": " << rule << std::endl;
        index++;
    }
}
