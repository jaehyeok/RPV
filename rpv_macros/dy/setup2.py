from distutils.core import setup
from Cython.Build import cythonize

setup(
	ext_modules = cythonize("DY_test.pyx")
)
