#include <vector>
#include <utility> // pair
#include <string.h> // to_string
#include "barcode.hpp" // BATS barcode
#include "wasserstein.h" // Hera wasserstein
#include "util.hpp" // common utilities

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include <pybind11/buffer_info.h>


template <typename T>
auto WassersteinDistanceBATS(
    const std::vector<bats::PersistencePair<T>> &ps1,
    const std::vector<bats::PersistencePair<T>> &ps2,
    T wasserstein_power
) {
    auto diagramA = PersistencePairs_to_pairs(ps1);
    auto diagramB = PersistencePairs_to_pairs(ps2);
    hera::AuctionParams<T> params;
    params.wasserstein_power = wasserstein_power;

    return hera::wasserstein_dist(diagramA, diagramB, params);
}

template <typename T>
auto WassersteinDistanceBATS(
    const std::vector<bats::PersistencePair<T>> &ps1,
    const std::vector<bats::PersistencePair<T>> &ps2,
    hera::AuctionParams<T> &params
) {
    auto diagramA = PersistencePairs_to_pairs(ps1);
    auto diagramB = PersistencePairs_to_pairs(ps2);

    return hera::wasserstein_dist(diagramA, diagramB, params);
}

template <typename T>
auto WassersteinDistance(
    const std::vector<std::vector<T>> &ps1,
    const std::vector<std::vector<T>> &ps2,
    T wasserstein_power
) {
    auto diagramA = array_to_pairs(ps1);
    auto diagramB = array_to_pairs(ps2);
    hera::AuctionParams<T> params;
    params.wasserstein_power = wasserstein_power;

    return hera::wasserstein_dist(diagramA, diagramB, params);
}

template <typename T>
auto WassersteinDistance(
    const std::vector<std::vector<T>> &ps1,
    const std::vector<std::vector<T>> &ps2,
    hera::AuctionParams<T> &params
) {
    auto diagramA = array_to_pairs(ps1);
    auto diagramB = array_to_pairs(ps2);

    return hera::wasserstein_dist(diagramA, diagramB, params);
}


namespace py = pybind11;

PYBIND11_MODULE(wasserstein, m) {

    py::class_<hera::AuctionParams<double>>(m, "AuctionParams")
    .def(py::init<>())
    .def_readwrite("wasserstein_power", &hera::AuctionParams<double>::wasserstein_power)
    .def_readwrite("delta", &hera::AuctionParams<double>::delta)
    .def_readwrite("internal_p", &hera::AuctionParams<double>::internal_p)
    .def_readwrite("initial_epsilon", &hera::AuctionParams<double>::initial_epsilon)
    .def_readwrite("epsilon_common_ratio", &hera::AuctionParams<double>::epsilon_common_ratio)
    .def_readwrite("gamma_threshold", &hera::AuctionParams<double>::gamma_threshold)
    .def_readwrite("max_num_phases", &hera::AuctionParams<double>::max_num_phases)
    .def_readwrite("max_bids_per_round", &hera::AuctionParams<double>::max_bids_per_round)
    .def_readwrite("dim", &hera::AuctionParams<double>::dim)
    .def_readwrite("final_relative_error", &hera::AuctionParams<double>::final_relative_error)
    .def_readwrite("tolerate_max_iter_exceeded", &hera::AuctionParams<double>::tolerate_max_iter_exceeded)
    .def("__repr__",
        [](const hera::AuctionParams<double> &a) {
            return "AuctionParams( p=" + std::to_string(a.wasserstein_power) + " )";
        }
    );

    m.def("WassersteinDistance",
        [](
            std::vector<bats::PersistencePair<double>> &ps1,
            std::vector<bats::PersistencePair<double>> &ps2,
            double p
        ){return WassersteinDistanceBATS(ps1, ps2, p);}
    );
    m.def("WassersteinDistance",
        [](
            std::vector<bats::PersistencePair<double>> &ps1,
            std::vector<bats::PersistencePair<double>> &ps2,
            hera::AuctionParams<double> &p
        ){return WassersteinDistanceBATS(ps1, ps2, p);}
    );
    m.def("WassersteinDistance",
        [](
            std::vector<std::vector<double>> &ps1,
            std::vector<std::vector<double>> &ps2,
            double p
        ){return WassersteinDistance(ps1, ps2, p);}
    );
    m.def("WassersteinDistance",
        [](
            std::vector<std::vector<double>> &ps1,
            std::vector<std::vector<double>> &ps2,
            hera::AuctionParams<double> &p
        ){return WassersteinDistance(ps1, ps2, p);}
    );


    // m.def("BottleneckDistance", &BottleneckDistanceBATS<double>);
    // m.def("BottleneckDistance", &BottleneckDistance<double>);
    // m.def("BottleneckDistanceApprox", &BottleneckDistanceApproxBATS<double>);
    // m.def("BottleneckDistanceApprox", &BottleneckDistanceApprox<double>);
}
