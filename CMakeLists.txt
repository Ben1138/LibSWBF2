cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0079 NEW)

project(LibSWBF2_Project)

# Use folders for generators that supports them (VS, XCode, ...)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# SETTINGS
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# produce relative code adresses, necessary for shared libs
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(LibSWBF2 STATIC)

set(GLM_DIR "${PROJECT_SOURCE_DIR}/ThirdParty/glm")
set(FMT_DIR "${PROJECT_SOURCE_DIR}/ThirdParty/fmt")

add_subdirectory(${GLM_DIR} "${CMAKE_CURRENT_BINARY_DIR}/glm")
add_subdirectory(${FMT_DIR} "${CMAKE_CURRENT_BINARY_DIR}/fmt")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/include")
target_include_directories(LibSWBF2 PRIVATE ${INC_DIR} "${INC_DIR}/LibSWBF2/DirectX" "${INC_DIR}/LibSWBF2/DirectX/detex")

target_link_libraries(LibSWBF2 glm)
target_link_libraries(LibSWBF2 fmt)

target_precompile_headers(LibSWBF2 PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${INC_DIR}/LibSWBF2/pch.h>")
target_compile_definitions(LibSWBF2 PUBLIC MEMORY_MAPPED_READER)
target_compile_definitions(LibSWBF2 PRIVATE LOOKUP_CSV_PATH="${PROJECT_SOURCE_DIR}/lookup.csv")

if (UNIX)
  target_compile_options(LibSWBF2 PUBLIC -Wno-attributes)
  #target_compile_options(LibSWBF2 PUBLIC -Wno-deprecated-volatile)

  # Per convention, in UNIX shared libraries start with a lower 
  # case "lib" prefix, which would result in "libLibSWBF2". 
  # To circumvent that, just change the file output name accordingly.
  set_target_properties(LibSWBF2 PROPERTIES OUTPUT_NAME "SWBF2")
endif(UNIX)

if(MSVC)
  # Enable multi processor compilation for VS projects
  target_compile_options(LibSWBF2 PRIVATE "/MP")
endif()

# Just for folder display in generated project
# TODO: There is probably a way to do this procedurally
source_group("Source" REGULAR_EXPRESSION "${SRC_DIR}/*")
source_group("Source/DirectX" REGULAR_EXPRESSION "${SRC_DIR}/DirectX/*")
source_group("Source/Logging" REGULAR_EXPRESSION "${SRC_DIR}/Logging/*")
source_group("Source/Types" REGULAR_EXPRESSION "${SRC_DIR}/Types/*")
source_group("Source/Wrappers" REGULAR_EXPRESSION "${SRC_DIR}/Wrappers/*")
source_group("Source/Chunks" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/*")
source_group("Source/Chunks/LVL" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/*")
source_group("Source/Chunks/LVL/coll" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/coll/*")
source_group("Source/Chunks/LVL/common" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/common/*")
source_group("Source/Chunks/LVL/config" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/config/*")
source_group("Source/Chunks/LVL/gmod" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/gmod/*")
source_group("Source/Chunks/LVL/Locl" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/Locl/*")
source_group("Source/Chunks/LVL/modl" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/modl/*")
source_group("Source/Chunks/LVL/prim" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/prim/*")
source_group("Source/Chunks/LVL/scr_" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/scr_/*")
source_group("Source/Chunks/LVL/skel" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/skel/*")
source_group("Source/Chunks/LVL/sound" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/sound/*")
source_group("Source/Chunks/LVL/tern" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/tern/*")
source_group("Source/Chunks/LVL/tex_" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/tex_/*")
source_group("Source/Chunks/LVL/wrld" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/wrld/*")
source_group("Source/Chunks/LVL/zaa_" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/zaa_/*")
source_group("Source/Chunks/LVL/zaf_" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/zaf_/*")
source_group("Source/Chunks/MSH" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/MSH/*")
source_group("Source/Chunks/TERR" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/TERR/*")
source_group("Source/Chunks/LVL/plan" REGULAR_EXPRESSION "${SRC_DIR}/Chunks/LVL/plan/*")

target_sources(LibSWBF2 PRIVATE 

  # Root
  "${SRC_DIR}/API.cpp"
  "${SRC_DIR}/Container.cpp"
  "${SRC_DIR}/dllmain.cpp"
  "${SRC_DIR}/Hashing.cpp"
  "${SRC_DIR}/InternalHelpers.cpp"

  # IO
  "${SRC_DIR}/IO/StreamReader.cpp"
  "${SRC_DIR}/IO/MemoryMappedReader.cpp"
  "${SRC_DIR}/IO/FileWriter.cpp"

  # DirectX
  "${SRC_DIR}/DirectX/DXHelpers.cpp"
  "${SRC_DIR}/DirectX/DXTexCrossPlat.cpp"
  "${SRC_DIR}/DirectX/DXTexCrossPlatConverters.cpp"
  "${SRC_DIR}/DirectX/detex/decompress-bc.c"
  "${SRC_DIR}/DirectX/detex/division-tables.c"

  # Sound
  "${SRC_DIR}/Audio/IMAADPCMDecoder.cpp"  
  "${SRC_DIR}/Audio/PCM16Decoder.cpp"  

  # Logging
  "${SRC_DIR}/Logging/Logger.cpp"
  "${SRC_DIR}/Logging/LoggerEntry.cpp"

  # Types
  "${SRC_DIR}/Types/Animation.cpp"
  "${SRC_DIR}/Types/BoneFrames.cpp"
  "${SRC_DIR}/Types/BoneWeight.cpp"
  "${SRC_DIR}/Types/Color4.cpp"
  "${SRC_DIR}/Types/Color4u8.cpp"
  "${SRC_DIR}/Types/Enums.cpp"
  "${SRC_DIR}/Types/LibString.cpp"
  "${SRC_DIR}/Types/List.cpp"
  "${SRC_DIR}/Types/LocalizeEntry.cpp"
  "${SRC_DIR}/Types/Matrix3x3.cpp"
  "${SRC_DIR}/Types/RotationFrame.cpp"
  "${SRC_DIR}/Types/SoundBankHeader.cpp"
  "${SRC_DIR}/Types/SoundClip.cpp"
  "${SRC_DIR}/Types/TerrainBufferEntry.cpp"
  "${SRC_DIR}/Types/TranslationFrame.cpp"
  "${SRC_DIR}/Types/Vector2.cpp"
  "${SRC_DIR}/Types/Vector3.cpp"
  "${SRC_DIR}/Types/Vector3u8.cpp"
  "${SRC_DIR}/Types/Vector4.cpp"
  "${SRC_DIR}/Types/WorldAnimationKey.cpp"
  "${SRC_DIR}/Types/Planning.cpp"

  # Wrappers
  "${SRC_DIR}/Wrappers/AnimationBank.cpp"
  "${SRC_DIR}/Wrappers/AnimationSkeleton.cpp"
  "${SRC_DIR}/Wrappers/CollisionMesh.cpp"
  "${SRC_DIR}/Wrappers/CollisionPrimitive.cpp"
  "${SRC_DIR}/Wrappers/Config.cpp"
  "${SRC_DIR}/Wrappers/EntityClass.cpp"
  "${SRC_DIR}/Wrappers/Instance.cpp"
  "${SRC_DIR}/Wrappers/Level.cpp"
  "${SRC_DIR}/Wrappers/Localization.cpp"
  "${SRC_DIR}/Wrappers/Material.cpp"
  "${SRC_DIR}/Wrappers/Model.cpp"
  "${SRC_DIR}/Wrappers/Script.cpp"
  "${SRC_DIR}/Wrappers/Segment.cpp"
  "${SRC_DIR}/Wrappers/Sound.cpp"
  "${SRC_DIR}/Wrappers/SoundBank.cpp"
  "${SRC_DIR}/Wrappers/Terrain.cpp"
  "${SRC_DIR}/Wrappers/Texture.cpp"
  "${SRC_DIR}/Wrappers/World.cpp"
  "${SRC_DIR}/Wrappers/SoundStream.cpp"
  "${SRC_DIR}/Wrappers/PlanSet.cpp"


  # Chunks
  "${SRC_DIR}/Chunks/BaseChunk.cpp"
  "${SRC_DIR}/Chunks/GenericChunk.cpp"
  "${SRC_DIR}/Chunks/HeaderNames.cpp"
  "${SRC_DIR}/Chunks/RawData.cpp"
  "${SRC_DIR}/Chunks/STR.cpp"
  "${SRC_DIR}/Chunks/STRMULT.cpp"

  # LVL
  "${SRC_DIR}/Chunks/LVL/LVL.cpp"
  "${SRC_DIR}/Chunks/LVL/lvl_.cpp"

  "${SRC_DIR}/Chunks/LVL/coll/coll.cpp"
  "${SRC_DIR}/Chunks/LVL/coll/coll.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/coll/POSI.cpp"
  "${SRC_DIR}/Chunks/LVL/coll/TREE.cpp"
  "${SRC_DIR}/Chunks/LVL/coll/TREE.LEAF.cpp"
  "${SRC_DIR}/Chunks/LVL/coll/TREE.NODE.cpp"

  "${SRC_DIR}/Chunks/LVL/common/GenericClass.cpp"
  "${SRC_DIR}/Chunks/LVL/common/PROP.cpp"

  "${SRC_DIR}/Chunks/LVL/config/config.NAME.cpp"
  "${SRC_DIR}/Chunks/LVL/config/ConfigChunk.cpp"
  "${SRC_DIR}/Chunks/LVL/config/DATA.cpp"
  "${SRC_DIR}/Chunks/LVL/config/float.DATA.cpp"
  "${SRC_DIR}/Chunks/LVL/config/SCOP.cpp"
  "${SRC_DIR}/Chunks/LVL/config/string.DATA.cpp"

  "${SRC_DIR}/Chunks/LVL/gmod/gmod.cpp"

  "${SRC_DIR}/Chunks/LVL/Locl/Locl.cpp"
  "${SRC_DIR}/Chunks/LVL/Locl/Locl.BODY.cpp"

  "${SRC_DIR}/Chunks/LVL/modl/BMAP.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/IBUF.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/LVL.modl.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/modl.segm.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/modl.VBUF.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/MTRL.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/segm.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/SKIN.cpp"
  "${SRC_DIR}/Chunks/LVL/modl/TNAM.cpp"

  "${SRC_DIR}/Chunks/LVL/prim/MASK.cpp"
  "${SRC_DIR}/Chunks/LVL/prim/prim.cpp"
  "${SRC_DIR}/Chunks/LVL/prim/prim.DATA.cpp"
  "${SRC_DIR}/Chunks/LVL/prim/prim.INFO.cpp"

  "${SRC_DIR}/Chunks/LVL/scr_/scr_.cpp"
  "${SRC_DIR}/Chunks/LVL/scr_/scr_.INFO.cpp"

  "${SRC_DIR}/Chunks/LVL/skel/skel.cpp"
  "${SRC_DIR}/Chunks/LVL/skel/skel.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/skel/skel.XFRM.cpp"

  "${SRC_DIR}/Chunks/LVL/sound/StreamList.cpp"
  "${SRC_DIR}/Chunks/LVL/sound/Stream.cpp"
  "${SRC_DIR}/Chunks/LVL/sound/StreamInfo.cpp"
  "${SRC_DIR}/Chunks/LVL/sound/SoundBankList.cpp"
  "${SRC_DIR}/Chunks/LVL/sound/SampleBankData.cpp"
  "${SRC_DIR}/Chunks/LVL/sound/SampleBank.cpp"
  "${SRC_DIR}/Chunks/LVL/sound/SampleBankInfo.cpp"
  "${SRC_DIR}/Chunks/LVL/sound/_pad.cpp"
  "${SRC_DIR}/Chunks/LVL/sound/StreamData.cpp"

  "${SRC_DIR}/Chunks/LVL/tern/DTEX.cpp"
  "${SRC_DIR}/Chunks/LVL/tern/LTEX.cpp"
  "${SRC_DIR}/Chunks/LVL/tern/PCHS.cpp"
  "${SRC_DIR}/Chunks/LVL/tern/PTCH.cpp"
  "${SRC_DIR}/Chunks/LVL/tern/PTCH.IBUF.cpp"
  "${SRC_DIR}/Chunks/LVL/tern/PTCH.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/tern/PTCH.VBUF.cpp"
  "${SRC_DIR}/Chunks/LVL/tern/tern.cpp"
  "${SRC_DIR}/Chunks/LVL/tern/tern.INFO.cpp"

  "${SRC_DIR}/Chunks/LVL/tex_/BODY.cpp"
  "${SRC_DIR}/Chunks/LVL/tex_/FACE.cpp"
  "${SRC_DIR}/Chunks/LVL/tex_/FMT_.cpp"
  "${SRC_DIR}/Chunks/LVL/tex_/FMT_.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/tex_/LVL_.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/tex_/tex_.cpp"
  "${SRC_DIR}/Chunks/LVL/tex_/tex_.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/tex_/tex_.LVL_.cpp"

  "${SRC_DIR}/Chunks/LVL/wrld/anim.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/anmg.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/anmh.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/inst.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/regn.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/SIZE.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/wrld.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/wrld.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/XFRM.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/WorldAnimKeyChunk.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/anim.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/anmg.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/anmh.INFO.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/BARR.cpp"
  "${SRC_DIR}/Chunks/LVL/wrld/Hint.cpp"

  "${SRC_DIR}/Chunks/LVL/zaa_/BIN_.cpp"
  "${SRC_DIR}/Chunks/LVL/zaa_/MINA.cpp"
  "${SRC_DIR}/Chunks/LVL/zaa_/TADA.cpp"
  "${SRC_DIR}/Chunks/LVL/zaa_/TNJA.cpp"
  "${SRC_DIR}/Chunks/LVL/zaa_/zaa_.cpp"

  "${SRC_DIR}/Chunks/LVL/zaf_/BIN_.cpp"
  "${SRC_DIR}/Chunks/LVL/zaf_/LEKS.cpp"
  "${SRC_DIR}/Chunks/LVL/zaf_/TNOJ.cpp"
  "${SRC_DIR}/Chunks/LVL/zaf_/zaf_.cpp"

  # MSH
  "${SRC_DIR}/Chunks/MSH/ANM2.cpp"
  "${SRC_DIR}/Chunks/MSH/ATRB.cpp"
  "${SRC_DIR}/Chunks/MSH/BBOX.cpp"
  "${SRC_DIR}/Chunks/MSH/CYCL.cpp"
  "${SRC_DIR}/Chunks/MSH/ENVL.cpp"
  "${SRC_DIR}/Chunks/MSH/FLGS.cpp"
  "${SRC_DIR}/Chunks/MSH/FRAM.cpp"
  "${SRC_DIR}/Chunks/MSH/GEOM.cpp"
  "${SRC_DIR}/Chunks/MSH/KFR3.cpp"
  "${SRC_DIR}/Chunks/MSH/MATD.cpp"
  "${SRC_DIR}/Chunks/MSH/MATI.cpp"
  "${SRC_DIR}/Chunks/MSH/MATL.cpp"
  "${SRC_DIR}/Chunks/MSH/MNDX.cpp"
  "${SRC_DIR}/Chunks/MSH/MODL.cpp"
  "${SRC_DIR}/Chunks/MSH/MSH.cpp"
  "${SRC_DIR}/Chunks/MSH/MSH.DATA.cpp"
  "${SRC_DIR}/Chunks/MSH/MSH2.cpp"
  "${SRC_DIR}/Chunks/MSH/MTYP.cpp"
  "${SRC_DIR}/Chunks/MSH/NRML.cpp"
  "${SRC_DIR}/Chunks/MSH/POSL.cpp"
  "${SRC_DIR}/Chunks/MSH/SEGM.cpp"
  "${SRC_DIR}/Chunks/MSH/SHVO.cpp"
  "${SRC_DIR}/Chunks/MSH/SINF.cpp"
  "${SRC_DIR}/Chunks/MSH/STRP.cpp"
  "${SRC_DIR}/Chunks/MSH/SWCI.cpp"
  "${SRC_DIR}/Chunks/MSH/TRAN.cpp"
  "${SRC_DIR}/Chunks/MSH/UV0L.cpp"
  "${SRC_DIR}/Chunks/MSH/WGHT.cpp"

  # TERR
  "${SRC_DIR}/Chunks/TERR/TERR.cpp"

  # PLAN
  "${SRC_DIR}/Chunks/LVL/plan/plan.cpp"
  "${SRC_DIR}/Chunks/LVL/plan/plnp.cpp"
)

