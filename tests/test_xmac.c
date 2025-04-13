int test_xmac(int x, int y, int z) {
    x = __builtin_riscv_xmac(x, y, z);
    return x;
}


int test_xmac2(int x, int y, int z) {
    x += y * z;
    return x;
}

int main(int argc, const char** argv) {
    return test_xmac(5,4,3);
}
