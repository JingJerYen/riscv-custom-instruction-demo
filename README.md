# RISC-V Custom Extension Demo (xstar)

This repository demonstrates how to add custom RISC-V instructions across the full toolchain:

- **LLVM/Clang** - Compiler support with intrinsics
- **Spike** - ISA simulator
- **Test suite** - C programs using custom instructions

## Custom Extension: `xstar`

The `xstar` extension includes:

### Scalar Instructions
- `xmac rd, rs1, rs2` - Multiply-accumulate: `rd = rd + (rs1 * rs2)`

### Vector Instructions
- `vwcmul.vv` - Widening complex multiply for complex number arrays
- `vrotate.vi` - Rotate complex numbers by 90/180/270 degrees

## Builtin Functions

### Scalar Builtins

```c
int __builtin_riscv_xmac(int rd, int rs1, int rs2)
```
Multiply-accumulate operation: returns `rd + (rs1 * rs2)`

### Vector Builtins

```c
vint32m2_t __riscv_vwcmul_vv_i32m2(vint16m1_t va, vint16m1_t vb, size_t vl)
```
Widening complex multiply for complex number arrays. Multiplies two vectors of `int16_t` complex numbers and produces `int32_t` results. The real and imaginary parts are stored in an interleaved format. This is similar to `VCMLA` in Aarch64.

```c
vint16m1_t __riscv_vrotate_rot90_v_i16m1(vint16m1_t va, size_t vl)
```
Rotate complex numbers by 90 degrees: `(a + bi) → (-b + ai)`

## Project Structure

```
├── llvm/          # LLVM/Clang patches for xstar extension
├── spike/         # Spike simulator patches
└── tests/         # Test programs and Makefile
```

## Building

### 1. Build LLVM with xstar support

Apply patches and build:
```bash
cd /path/to/llvm-project
# Apply patches from llvm/ directory
ninja -C build
```

### 2. Build Spike with xstar support

Apply patches and build:
```bash
cd /path/to/riscv-isa-sim
# Apply patches from spike/ directory
mkdir build && cd build
../configure
make -j$(nproc)
```

## Running Tests

```bash
cd tests

# Build all tests
make

# Run specific test
make run-test_xmac
make run-test_vwcmul
make run-test_vrotate

# Clean
make clean
```

### Test Programs

- **test_xmac.c** - Tests scalar multiply-accumulate instruction
- **test_vwcmul.c** - Tests vector widening complex multiply
- **test_vrotate.c** - Tests vector complex rotation

## ISA String

When using the custom extension, specify:
```
rv32imac_xstar         # For scalar only
rv32imac_xstar_zve32x  # For scalar + vector
```

## References

- [RISC-V ISA Manual](https://riscv.org/technical/specifications/)
- [LLVM RISC-V Target](https://llvm.org/docs/RISCVUsage.html)
- [Spike ISA Simulator](https://github.com/riscv-software-src/riscv-isa-sim)
