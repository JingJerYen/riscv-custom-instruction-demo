#include <riscv_vector.h>
// #include <stdio.h>
#define printf(...)

int main()
{
    // Complex numbers stored as [real, imag, real, imag, ...]
    float a[] = {1.0, 2.0, 3.0, 4.0};  // (1+2i), (3+4i)
    float b[] = {5.0, 6.0, 7.0, 8.0};  // (5+6i), (7+8i)
    float result[4] = {0.0, 0.0, 0.0, 0.0};

    size_t vl = __riscv_vsetvl_e32m2(4);

    vfloat32m2_t va = __riscv_vle32_v_f32m2(a, vl);
    vfloat32m2_t vb = __riscv_vle32_v_f32m2(b, vl);
    vfloat32m2_t vd = __riscv_vle32_v_f32m2(result, vl);

    // Test vcmla: vd = vd + (va * vb)
    // (1+2i) * (5+6i) = (5-12) + (6+10)i = -7 + 16i
    // (3+4i) * (7+8i) = (21-32) + (24+28)i = -11 + 52i
    printf("Testing vcmla (no rotation):\n");
    vd = __riscv_vcmla_vv_f32m2(vd, va, vb, vl);
    __riscv_vse32_v_f32m2(result, vd, vl);
    printf("Result 1: %.1f + %.1fi (Expected: -7.0 + 16.0i)\n", result[0], result[1]);
    printf("Result 2: %.1f + %.1fi (Expected: -11.0 + 52.0i)\n\n", result[2], result[3]);

    // Reset result
    result[0] = result[1] = result[2] = result[3] = 0.0;
    vd = __riscv_vle32_v_f32m2(result, vl);

    // Test vcmla_rot90: vd = vd + (va * (vb rotated 90°))
    // vb rotated 90°: (5+6i) -> (-6+5i), (7+8i) -> (-8+7i)
    // (1+2i) * (-6+5i) = (-6-10) + (5-12)i = -16 + -7i
    // (3+4i) * (-8+7i) = (-24-28) + (21-32)i = -52 + -11i
    printf("Testing vcmla_rot90 (90° rotation):\n");
    vd = __riscv_vcmla_rot90_vv_f32m2(vd, va, vb, vl);
    __riscv_vse32_v_f32m2(result, vd, vl);
    printf("Result 1: %.1f + %.1fi (Expected: -16.0 + -7.0i)\n", result[0], result[1]);
    printf("Result 2: %.1f + %.1fi (Expected: -52.0 + -11.0i)\n\n", result[2], result[3]);

    // Reset result
    result[0] = result[1] = result[2] = result[3] = 0.0;
    vd = __riscv_vle32_v_f32m2(result, vl);

    // Test vcmla_rot180: vd = vd + (va * (vb rotated 180°))
    // vb rotated 180°: (5+6i) -> (-5+-6i), (7+8i) -> (-7+-8i)
    // (1+2i) * (-5+-6i) = (-5+12) + (-6-10)i = 7 + -16i
    // (3+4i) * (-7+-8i) = (-21+32) + (-24-28)i = 11 + -52i
    printf("Testing vcmla_rot180 (180° rotation):\n");
    vd = __riscv_vcmla_rot180_vv_f32m2(vd, va, vb, vl);
    __riscv_vse32_v_f32m2(result, vd, vl);
    printf("Result 1: %.1f + %.1fi (Expected: 7.0 + -16.0i)\n", result[0], result[1]);
    printf("Result 2: %.1f + %.1fi (Expected: 11.0 + -52.0i)\n\n", result[2], result[3]);

    // Reset result
    result[0] = result[1] = result[2] = result[3] = 0.0;
    vd = __riscv_vle32_v_f32m2(result, vl);

    // Test vcmla_rot270: vd = vd + (va * (vb rotated 270°))
    // vb rotated 270°: (5+6i) -> (6+-5i), (7+8i) -> (8+-7i)
    // (1+2i) * (6+-5i) = (6+10) + (-5+12)i = 16 + 7i
    // (3+4i) * (8+-7i) = (24+28) + (-21+32)i = 52 + 11i
    printf("Testing vcmla_rot270 (270° rotation):\n");
    vd = __riscv_vcmla_rot270_vv_f32m2(vd, va, vb, vl);
    __riscv_vse32_v_f32m2(result, vd, vl);
    printf("Result 1: %.1f + %.1fi (Expected: 16.0 + 7.0i)\n", result[0], result[1]);
    printf("Result 2: %.1f + %.1fi (Expected: 52.0 + 11.0i)\n", result[2], result[3]);

    return 0;
}
