#include <stdio.h>
#include <stdint.h>

#define GF4_POLY 0x13  /* x^4 + x + 1 */
#define GF8_POLY 0x11B /* x^8 + x^4 + x^3 + x + 1 */

/* Nhân a * b trong GF(2^n), rút gọn theo đa thức tối giản poly */
uint8_t gf_mul(uint8_t a, uint8_t b, int n, uint16_t poly)
{
    uint16_t x = a;
    uint8_t result = 0;

    while (b) {
        if (b & 1)
            result ^= x;
        b >>= 1;
        x <<= 1;
        if (x & (1 << n))
            x ^= poly;
    }
    return result;
}

/* In phần tử dưới dạng đa thức, ví dụ 0xB -> x^3 + x + 1 */
void print_poly(uint8_t v)
{
    int first = 1;

    if (v == 0) {
        printf("0");
        return;
    }
    for (int i = 7; i >= 0; i--) {
        if (!(v >> i & 1))
            continue;
        if (!first)
            printf(" + ");
        if (i == 0)
            printf("1");
        else if (i == 1)
            printf("x");
        else
            printf("x^%d", i);
        first = 0;
    }
}

/* In kết quả phép nhân ở cả dạng hex và dạng đa thức */
void show(int n, uint8_t a, uint8_t b)
{
    uint8_t c = gf_mul(a, b, n, n == 4 ? GF4_POLY : GF8_POLY);

    printf("GF(2^%d): 0x%02X * 0x%02X = 0x%02X\n", n, a, b, c);
    printf("  (");
    print_poly(a);
    printf(") * (");
    print_poly(b);
    printf(") = ");
    print_poly(c);
    printf("\n");
}

int main(void)
{
    int n;
    unsigned int a, b;

    printf("Chọn trường (4 hoặc 8): ");
    if (scanf("%d", &n) != 1 || (n != 4 && n != 8)) {
        printf("Chỉ hỗ trợ n = 4 hoặc n = 8\n");
        return 1;
    }
    printf("Nhập a, b (hex): ");
    if (scanf("%x %x", &a, &b) != 2 || a >= (1u << n) || b >= (1u << n)) {
        printf("Giá trị không hợp lệ\n");
        return 1;
    }
    show(n, a, b);
    return 0;
}
