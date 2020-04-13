// File name: "EnumToString.cpp"
#include "enums.h"
#include "types.h"
#include "Log.hpp"
/// The strings associated with the enums are gererated here
/////////////////////////////////////////////////////////////////////
#define GENERATE_ENUM_STRINGS  // Start string generation

#include "enums.h"           
#include "types.h"
//#include "AnotherOne.h"
#undef GENERATE_ENUM_STRINGS   // Stop string generation 

structlog LOGCFG = {};