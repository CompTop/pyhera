# PyHera
[BATS](https://bats-tda.readthedocs.io/en/latest/) compatible python bindings for [Hera](https://bitbucket.org/grey_narn/hera/src/master/)

This allows for fast and easy computation of bottleneck distance between persistence diagrams in Python.

Note that Hera is also used in [Dionysus 2](https://mrzv.org/software/dionysus2/API.html#diagrams) for bottleneck distance computation.

## Installation


You first need to install boost headers for Hera
```
dnf install boost-devel # fedora
```

Then, do a recursive clone for submodules
```
git clone --recursive git@github.com:CompTop/pyhera.git
```

then you can install to your Python environment
```
python setup.py install
```

## Basic Example

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

## Additional Examples

See [demo.ipynb](ipynb/demo.ipynb)

## TODO

Add bindings for Wasserstein distance
