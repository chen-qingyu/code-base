#include <stdio.h>

int main(void)
{
    const int chars_per_line = 64; // The number of characters per line
    const int chars_total = chars_per_line * 7; // There are 448 characters in total

    for (int i = chars_total - 1; i >= 0; i--) // i: 447, 446, 445, ..., 2, 1, 0.
    {
        if (i % chars_per_line) // Wrap every 64 characters
        {
            char time_digit = __TIME__[7 - i / 8 % 8]; // char: "0123456789:" -> ASCII: 48-58

            char selector = ">'txiZ^(~z?"[time_digit - '0'] + 1; // '0'->'>', '1'->''', '2'->'t'......, ':'->'?'
            /*
            for example:
            if time_digit is '0':
                then (time_digit - '0') is 0,
                get '>', which in ASCII is 62(0011 1110),
                add 1 to get 63(0011 1111),
                so, '0' -> 0011 1111.

            ```Python
            for time_digit in "0123456789:":
                selector = ord(">'txiZ^(~z?"[ord(time_digit) - ord('0')]) + 1
                print("'{}' -> ".format(time_digit)+"{:0>8b}".format(selector)[:4]+" "+"{:0>8b}".format(selector)[4:])
            ```

            selector table:

            '0' -> 0011 1111
            '1' -> 0010 1000
            '2' -> 0111 0101
            '3' -> 0111 1001
            '4' -> 0110 1010
            '5' -> 0101 1011
            '6' -> 0101 1111
            '7' -> 0010 1001
            '8' -> 0111 1111
            '9' -> 0111 1011
            ':' -> 0100 0000
            */

            char bitmap = ";;;====~$::199"[((i * 2) & 8) | (i / chars_per_line)];
            /*
            ((i * 2) & 8):
                if i = 4,5,6,7 + 8*k (k is integer):
                    result is 8
                else i = 0,1,2,3 + 8*k (k is integer):
                    result is 0

            (i / chars_per_line):
                result from 6 to 0

            ((i * 2) & 8) | (i / chars_per_line):
                result in integer closed interval [14, 0]

            So bitmap is in range '\0'(0000 0000) and ';'(0011 1011)

            ```Python
            i = 0
            for bitmap in ";;;====~$::199\0":
                print("[{:0>2}] {:2} -> ".format(i, (bitmap if bitmap != '\0' else "\\0")) +
                      "{:0>8b}".format(ord(bitmap))[:4]+" "+"{:0>8b}".format(ord(bitmap))[4:])
                i += 1
            ```

            ";;;====~$::199" in ASCII:

            [00] ;  -> 0011 1011
            [01] ;  -> 0011 1011
            [02] ;  -> 0011 1011
            [03] =  -> 0011 1101
            [04] =  -> 0011 1101
            [05] =  -> 0011 1101
            [06] =  -> 0011 1101
            [07] ~  -> 0111 1110
            [08] $  -> 0010 0100
            [09] :  -> 0011 1010
            [10] :  -> 0011 1010
            [11] 1  -> 0011 0001
            [12] 9  -> 0011 1001
            [13] 9  -> 0011 1001
            [14] \0 -> 0000 0000
            */

            if ((i & 2) == 0)
            {
                bitmap >>= 3; // Shift right 3 bits
            }
            bitmap &= 7; // Get lower 3 bits
            /*
            if i = 0,1,4,5 + 8*k (k is integer):
                get middle 3 bits(5,4,3) of bitmap
            else i = 2,3,6,7 + 8*k (k is integer):
                get lower 3 bits(2,1,0) of bitmap

            for example:
            if i is 447(‭1 1011 1111‬):
                ((i * 2) & 8) is 8
                (i / chars_per_line) is 6
                ((i * 2) & 8) | (i / chars_per_line) is 14
                get '\0'(0000 0000)
                (i & 2) is 1
                get lower 3 bits 000
                so bitmap is 0

            if i is 0(‭‭0000 0000):
                ((i * 2) & 8) is 0
                (i / chars_per_line) is 0
                ((i * 2) & 8) | (i / chars_per_line) is 0
                get ';'(0011 1011)
                (i & 2) is 0
                get middle 3 bits 111
                so bitmap is 7

            So, with i is 447, 446, 445, ..., 2, 1, 0:
                bitmap is 0, 0, 0, ..., 3, 7, 7.

            ```Python
            chars_per_line = 64
            chars_total = chars_per_line * 7
            for i in range(chars_total-1, 0-1, -1):
                bitmap = ord(";;;====~$::199\0"[((i * 2) & 8) | (i // chars_per_line)])
                if (i & 2) == 0:
                    bitmap >>= 3
                bitmap &= 7
                print(bitmap, end="")
                if i % 8 == 0:
                    print(" ", end="")
                    if i % 64 == 0:
                        print()
            ```

            00005577 00005577 00005577 00005577 00005577 00005577 00005577 00005577
            11775577 11775577 11775577 11775577 11775577 11775577 11775577 11775577
            11775577 11775577 11775577 11775577 11775577 11775577 11775577 11775577
            11665577 11665577 11665577 11665577 11665577 11665577 11665577 11665577
            22773377 22773377 22773377 22773377 22773377 22773377 22773377 22773377
            22773377 22773377 22773377 22773377 22773377 22773377 22773377 22773377
            44443377 44443377 44443377 44443377 44443377 44443377 44443377 44443377

            bitmap table:

            00005577
            11775577
            11775577
            11665577
            22773377
            22773377
            44443377

            seven-segment display, 7 is blank

            000055
            11  55
            11  55
            116655
            22  33
            22  33
            444433

            Wow!

            So, if time_digit is '0', then the selector is 0011 1111, means bits/segments 0,1,2,3,4,5 set.
                000055
                11  55
                11  55
                11  55
                22  33
                22  33
                444433

            If time_digit is '9', then the selector is 0111 1011, means bits/segments 0,1,3,4,5,6 set.
                000055
                11  55
                11  55
                116655
                    33
                    33
                444433

            That's interesting!
            */
            char c = selector >> bitmap;
            putchar((c & 1) ? '!' : ' ');
        }
        else
        {
            putchar('\n');
        }
    }

    return 0;
}
