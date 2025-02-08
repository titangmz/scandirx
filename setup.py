from setuptools import setup, Extension
import os

# Define the C extension
module = Extension(
    "scandirx._scandirx",
    sources=["scandirx/scandirx.c"],
    extra_compile_args=["-O2"],
)

# Read the long description from README.md
current_dir = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(current_dir, "README.md"), encoding="utf-8") as f:
    long_description = f.read()

setup(
    name="scandirx",
    version="0.1.1",
    author=["Pedram Parsa", "Omid Saghatchian"],
    author_email=["titangmz@gmail.com", "omidsaghatchian@gmail.com"],
    description="A fast directory walker using a C extension",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/titangmz/scandirx",
    packages=["scandirx"],
    ext_modules=[module],
    python_requires=">=3.6",
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: POSIX :: Linux",
        "Operating System :: Microsoft :: Windows",
    ],
    install_requires=[
        "pytest",
        "setuptools", 
        "wheel"
    ],

)