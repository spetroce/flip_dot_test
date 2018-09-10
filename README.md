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

```bash
cd flip_dot_test #ie. change to root repo directory
mkdir build
cd build
cmake ..
make
```

# Run

```bash
cd flip_dot_test/build
./flip_dot_test /path/to/serial/dev
```
The path to the serial device must be first argument.

Example usage:
```bash
./flip_dot_test /dev/ttyUSB0
```

