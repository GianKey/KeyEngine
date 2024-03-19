#pragma once

#ifdef KEY_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <Key/Core/Base.h>
#include <Key/Core/Log.h>
#include <Key/Core/Events/Event.h>

// Math
#include <Key/Core/Math/Mat4.h>
