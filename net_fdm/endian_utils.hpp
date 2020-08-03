
#include <array>
#include <algorithm>

bool is_big_endian()
{
   union {
      std::uint32_t i;
      char c[4];
   } bint = { 0x01020304 };

   return bint.c[0] == 1;
}

//-----------------------------------------------------------
// Template to swap bytes to/from big/little endian order
//
// source: Robust endianness conversion website
//-----------------------------------------------------------
template <typename T>
void swap_endian(T &val) {
   union U {
      T val;
      std::array<std::uint8_t, sizeof(T)> raw;
   } src, dst;

   src.val = val;
   std::reverse_copy(src.raw.begin(), src.raw.end(), dst.raw.begin());
   val = dst.val;
}

