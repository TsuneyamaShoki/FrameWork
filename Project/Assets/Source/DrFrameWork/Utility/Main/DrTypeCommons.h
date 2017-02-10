#pragma once

//! Include
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <memory>
//! type
typedef unsigned int        DrUint;
typedef int                 DrInt;
typedef float               Drfloat;
typedef double              Drdoble;
typedef wchar_t             DrLChar;
typedef char                DrChar;
typedef unsigned char       DrByte;
typedef short               DrShort;
typedef unsigned short      DrUshort;
typedef bool                DrBool;
typedef std::string         DrString;

typedef char                DrS8;
typedef unsigned char       DrU8;
typedef short               DrS16;
typedef unsigned short      DrU16;
typedef int					DrS32;
typedef unsigned int		DrU32;
typedef long long           DrS64;
typedef unsigned long long  DrU64;
typedef float               DrF32;
typedef double              DrF64;

typedef DrU64				DR_HASH;

#if USE_EASTL
#define tstl               eastl
#else
#define tstl               std
#endif

#define DrList              tstl::list
#define DrVector            tstl::vector
#define DrStack             tstl::stack
#define DrUniquePtr			std::unique_ptr
#define DrSharedPtr			std::shared_ptr
#define DrWeakPtr			std::weak_ptr
#define DrMap               std::unordered_map

#define DR_TRUE             true
#define DR_FALSE            false


