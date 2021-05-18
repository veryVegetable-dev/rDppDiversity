#include "DppKernelModel.h"
#include <fstream>
#include <unordered_map>


void DppKernelModel::parse_sample(const std::string &file_path, std::vector<std::vector<size_t> > *sample_ptr, std::vector<std::string> *item_names) {
    std::ifstream in_file;
    in_file.open(file_path, std::ifstream::in);
    const int MAX_LINE_SIZE = 1000;
    char buffer[MAX_LINE_SIZE];
    std::unordered_map<std::string, size_t> uniq_item;
    std::vector<size_t> one_line;
    while (in_file.getline(buffer, MAX_LINE_SIZE)) {
        one_line.clear();
        char *field = strtok(buffer, ",");
        while (field != nullptr) {
            std::string item(field);
            if (uniq_item.find(item) == uniq_item.end()) {
                uniq_item[item] = uniq_item.size();
                item_names->emplace_back(item);
            }
            one_line.emplace_back(uniq_item[item]);
            field = strtok(nullptr, ",");
        }
        sample_ptr->emplace_back(one_line);
    }
    in_file.close();
}
