cmake_minimum_required(VERSION 3.14)
project(korvahk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(string_theory REQUIRED)

set(KORVAHK_PLASMA_TYPE HuruMOUL CACHE STRING "Plasma engine to build Korvahk for.")
set_property(CACHE KORVAHK_PLASMA_TYPE PROPERTY STRINGS HuruMOUL LegacyMOUL TPotS)

if(KORVAHK_PLASMA_TYPE STREQUAL HuruMOUL)
    set(PLASMA_MOUL TRUE)
    set(PLASMA_TARRAY_IS_VECTOR TRUE)
    set(PLASMA_ATOMIC_REFCOUNT TRUE)
    set(PLASMA_HAVE_STRING_THEORY TRUE)
elseif(KORVAHK_PLASMA_TYPE STREQUAL LegacyMOUL)
    set(PLASMA_MOUL TRUE)
    set(PLASMA_WIN32_BOOLS TRUE)
elseif(KORVAHK_PLASMA_TYPE STREQUAL TPotS)
    set(PLASMA_TPOTS TRUE)
    set(PLASMA_WIN32_BOOLS TRUE)
else()
    # TODO: die
endif()

add_library(plasma OBJECT)
set_target_properties(plasma PROPERTIES LINKER_LANGUAGE CXX)
target_sources(plasma
    PUBLIC
        "${PLASMA_CONFIG_PATH}"

        "src/Plasma/BitVector.h"
        "src/Plasma/Creatable.h"
        "src/Plasma/CreatableIDs.h"
        "src/Plasma/Dispatch.h"
        "src/Plasma/Key.h"
        "src/Plasma/KeyedObject.h"
        "src/Plasma/Message.h"
        "src/Plasma/NetApp.h"
        "src/Plasma/Pipeline.h"
        "src/Plasma/RefCount.h"
        "src/Plasma/ResMgr.h"
        "src/Plasma/TArray.h"
        "src/Plasma/Types.h"
)
target_include_directories(plasma PUBLIC "src")
target_link_libraries(plasma PUBLIC string_theory::string_theory)

configure_file("cmake/plConfig.inc" "${PROJECT_BINARY_DIR}/plConfig.h")
target_include_directories(plasma PUBLIC "${PROJECT_BINARY_DIR}")

add_library(korvahk SHARED)
target_sources(korvahk
    PRIVATE
        "src/Korvahk/DLLMain.cpp"
        "src/Korvahk/Plugin.h"
        "src/Korvahk/PluginCore.cpp"
)
target_link_libraries(korvahk
    PRIVATE
        plasma
)
