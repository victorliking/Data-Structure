#include "letter_hash.h"

unsigned int LetterHash::operator()( char const & key, int size ) {
    return (unsigned char)key % size;
}
