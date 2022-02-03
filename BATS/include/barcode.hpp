/**
This file is taken from BATS, distributed under a MIT license

https://github.com/CompTop/BATS/blob/master/include/persistence/barcode.hpp

MIT License

Copyright (c) 2019 Bradley Nelson, Anjan Dwaraknath

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once

#include <cstddef>
#include <limits>
#include <string>
#include <iostream>
#include <vector>


namespace bats {

// no index
const size_t NO_IND = std::numeric_limits<size_t>::max();

// store dimension, birth, death, and critical indices of pair
template <typename T>
struct PersistencePair {
	size_t dim;
	size_t birth_ind;
	size_t death_ind;
	T birth;
	T death;

	PersistencePair() {}
	PersistencePair(
		const size_t dim,
		const size_t birth_ind,
		const size_t death_ind,
		const T birth,
		const T death
	) : dim(dim), birth_ind(birth_ind), death_ind(death_ind), birth(birth), death(death) {}

	// useful for checking equality of barcodes
	inline bool operator==(const PersistencePair &other) const { return birth == other.birth && death == other.death && dim == other.dim; }
	inline bool operator!=(const PersistencePair &other) const { return birth != other.birth || death != other.death || dim != other.dim; }

	inline size_t get_dim() const {return dim;}
	inline size_t get_birth_ind() const {return birth_ind;}
	inline size_t get_death_ind() const {return death_ind;}
	inline T get_birth() const {return birth;}
	inline T get_death() const {return death;}
	inline T length() const {return death - birth;}
	inline T mid() const {return (death + birth) / T(2);}

	// std::string str() {
    //     std::ostringstream oss;
    //     oss << dim << " : (" << birth << ',' << death << ") <" << birth_ind << ',' << (death_ind == bats::NO_IND ? (int) -1 : (int) death_ind) << '>';
    //     return oss.str();
    // }
};

template <typename T>
bool barcode_equality(
	const std::vector<PersistencePair<T>> &ps1,
	const std::vector<PersistencePair<T>> &ps2
) {
	// check for same number of pairs
	if (ps1.size() != ps2.size()) {
		return false;
	}

	size_t n = ps1.size();
	// vector for checking if a pair in ps2 has been matched
	std::vector<bool> matched(n, false);
	for (size_t i = 0; i < n; i++) {
		bool found_match = false;
		for (size_t j = 0; j < n; j++) {
			if (ps1[i] == ps2[j] && !matched[j]){
				found_match = true;
				matched[j] = true;
				break;
			}
		}
		if (!found_match) {
			return false; // no match for ps1[i]
		}
	}
	return true; // we found a match for every pair.

}

} // namespace bats
