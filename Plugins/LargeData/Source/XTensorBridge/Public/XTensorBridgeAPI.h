#pragma once

#ifdef _WIN32
    #define XTENSOR_API __declspec(dllexport)
#else
    #define XTENSOR_API
#endif

extern "C"
{
    XTENSOR_API void XTensor_SmokeTest();
}
