#include <thread>
#include <future>
#include <iostream>
#include <random>

const int num_of_futures = 10;

void DotsGen(std::vector<std::pair<float,float>>& dots, float R) {

    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine eng(seed);

    std::uniform_real_distribution<float> distr(-R, R);

    for (auto&& elem : dots) {
        elem.first = distr(eng);
        elem.second = distr(eng);
    }
}

int main() {

    float R = 0;
    int N = 0, K = 0;
    std::cin >> R >> N;

    int group_size = N / num_of_futures;
    std::vector<std::pair<float,float>> dots(N);
    DotsGen(dots, R);

    std::vector<std::future<int>> futures;
    futures.reserve(num_of_futures);

    for (int i = 0; i < futures.size(); ++i) {
        futures.push_back(std::async([&dots, i, group_size, R]() {

            int ans = 0;
            for (int j = i * group_size; j < (1 + i) * group_size; ++j) {

                float r_2 = dots[j].first * dots[j].first + dots[j].second * dots[j].second;
                if (r_2 <= R * R)
                    ans++;
            }
            return ans;
        }));

    }

    for (auto&& fut : futures) {
        K += fut.get();
    }

    std:: cout << "S = " << (static_cast<float>(K)/ static_cast<float>(N)) * R * R;

    return 0;
}
