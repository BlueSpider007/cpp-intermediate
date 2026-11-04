#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Rec {
    std::string name;
    int score;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Rec> recs(n);
    for (Rec &r : recs) {
        std::cin >> r.name >> r.score;
    }
    int cutoff, q;
    std::cin >> cutoff >> q;

    // TODO 1: drop every record whose score is below cutoff (erase-remove).
    auto newend = std::remove_if(recs.begin(), recs.end(),
                                 [cutoff](Rec x) { return x.score < cutoff; });
    recs.erase(newend, recs.end());
    // TODO 2: order the survivors by score, highest first; equal scores keep
    // input order.
    std::stable_sort(recs.begin(), recs.end(), [](const Rec &x, const Rec &y) {
        return x.score > y.score;
    });

    std::cout << "kept: " << recs.size() << "\n";
    for (const Rec &r : recs)
        std::cout << r.name << " " << r.score << "\n";

    for (int i = 0; i < q; ++i) {
        int s;
        std::cin >> s;
        // TODO 3: how many survivors have score >= s (binary search)
        int count =
            std::partition_point(recs.begin(), recs.end(),
                                 [&s](const Rec &r) { return r.score >= s; }) -
            recs.begin();
        std::cout << ">= " << s << ": " << count << "\n";
    }
    return 0;
}
