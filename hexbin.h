#ifndef HEXBIN_H_
#define HEXBIN_H_

const unsigned char kInvalidHexChar = 0x80;

// Convert a hexadecimal char to nybble. The nybble is stored in the
// lower 4 bites of the unsigned char. If the character is not a valid
// hex char, the function returns kInvalidHexChar.
unsigned char HexCharToNybble(char ch);

#endif  // HEXBIN_H_
