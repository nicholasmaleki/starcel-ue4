#pragma once
// Suppress warnings for Boost/MPFR/GMP headers
#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4668) // '__GNUC__' not defined
    #pragma warning(disable: 4146) // unary minus applied to unsigned type
    #pragma warning(disable: 4800) // implicit int->bool conversion
    #pragma warning(disable: 26812) // unscoped enum
    #pragma warning(disable: 26495) // uninitialized member
    #pragma warning(disable: 26451) // arithmetic overflow
#endif

// Unreal defines this
#ifdef check
#undef check
#endif
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/mpfr.hpp>
#include <gmp.h>
#include <sstream>

#ifdef _MSC_VER
    #pragma warning(pop)
#endif