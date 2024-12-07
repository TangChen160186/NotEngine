#pragma once
#ifdef EXPORT
// Exports
#ifdef _MSC_VER
#define API __declspec(dllexport)
#else
#define API __attribute__((visibility("default")))
#endif
#else

// Imports
#ifdef _MSC_VER
#define API __declspec(dllimport)
#else
#define API
#endif
#endif
