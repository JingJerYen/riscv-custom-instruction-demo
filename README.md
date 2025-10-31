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
- `vwcmul.vv vd, vs2, vs1` - Widening complex multiply `vd = vs2 * vs1` for complex number arrays
- `vrotate.vi vd, imm` - Rotate complex numbers array `vd` by 90/180/270 degrees (imm = 1/2/3)
- `vcmla.vv vd, vs2, vs1, imm` - Multiply-Add complex float numbers and rotate by 90/180/270 degrees, similar to Aarch64 `VCMLA`, `vd = vd + (vs1 * vs2 * rotation angle 0/90/180/270)`

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

```c
vfloat32m2_t __riscv_vcmla_vv_f32m2(vfloat32m2_t vd, vfloat32m2_t va, vfloat32m2_t vb, size_t vl)
vfloat32m2_t __riscv_vcmla_rot90_vv_f32m2(vfloat32m2_t vd, vfloat32m2_t va, vfloat32m2_t vb, size_t vl)
vfloat32m2_t __riscv_vcmla_rot180_vv_f32m2(vfloat32m2_t vd, vfloat32m2_t va, vfloat32m2_t vb, size_t vl)
vfloat32m2_t __riscv_vcmla_rot270_vv_f32m2(vfloat32m2_t vd, vfloat32m2_t va, vfloat32m2_t vb, size_t vl)
```
Complex multiply-add with rotation for floating-point complex numbers. Similar to Aarch64 `VCMLA` instruction. The operation performs:
- `vcmla`: `vd = vd + (va * vb)` where complex multiplication gives `(a+bi)*(c+di) = (ac-bd) + (ad+bc)i`
- `vcmla_rot90`: Rotate `vb` by 90° before multiply: `vd = vd + (va * (vb rotated 90°))`
- `vcmla_rot180`: Rotate `vb` by 180° before multiply: `vd = vd + (va * (vb rotated 180°))`
- `vcmla_rot270`: Rotate `vb` by 270° before multiply: `vd = vd + (va * (vb rotated 270°))`

Complex numbers are stored in interleaved format: `[real0, imag0, real1, imag1, ...]`

### Usage Example

```c
#include <riscv_vector.h>

// Complex arrays: [real, imag, real, imag, ...]
float a[] = {1.0, 2.0, 3.0, 4.0};  // (1+2i), (3+4i)
float b[] = {5.0, 6.0, 7.0, 8.0};  // (5+6i), (7+8i)
float result[4] = {0.0};

size_t vl = __riscv_vsetvl_e32m2(4);
vfloat32m2_t va = __riscv_vle32_v_f32m2(a, vl);
vfloat32m2_t vb = __riscv_vle32_v_f32m2(b, vl);
vfloat32m2_t vd = __riscv_vle32_v_f32m2(result, vl);

// Perform complex multiply-add: result = result + (a * b)
vd = __riscv_vcmla_vv_f32m2(vd, va, vb, vl);

// With 90° rotation: result = result + (a * (b rotated 90°))
vd = __riscv_vcmla_rot90_vv_f32m2(vd, va, vb, vl);

__riscv_vse32_v_f32m2(result, vd, vl);
```

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
