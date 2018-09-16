# Pull the repo with submodules

```bash
git clone --recurse-submodules git@github.com:spetroce/flip_dot_test.git
```

*or*

```bash
git clone git@github.com:spetroce/flip_dot_test.git
cd flip_dot_test #ie. change to root repo directory
git submodule update --init --recursive
```

# Build
By default, the cmake option WITH_QT is set and cmake will try find and build this program with a graphical interface. If the option is turned off or Qt could not be found by cmake, the program will build with a command line only interface. The command line interface only takes as input the serial device path and runs a segment test followed by a number test. The graphical interface allows you to run tests at will with push buttons.

```bash
cd flip_dot_test #ie. change to root repo directory
mkdir build
cd build
cmake ..
make
```

# Run (graphical interface)

```bash
cd flip_dot_test/build
./flip_dot_test
```

# Run (command line interface)

```bash
cd flip_dot_test/build
./flip_dot_test /path/to/serial/dev
```
The path to the serial device must be first argument.

Example usage:
```bash
./flip_dot_test /dev/ttyUSB0
```

