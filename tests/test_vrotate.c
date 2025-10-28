#include <riscv_vector.h>

int main()
{
    // Complex numbers stored as [real, imag, real, imag, ...]
    int16_t a[] = {2, 3, 1, 1}; // [2+3i, 1+1i]

    size_t vl = __riscv_vsetvl_e16m1(4);
    vint16m1_t va = __riscv_vle16_v_i16m1(a, vl);

    // rotate 90 degrees: (a + bi) -> (-b + ai)
    va = __riscv_vrotate_rot90_v_i16m1(va, vl);

    __riscv_vse16_v_i16m1(a, va, vl);

    printf("Result 1: %d + %di\n", a[0], a[1]); // Expected: -3+2i
    printf("Result 2: %d + %di\n", a[2], a[3]); // Expected: -1+1i

    return 0;
}
