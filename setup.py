# setup file to compile C++ library
import setuptools
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys, os
import distutils

# from pybind11.setup_helpers import Pybind11Extension, build_ext
sys.path = [os.path.dirname(os.path.abspath(sys.argv[0])) + '/hera_tda'] + sys.path
from _version import __version__
sys.path = sys.path[1:]


this_dir = os.path.dirname(os.path.realpath(__file__))
include_dirs = [
this_dir + '/BATS/include/',
this_dir + '/pybind11/include/',
this_dir + '/hera/bottleneck/include/',
this_dir + '/hera/wasserstein/include/'
]

print('default compiler:', distutils.ccompiler.get_default_compiler())

extra = {'cxx': ['-std=c++17']}

ext_modules = [
    Extension(
        'hera_tda.bottleneck',
        ['hera_tda/bottleneck.cpp'],
        include_dirs=include_dirs,
        extra_compile_args=extra['cxx'],
        # extra_link_args=extra_link,
        language='c++'
    ),
    Extension(
        'hera_tda.wasserstein',
        ['hera_tda/wasserstein.cpp'],
        include_dirs=include_dirs,
        extra_compile_args=extra['cxx'],
        # extra_link_args=extra_link,
        language='c++'
    ),
]

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

setup(
    name='hera-tda',
    version=__version__,
    author='Brad Nelson',
    author_email='bradnelson@uchicago.edu',
    packages=['hera_tda'],
    ext_modules=ext_modules,
    zip_safe=False,
    license_files = ('LICENSE','hera/license.txt'),
    description="Python bindings for Hera",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/CompTop/pyhera",
    project_urls={
        "Bug Tracker": "https://github.com/CompTop/pyhera/issues",
    },
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Intended Audience :: Education',
        'Intended Audience :: Science/Research',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Topic :: Utilities',
        'Topic :: Scientific/Engineering :: Mathematics',
        'Programming Language :: C++',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'License :: OSI Approved :: BSD License',
        'Operating System :: POSIX :: Linux',
        'Operating System :: MacOS :: MacOS X'
    ],
    python_requires=">=3.7",
    keywords='algebraic topology, topological data analysis, bottleneck distance, wasserstein distance, persistence barcode, persistence diagram',
)
