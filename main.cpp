
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#define random(a, b) (rand()%(b-a+1))+a

int main() {
    srand((int) time(0));  // 产生随机种子  把0换成NULL也行

    int m, n;
    // 给定人数n
//    std::cin >> n;
    n = 30;
    // 给定每组人数
//    std::cin >> m;
    m = 3;
    // 得到group组
    int group = n / m;
    // 剩余人数
    int mod = n % m;
    std::vector<bool> is_first(n, true);
    std::vector<std::vector<int>> res(group);
    // 每次产生 m 个随机数,共group组
    for (int i = 1; i <= group; i++) {
        std::vector<int> tmp;
        while (tmp.size() <= m) {
            int k = random(1, n);
            if (is_first[k]) {
                std::cout<<k<<std::endl;
                tmp.emplace_back(k);
                is_first[k] = false;
            }
        }
        res.emplace_back(tmp);
    }

    // 将剩余人数随机加入group组中
    std::vector<bool> is_first_group(group, true);
    for (int i = 1; i <= mod; i++) {
        // 决定分配到哪一个组
        int k = random(1, group);
        // 为当前剩余的第i个人分配一个随机数
        int l = random(1, n);
        if (is_first_group[k] && is_first[l]) {
            res[k].emplace_back(l);
            is_first_group[k] = false;
            is_first[l] = false;
        }
    }

    // 输出结果
    for (auto all_group : res) {
        for (auto ret : all_group) {
            std::cout << ret << " ";
        }
        std::cout<<std::endl;
    }
    return 0;
}