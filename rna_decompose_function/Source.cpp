#include <stdio.h>

/// <summary>
/// 
/// </summary>
/// <param name="code">- format: ?? 00 00 00</param>
/// <returns>Nucl letter</returns>
char getNuclByCode(unsigned char code) {
    if (code == 0xC0) return 'G'; // 11 00 00 00
    if (code == 0x80) return 'C'; // 10 00 00 00
    if (code == 0x40) return 'U'; // 01 00 00 00
    if (code == 0x00) return 'A'; // 00 00 00 00
    return 'E';
}

/// <summary>
/// Get nucl letter from unsigned char array element by index
/// </summary>
/// <param name="arrPart">- UnsChar with 4 nucls in it</param>
/// <param name="idx">- Index of the nucl in char (0 - 3)</param>
/// <returns>Nucl letter</returns>
char getNucl(unsigned char arrPart, int idx) {
    if (idx < 0 || idx > 3) return 'E'; // error
    arrPart <<= (2 * idx);
    return getNuclByCode((0xC0 & arrPart));
}


int main() {

    // Tests:
    unsigned char test0 = 0x72; // 01 11 00 10 - U G A C
    unsigned char test1 = 0x00; // 00 00 00 00 - G G G G
    unsigned char test2 = 0xff; // 11 11 11 11 - A A A A
    
    for (int i = 0; i < 4; i++) {
        printf("%c ", getNucl(test0, i)); // U G A C 
    }

    printf("\n%c", getNucl(test0, 4)); // E

    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%c ", getNucl(test1, i)); // A A A A
    }

    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%c ", getNucl(test2, i)); // G G G G
    }

    return 0;
}
