#pragma once

//Redefinicion de tipos by Aleix XD

typedef unsigned __int8 UINT_8;
typedef unsigned __int16 UINT_16;
typedef unsigned __int32 UINT_32;
typedef unsigned __int64 UINT_64;

typedef signed __int8 SINT_8;
typedef signed __int16 SINT_16;
typedef signed __int32 SINT_32;
typedef signed __int64 SINT_64;

//Puntero generico a void
typedef void* VOID_PTR;


//Este cambia de tamaño segun 32 bits o 64 bits
#ifdef WIN32
typedef UINT_32 UINT_Ptr;
#else
typedef UINT_64 UINT_Ptr;
#endif