# Nhân đa thức trong GF(2^4) và GF(2^8)

Sinh viên: **Vũ Nhật Minh**

Cài đặt phép nhân hai đa thức trong trường hữu hạn GF(2^4) và GF(2^8), rút gọn theo đa thức tối giản:

- GF(2^4): `x^4 + x + 1` (`0x13`)
- GF(2^8): `x^8 + x^4 + x^3 + x + 1` (`0x11B`)

## Thuật toán

Mỗi phần tử là một đa thức hệ số 0/1, biểu diễn bằng số n bit. Phép nhân dùng phương pháp shift-and-add: duyệt từng bit của `b`, nếu bit bằng 1 thì XOR `a` vào kết quả; sau mỗi bước nhân `a` với `x` (dịch trái 1 bit) và XOR với đa thức tối giản khi bậc của `a` đạt n.

## Biên dịch và chạy

```
gcc gf_multiply.c -o gf_multiply
./gf_multiply
```

Ví dụ: `0x7 * 0xB = 0x4` trong GF(2^4), `0x57 * 0x83 = 0xC1` trong GF(2^8).
