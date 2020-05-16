
#include <climits>

//
// Source: https://stackoverflow.com/questions/105252/how-do-i-convert-between-big-endian-and-little-endian-values-in-c
//
// Example Usage:
// swap_endian<uint32_t>(42);
//
template <typename T>
T swap_endian(T u)
{
   static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

   union
   {
      T u;
      unsigned char u8[sizeof(T)];
   } source, dest;

   source.u = u;

   for (size_t k = 0; k < sizeof(T); k++)
      dest.u8[k] = source.u8[sizeof(T) - k - 1];

   return dest.u;
}
