#include <vector>
#include <utility> // pair
#include "barcode.hpp" // BATS barcode
#include "bottleneck.h" // Hera bottleneck

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include <pybind11/buffer_info.h>

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

template <typename T>
inline std::pair<int, int> matched_inds(
    hera::bt::MatchingEdge<T> e
) {
    return std::make_pair(e.first.get_user_id(), e.second.get_user_id());
}

template <typename T>
auto BottleneckDistance(
    const std::vector<bats::PersistencePair<T>> &ps1,
    const std::vector<bats::PersistencePair<T>> &ps2
) {
    auto diagramA = PersistencePairs_to_pairs(ps1);
    auto diagramB = PersistencePairs_to_pairs(ps2);
    int decPrecision { 0 };
    double res;
    hera::bt::MatchingEdge<T> e;

    res = hera::bottleneckDistExact(diagramA, diagramB, decPrecision, e, true);
    return std::make_pair(res, matched_inds(e));
}

template <typename T>
auto BottleneckDistanceApprox(
    const std::vector<bats::PersistencePair<T>> &ps1,
    const std::vector<bats::PersistencePair<T>> &ps2,
    T delta
) {
    auto diagramA = PersistencePairs_to_pairs(ps1);
    auto diagramB = PersistencePairs_to_pairs(ps2);
    double res;
    hera::bt::MatchingEdge<T> e;

    res = hera::bottleneckDistApprox(diagramA, diagramB, delta, e, true);
    return std::make_pair(res, matched_inds(e));
}



PYBIND11_MODULE(bottleneck, m) {

    m.def("Pairs", &PersistencePairs_to_pairs<double>);
    m.def("BottleneckDistance", &BottleneckDistance<double>);
    m.def("BottleneckDistanceApprox", &BottleneckDistanceApprox<double>);
}
