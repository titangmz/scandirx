# scandirx

**scandirx** is a fast and efficient directory walker implemented as a Python package with a C extension. It allows you to recursively traverse directories and collect all file and folder paths with optional depth control.

## Table of Contents

- [Installation](#installation)
  - [Prerequisites](#prerequisites)
  - [Clone the Repository](#clone-the-repository)
  - [Set Up a Virtual Environment](#set-up-a-virtual-environment)
  - [Install Dependencies](#install-dependencies)
  - [Build and Install the Package](#build-and-install-the-package)
- [Usage](#usage)
  - [Basic Example](#basic-example)
- [Running Tests](#running-tests)
- [Contributing](#contributing)
- [License](#license)

## Installation

Follow these steps to set up **scandirx** on your local machine.

### Prerequisites

- **Python 3.6** or higher
- **C Compiler:** Ensure you have a C compiler installed.
  - **Ubuntu/Debian:**
    ```shell
    sudo apt-get update
    sudo apt-get install build-essential python3-dev
    ```
  - **macOS:**
    ```shell
    xcode-select --install
    ```
  - **Windows:**
    - Install [Build Tools for Visual Studio](https://visualstudio.microsoft.com/downloads/).

### Clone the Repository

First, clone the repository to your local machine:

```shell
git clone https://github.com/titangmz/scandirx.git
cd scandirx
```

### Set Up a Virtual Environment

It's recommended to use a virtual environment to manage dependencies:

```shell
python3 -m venv .venv
```

Activate the virtual environment:

- **Linux/macOS:**
  ```shell
  source .venv/bin/activate
  ```
- **Windows:**
  ```shell
  .venv\Scripts\activate
  ```

### Install Dependencies

Install the required Python packages using `pip`:

```shell
pip install -r requirements.txt
```

### Build and Install the Package

Build the C extension and install the package in editable mode:

```shell
pip install -e .
```

This command will compile the C extension and install the `scandirx` package into your virtual environment.

**Alternatively**, you can build the extension in place:

```shell
python setup.py build_ext --inplace
```

This will place the compiled `_scandirx` extension directly into the `scandirx` package directory.

## Usage

Once installed, you can use **scandirx** to walk through directories.

### Basic Example

```python
import scandirx

# Walk through the specified directory with a maximum depth of 2
directories = scandirx.walk("/path/to/your/directory", max_depth=2)

# Print all found directories and files
print(*directories, sep="\n")
```

**Example Output:**
```
/path/to/your/directory/file1.txt
/path/to/your/directory/subdir1/
path/to/your/directory/subdir1/file2.txt
...
```

## Running Tests

Ensure that **scandirx** is working correctly by running the provided tests.

1. **Activate the Virtual Environment** (if not already activated):

   ```shell
   source .venv/bin/activate  # Linux/macOS
   .venv\Scripts\activate     # Windows
   ```

2. **Run Tests Using pytest:**

   ```shell
   pytest
   ```

   You should see output indicating that all tests have passed.

## Contributing

Contributions are welcome! Please follow these steps to contribute:

1. **Fork the Repository**

2. **Create a New Branch:**

   ```shell
   git checkout -b feature/your-feature-name
   ```

3. **Make Your Changes**

4. **Commit Your Changes:**

   ```shell
   git commit -m "Add your message here"
   ```

5. **Push to Your Fork:**

   ```shell
   git push origin feature/your-feature-name
   ```

6. **Create a Pull Request**

Please ensure that your code follows the project's coding standards and that all tests pass before submitting a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

---

© 2023 [Pedram Parsa](https://github.com/titangmz)
