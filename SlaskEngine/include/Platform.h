#pragma once

#if defined(_WIN32) || defined(_WIN64)
 #ifndef WINDOWS
  #define WINDOWS
  #ifndef PLATFORM
   #define PLATFORM
  #endif
 #endif
#endif


#if defined(__linux__) || defined(__linux) || defined(_linux) || defined(__LINUX__) || defined(__LINUX) || defined(_LINUX)
 #ifndef LINUX
  #define LINUX
  #ifndef UNIX
   #define UNIX
  #endif
  #ifndef PLATFORM
   #define PLATFORM
  #endif
 #endif
#endif


#if defined(__APPLE__)
 #ifndef MAC
  #define MAC
  #ifndef UNIX
   #define UNIX
  #endif
  #ifndef PLATFORM
   #define PLATFORM
  #endif
 #endif
#endif

#ifndef PLATFORM
 #error Compiling platform not recognized.
#endif
