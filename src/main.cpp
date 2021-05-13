#include <iostream>
#include "DPPDiversity.h"


int main() {
    DPPDiversity dppDiversity;
    dppDiversity.init({{-0.1, -0.15}, {0.2, 0.3}, {-0.2, -0.3}}, {1, 2, 3});
    dppDiversity.show_weighted_corr_mat();
    std::unordered_map<int, float>* res = new std::unordered_map<int, float>();
    dppDiversity.select(3, res);
    for (const auto &p : *res) {
        std::cout << p.first << ", " << p.second << "; ";
    }
    std::cout << std::endl;
    delete res;
    return 0;
}
