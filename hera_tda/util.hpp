#include <utility> // pair
#include <vector>
#include "barcode.hpp" // BATS barcode

template <typename T>
std::vector<std::pair<T, T>> PersistencePairs_to_pairs(
    const std::vector<bats::PersistencePair<T>> &ps
) {
    std::vector<std::pair<T, T>> pairs;
    pairs.reserve(ps.size());
    for (auto& p : ps) {
        pairs.emplace_back(std::make_pair(p.birth, p.death));
    }
    return pairs;
}

// assume first two columns are births and deaths
template <typename T>
std::vector<std::pair<T, T>> array_to_pairs(
    const std::vector<std::vector<T>> &ps
) {
    std::vector<std::pair<T, T>> pairs;
    pairs.reserve(ps.size());
    for (auto& p : ps) {
        pairs.emplace_back(std::make_pair(p[0], p[1]));
    }
    return pairs;
}
