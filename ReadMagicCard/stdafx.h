// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here

#include "OcvException.h"
#include "OcvImageHelper.h"
#include <opencv2\core.hpp>



// Ugly hacks here! Keep them in one place!

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE 1 //Vcpkg apparantly doesn't have the latest version of boost so suppress the version warnings for now.



//Read the README.md file before coding!
//https://github.com/klanderfri/ReadMagicCard/blob/master/README.md
