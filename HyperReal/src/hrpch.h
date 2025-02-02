	#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "core-files/Core/log.h"
#include "core-files/Debug/Instrumentor.h"

#ifdef HR_PLATFORM_WINDOWS
	#include <Windows.h>
#endif