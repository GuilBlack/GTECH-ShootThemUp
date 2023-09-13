#pragma once

#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <type_traits>
#include <memory>
#include <sstream>
#include <string>
#include <cassert>
#include <debugapi.h>
#include <cmath>

#define DBOUT( s )            \
{                             \
   std::stringstream ss;    \
   ss << s;                   \
   OutputDebugStringA( ss.str().c_str() );  \
}