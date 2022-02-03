# Hera-TDA

[![Supported Python Versions](https://img.shields.io/pypi/pyversions/hera-tda.svg)](https://pypi.org/project/hera-tda/)
[![PyPi](https://img.shields.io/pypi/v/hera-tda.svg)](https://pypi.org/project/hera-tda/)
[![License: BSD](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

[![Ubuntu Tests](https://github.com/CompTop/pyhera/workflows/ubuntu-latest/badge.svg)](https://github.com/CompTop/pyhera/actions)
[![MacOS Tests](https://github.com/CompTop/pyhera/workflows/macos-latest/badge.svg)](https://github.com/CompTop/pyhera/actions)

Python bindings for [Hera](https://bitbucket.org/grey_narn/hera/src/master/), a library for fast calculation of bottleneck distance and Wasserstein distance on persistence diagrams.

These bindings can be used with standard Python types (lists of lists).  These bindings are also compatible with [BATS](https://bats-tda.readthedocs.io/en/latest/).

Note that Hera is also used in [Dionysus 2](https://mrzv.org/software/dionysus2/API.html#diagrams) for bottleneck distance computation.

## Installation


You first need to install boost headers for Hera
```
dnf install boost-devel # fedora
```

### pip install

```
pip install hera-tda
```
This will compile binaries.

### Build from source

Then, do a recursive clone for submodules
```
git clone --recursive git@github.com:CompTop/pyhera.git
```

then you can install to your Python environment
```
python setup.py install
```

## Basic Example

### Bottleneck Distance
After installation, the package is available under the `hera_tda` namespace.

```python
import hera_tda as hera
import hera_tda.bottleneck

pX = [[1.0, 2.0], [2.0,3.0]] # diagram 1
pY = [[1.1, 2.1], [2.1, 3.1]] # diagram 2
d, inds = hera.bottleneck.BottleneckDistance(pX, pY)
# d = 0.1
```

`d` is the computed bottleneck distance

`inds` is a tuple containing the indices of `pX` and `pY` that were the maximum-weight matching (`-1` is used to indicate a diagonal point).

### Wasserstein Distance

```python
from hera_tda.wasserstein import WassersteinDistance

pX = [[1.0, 2.0], [2.0,3.0]]
pY = [[1.1, 2.1], [2.1, 3.1]]
p = 2.0 # wasserstein-p
d = WassersteinDistance(pX, pY, p)
# d = 0.1414...
```

`WassersteinDistance` just returns the distance.  There is no matching.

## Additional Examples

See [demo.ipynb](ipynb/demo.ipynb) and [wasserstein.ipynb](ipynb/wasserstein.ipynb)
