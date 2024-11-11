#include "DnD_API.h"

int main() {
    DnDAPI api("dnd_rules.db");

    while (true) {
        std::cout << "Enter a rule index to view (or '0' to exit): ";
        int index;
        std::cin >> index;

        if (index == 0) {
            break;
        }

        std::string rule = api.getRule(index);
        if (!rule.empty()) {
            std::cout << "Rule " << index << ": " << rule << std::endl;
        }
        else {
            std::cout << "No rule found at index " << index << std::endl;
        }
    }

    return 0;
}
