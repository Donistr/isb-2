#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <math.h>

std::vector<bool> generate_sequence(size_t len) {
    std::vector<bool> res;

    for (int i = 0; i < len; ++i)
        res.push_back(((std::rand() % 13579) * 17 + 193) % 13579 % 2);

    return res;
}

double test_1(std::vector<bool> sequence) {
    double res = 0;

    for (int i = 0; i < sequence.size(); ++i) {
        if (sequence[i] == 1)
            ++res;
        else
            --res;
    }

    res /= sqrt(sequence.size());

    return erfc(res / sqrt(2));
}

double test_2(std::vector<bool> sequence) {
    double res_1 = 0;

    for (int i = 0; i < sequence.size(); ++i) {
        if (sequence[i] == 1)
            ++res_1;
    }

    res_1 /= sequence.size();

    if (fabs(res_1 - 0.5) >= 2 / sqrt(sequence.size()))
        return 0;

    double res_2 = 0;

    for (int i = 0; i < sequence.size() - 1; ++i) {
        if (sequence[i] != sequence[i + 1])
            ++res_2;
    }

    return erfc(fabs(res_2 - 2 * sequence.size() * res_1 * (1 - res_1)) / (2 * sqrt(2 * sequence.size()) * res_1 * (1 - res_1)));
}

double test_3_xi2(std::vector<bool> sequence) {
    int v[4] = { 0 };
    double pi[4] = { 0.2148, 0.3672, 0.2305, 0.1875 };

    int maxs_arr[16] = { 0 };

    for (int i = 0; i < 16; ++i) {
        int max = 0;
        int pred_max = 0;

        for (int j = 0; j < 8; ++j) {
            if (sequence[i + j] == 1)
                ++pred_max;
            else {
                if (pred_max > max)
                    max = pred_max;

                pred_max = 0;
            }
        }

        if (pred_max > max)
            max = pred_max;

        maxs_arr[i] = max;
    }

    for (int i = 0; i < 16; ++i) {
        if (maxs_arr[i] <= 1)
            ++v[0];
        else if (maxs_arr[i] == 2)
            ++v[1];
        else if (maxs_arr[i] == 3)
            ++v[2];
        else
            ++v[3];
    }

    double xi2 = 0;

    for (int i = 0; i < 4; ++i)
        xi2 += (v[i] - 16 * pi[i]) * (v[i] - 16 * pi[i]) / (16 * pi[i]);

    return xi2;
}

int main() {
	srand(time(0));

    std::vector<bool> sequence = generate_sequence(128);

    for (int i = 0; i < sequence.size(); ++i)
        std::cout << sequence[i];
    std::cout << std::endl;

    double p_1 = test_1(sequence);
    std::cout << p_1 << std::endl;

    double p_2 = test_2(sequence);
    std::cout << p_2 << std::endl;

    double xi2 = test_3_xi2(sequence);
    std::cout << xi2 << std::endl;

    return 0;
}