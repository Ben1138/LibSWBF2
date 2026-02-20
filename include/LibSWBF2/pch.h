#pragma once

#ifdef WIN32
#include <LibSWBF2/targetver.h>
#define WIN32_LEAN_AND_MEAN             // Don't include rarely used windows stuff
#include <LibSWBF2/windows.h>
#endif

// TODO: Place additional headers to precompile here
#include <LibSWBF2/req.h>
#include <LibSWBF2/Types/Animation.h>
#include <LibSWBF2/Types/BoneFrames.h>
#include <LibSWBF2/Types/BoneWeight.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Types/LibString.h>
#include <LibSWBF2/Types/List.h>
#include <LibSWBF2/Types/LocalizeEntry.h>
#include <LibSWBF2/Types/Polygon.h>
#include <LibSWBF2/Types/RotationFrame.h>
#include <LibSWBF2/Types/SoundBankHeader.h>
#include <LibSWBF2/Types/SoundClip.h>
#include <LibSWBF2/Types/TerrainBufferEntry.h>
#include <LibSWBF2/Types/TranslationFrame.h>
#include <LibSWBF2/Types/Vector2.h>
#include <LibSWBF2/Types/Vector3.h>
#include <LibSWBF2/Types/Vector4.h>
#include <LibSWBF2/Types/Color4f.h>
#include <LibSWBF2/Types/Color4u8.h>
#include <LibSWBF2/Types/Matrix3x3.h>
#include <LibSWBF2/Types/List.h>
#include <LibSWBF2/Logging/Logger.h>
#include <LibSWBF2/Exceptions.h>
#include <LibSWBF2/DirectX/DXHelpers.h>

