#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

int main() {

    std::unordered_map<std::string, std::size_t> map_;
    std::vector<std::pair<std::string, std::size_t>> list;

    std::string str;
    
    try {
        while (std::cin >> str) {

            if (!std::cin.good())
                throw std::invalid_argument("Error with std::cin\n");

            if (!std::cin)
                break;

            for (std::size_t i = 0; i < str.size(); ++i)
                str[i] = std::tolower(str[i]);

            if (map_.find(str) != map_.end())
                map_[str] += 1;
            else
                map_[str] = 1;
        }
    } catch (std::exception& e) {
        std::cerr<<e.what();
        exit(0);
    }

    for(const auto& pair : map_)
        list.push_back(pair);

    std::sort(list.begin(), list.end(), [](const std::pair<std::string, std::size_t>& lhs, const std::pair<std::string, std::size_t>& rhs) {
        return lhs.second > rhs.second;
    });

    for(const auto& elem : list)
        std::cout << "["<<elem.first << "] : " << elem.second << std::endl;
    
}
