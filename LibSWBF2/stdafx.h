#pragma once

#ifdef _WIN32
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Don't include rarely used windows stuff
#include <windows.h>
#endif

// TODO: Place additional headers to precompile here
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat3x3.hpp>
#include <fmt/core.h>
#include <fmt/format.h>
#include "DirectX/DXHelpers.h"
#include "req.h"