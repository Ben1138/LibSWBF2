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

print(Hash(sys.argv[1]))