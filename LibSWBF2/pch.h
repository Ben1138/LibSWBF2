#pragma once

#ifdef _WIN32
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Don't include rarely used windows stuff
#include <windows.h>
#endif

// TODO: Place additional headers to precompile here
#include "req.h"
#include "Types/Animation.h"
#include "Types/BoneFrames.h"
#include "Types/BoneWeight.h"
#include "Types/Enums.h"
#include "Types/LibString.h"
#include "Types/List.h"
#include "Types/LocalizeEntry.h"
#include "Types/Polygon.h"
#include "Types/RotationFrame.h"
#include "Types/SoundBankHeader.h"
#include "Types/SoundClip.h"
#include "Types/TerrainBufferEntry.h"
#include "Types/TranslationFrame.h"
#include "Types/Vector2.h"
#include "Types/Vector3.h"
#include "Types/Vector4.h"
#include "Types/Color4.h"
#include "Types/Color4u8.h"
#include "Types/Matrix3x3.h"
#include "Types/List.h"
#include "Logging/Logger.h"
#include "Exceptions.h"
#include "DirectX/DXHelpers.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat3x3.hpp>
#include <fmt/core.h>
#include <fmt/format.h>