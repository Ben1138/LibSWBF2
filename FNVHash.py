import sys

def Hash(str):
    FNV_prime = 16777619
    offset_basis = 2166136261

    hash = offset_basis
    for c in str:
        c = ord(c)
        c |= 0x20

        # ensure 32 bit int
        c &= 0xffffffff

        hash ^= c
        hash &= 0xffffffff
        hash *= FNV_prime
        hash &= 0xffffffff

    return hash

hashval = Hash(sys.argv[1])
hex_str = hex(hashval)
hex_str_le_bytes = hex_str[8:10] + hex_str[6:8] + hex_str[4:6] + hex_str[2:4]

print(hashval, "(Hex: {}, LE byte-order hex: {})".format(hex_str[2:], hex_str_le_bytes))