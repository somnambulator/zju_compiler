# Mypy compiler

In this project, we implemented a programming language named "mypy".

## Prequisites

```
LLVM Version 13.0.0
GNU Bison
GNU Flex
cmake
jsoncpp
```

## Building

Please follow the following steps for building.

```bash
cd src
mkdir build
cd build
cmake ..
make -j
```

Then you'll get an executable file `mypy`. 

## Testing

We provide sample programs in `test` folder. For testing, run:

```bash
./mypy ../../test/test_recur.mypy && lli a.ll
```
