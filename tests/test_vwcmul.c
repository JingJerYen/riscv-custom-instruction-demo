#include <riscv_vector.h>

int main()
{
    // Complex numbers stored as [real, imag, real, imag, ...]
    int16_t a[] = {2, 3, 1, 1}; // [2+3i, 1+1i]
    int16_t b[] = {4, 5, 3, 2}; // [4+5i, 3+2i]
    int32_t c[4];               // Result: widened to int32_t

    size_t vl = __riscv_vsetvl_e16m1(4);

    vint16m1_t va = __riscv_vle16_v_i16m1(a, vl);
    vint16m1_t vb = __riscv_vle16_v_i16m1(b, vl);

    // Test: (2+3i) * (4+5i) = (8-15) + (10+12)i = -7 + 22i
    vint32m2_t vc = __riscv_vwcmul_vv_i32m2(va, vb, vl);

    __riscv_vse32_v_i32m2(c, vc, vl);

    printf("Result 1: %d + %di\n", c[0], c[1]); // Expected: -7 + 22i
    printf("Result 2: %d + %di\n", c[2], c[3]); // Expected: 1 + 5i

    return 0;
}
