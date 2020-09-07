#include <stdio.h>

char getNuckByCode(unsigned char code) {
    if (code == 0xC0) return 'G'; // 11 00 00 00
    if (code == 0x80) return 'C'; // 10 00 00 00
    if (code == 0x40) return 'U'; // 01 00 00 00
    if (code == 0x00) return 'A'; // 00 00 00 00
}

char getNuck(unsigned char ch, int n) { // n - номер €чейки от 0 до 3
    if (n < 0 || n > 3) return 'E'; // error
    if (n == 0) { // mask - 11 00 00 00
        return getNuckByCode((0xC0 & ch));
    }
    if (n == 1) { // mask - 00 11 00 00
        return getNuckByCode((0x30 & ch) << (2 * n));
    }
    if (n == 2) { // mask - 00 00 11 00
        return getNuckByCode((0x0C & ch) << (2 * n));
    }
    if (n == 3) { // mask - 00 00 00 11
        return getNuckByCode((0x03 & ch) << (2 * n));
    }
}

int main() {

    unsigned char test0 = 0x72; // 01 11 00 10 - U G A C
    unsigned char test1 = 0x00; // 00 00 00 00 - G G G G
    unsigned char test2 = 0xff; // 11 11 11 11 - A A A A
    
    for (int i = 0; i < 4; i++) {
        printf("%c ", getNuck(test0, i)); // U G A C 
    }

    printf("\n%c", getNuck(test0, 4)); // E

    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%c ", getNuck(test1, i)); // A A A A
    }

    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%c ", getNuck(test2, i)); // G G G G
    }

    return 0;
}
