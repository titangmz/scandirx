from setuptools import setup, Extension
import os

# Define the C extension with the package name
module = Extension(
    "scandirx._scandirx",  # Include package name
    sources=["scandirx/scandirx.c"],
    extra_compile_args=["-O2"],  # Optimization flags (optional)
)

# Read the long description from README.md
current_dir = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(current_dir, "README.md"), encoding="utf-8") as f:
    long_description = f.read()

setup(
    ext_modules=[module],
    setup_cfg=True,  # Ensure it reads the setup.cfg
)