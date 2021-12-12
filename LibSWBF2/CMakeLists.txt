cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0079 NEW)

project(LibSWBF2)

# SETTINGS
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# produce relative code adresses, necessary for shared libs
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(SWBF2 SHARED)

set(GLM_DIR "${PROJECT_SOURCE_DIR}/../ThirdParty/glm")
set(FMT_DIR "${PROJECT_SOURCE_DIR}/../ThirdParty/fmt")

add_subdirectory(${GLM_DIR} "${CMAKE_CURRENT_BINARY_DIR}/glm")
add_subdirectory(${FMT_DIR} "${CMAKE_CURRENT_BINARY_DIR}/fmt")

target_include_directories(SWBF2 PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(SWBF2 glm)
target_link_libraries(SWBF2 fmt)

target_precompile_headers(SWBF2 PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${PROJECT_SOURCE_DIR}/pch.h>")
target_compile_definitions(SWBF2 PUBLIC MEMORY_MAPPED_READER)

if (UNIX)
  target_compile_options(SWBF2 PUBLIC -Wno-attributes)
  #target_compile_options(SWBF2 PUBLIC -Wno-deprecated-volatile)

  if (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    target_compile_options(SWBF2 PUBLIC -O3)
  endif()
endif(UNIX)

if(MSVC)
  # Enable multi processor compilation for VS projects
  target_compile_options(SWBF2 PRIVATE "/MP")
endif()

target_sources(SWBF2 PRIVATE 

  # Root
  "${PROJECT_SOURCE_DIR}/API.cpp"
  "${PROJECT_SOURCE_DIR}/Container.cpp"
  "${PROJECT_SOURCE_DIR}/dllmain.cpp"
  "${PROJECT_SOURCE_DIR}/FileReader.cpp"
  "${PROJECT_SOURCE_DIR}/FileReaderMemMapped.cpp"
  "${PROJECT_SOURCE_DIR}/FileWriter.cpp"
  "${PROJECT_SOURCE_DIR}/Hashing.cpp"
  "${PROJECT_SOURCE_DIR}/InternalHelpers.cpp"

  # DirectX
  "${PROJECT_SOURCE_DIR}/DirectX/DXHelpers.cpp"
  "${PROJECT_SOURCE_DIR}/DirectX/DXTexCrossPlat.cpp"
  "${PROJECT_SOURCE_DIR}/DirectX/DXTexCrossPlatConverters.cpp"
  "${PROJECT_SOURCE_DIR}/DirectX/detex/decompress-bc.c"
  "${PROJECT_SOURCE_DIR}/DirectX/detex/division-tables.c"

  # Logging
  "${PROJECT_SOURCE_DIR}/Logging/Logger.cpp"
  "${PROJECT_SOURCE_DIR}/Logging/LoggerEntry.cpp"

  # Types
  "${PROJECT_SOURCE_DIR}/Types/Animation.cpp"
  "${PROJECT_SOURCE_DIR}/Types/BoneFrames.cpp"
  "${PROJECT_SOURCE_DIR}/Types/BoneWeight.cpp"
  "${PROJECT_SOURCE_DIR}/Types/Color4.cpp"
  "${PROJECT_SOURCE_DIR}/Types/Color4u8.cpp"
  "${PROJECT_SOURCE_DIR}/Types/Enums.cpp"
  "${PROJECT_SOURCE_DIR}/Types/LibString.cpp"
  "${PROJECT_SOURCE_DIR}/Types/List.cpp"
  "${PROJECT_SOURCE_DIR}/Types/LocalizeEntry.cpp"
  "${PROJECT_SOURCE_DIR}/Types/Matrix3x3.cpp"
  "${PROJECT_SOURCE_DIR}/Types/RotationFrame.cpp"
  "${PROJECT_SOURCE_DIR}/Types/SoundBankHeader.cpp"
  "${PROJECT_SOURCE_DIR}/Types/SoundClip.cpp"
  "${PROJECT_SOURCE_DIR}/Types/TerrainBufferEntry.cpp"
  "${PROJECT_SOURCE_DIR}/Types/TranslationFrame.cpp"
  "${PROJECT_SOURCE_DIR}/Types/Vector2.cpp"
  "${PROJECT_SOURCE_DIR}/Types/Vector3.cpp"
  "${PROJECT_SOURCE_DIR}/Types/Vector3u8.cpp"
  "${PROJECT_SOURCE_DIR}/Types/Vector4.cpp"

  # Wrappers
  "${PROJECT_SOURCE_DIR}/Wrappers/AnimationBank.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/CollisionMesh.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/CollisionPrimitive.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Config.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/EntityClass.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Instance.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Level.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Localization.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Material.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Model.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Script.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Segment.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Sound.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/SoundBank.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Terrain.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/Texture.cpp"
  "${PROJECT_SOURCE_DIR}/Wrappers/World.cpp"

  # Chunks
  "${PROJECT_SOURCE_DIR}/Chunks/BaseChunk.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/GenericChunk.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/HeaderNames.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/RawData.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/STR.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/STRMULT.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/BNK/BNK.cpp"

  # LVL
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/LVL.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/lvl_.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/coll/coll.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/coll/coll.INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/coll/POSI.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/coll/TREE.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/coll/TREE.LEAF.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/coll/TREE.NODE.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/common/GenericClass.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/common/PROP.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/config/config.NAME.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/config/ConfigChunk.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/config/DATA.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/config/float.DATA.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/config/SCOP.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/config/string.DATA.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/gmod/gmod.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/Locl/Locl.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/Locl/Locl.BODY.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/BMAP.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/IBUF.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/LVL.modl.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/modl.segm.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/modl.VBUF.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/MTRL.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/segm.INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/SKIN.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/modl/TNAM.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/prim/MASK.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/prim/prim.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/prim/prim.DATA.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/prim/prim.INFO.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/scr_/scr_.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/scr_/scr_.INFO.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/skel/skel.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/skel/skel.INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/skel/skel.XFRM.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/sound/_pad.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/sound/emo_.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/DTEX.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/LTEX.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/PCHS.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/PTCH.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/PTCH.IBUF.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/PTCH.INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/PTCH.VBUF.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/tern.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tern/tern.INFO.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tex_/BODY.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tex_/FACE.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tex_/FMT_.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tex_/FMT_.INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tex_/LVL_.INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tex_/tex_.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tex_/tex_.INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/tex_/tex_.LVL_.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/wrld/anim.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/wrld/anmg.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/wrld/inst.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/wrld/regn.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/wrld/SIZE.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/wrld/wrld.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/wrld/wrld.INFO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/wrld/XFRM.cpp"

  "${PROJECT_SOURCE_DIR}/Chunks/LVL/zaa_/BIN_.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/zaa_/MINA.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/zaa_/TADA.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/zaa_/TNJA.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/LVL/zaa_/zaa_.cpp"

  # MSH
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/ANM2.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/ATRB.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/BBOX.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/CYCL.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/ENVL.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/FLGS.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/FRAM.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/GEOM.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/KFR3.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MATD.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MATI.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MATL.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MNDX.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MODL.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MSH.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MSH.DATA.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MSH2.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/MTYP.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/NRML.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/POSL.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/SEGM.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/SHVO.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/SINF.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/STRP.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/SWCI.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/TRAN.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/UV0L.cpp"
  "${PROJECT_SOURCE_DIR}/Chunks/MSH/WGHT.cpp"

  # TERR
  "${PROJECT_SOURCE_DIR}/Chunks/TERR/TERR.cpp"
)