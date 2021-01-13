# - Try to find KMSMNSCMIXER library

#=============================================================================
# Copyright 2014 Kurento
#
#=============================================================================

set(PACKAGE_VERSION "0.0.1~3.g9967f42")
set(KMSMNSCMIXER_VERSION ${PACKAGE_VERSION})

message (STATUS "Looking for KMSMNSCMIXER: 0.0.1~3.g9967f42")

include (GenericFind)

generic_find (
  REQUIRED
  LIBNAME KMSCORE
  VERSION ^6.0.0
)

generic_find (
  REQUIRED
  LIBNAME KMSELEMENTS
  VERSION ^6.0.0
)

generic_find (
  REQUIRED
  LIBNAME KMSFILTERS
  VERSION ^6.0.0
)

set (REQUIRED_VARS
  KMSMNSCMIXER_VERSION
  KMSMNSCMIXER_INCLUDE_DIRS
  KMSMNSCMIXER_LIBRARY
  KMSMNSCMIXER_LIBRARIES
)

set (KMSMNSCMIXER_BINARY_DIR_PREFIX "build" CACHE PATH "Path prefix used to look for binary files")
set (KMSMNSCMIXER_SOURCE_DIR_PREFIX "" CACHE PATH "Path prefix used to look for source files")

set(KMSMNSCMIXER_INCLUDE_DIRS
  ${KMSCORE_INCLUDE_DIRS}
  ${KMSELEMENTS_INCLUDE_DIRS}
  ${KMSFILTERS_INCLUDE_DIRS}
)

if (NOT "mnscmixer.hpp mnscmixerInternal.hpp" STREQUAL " ")
  if (TARGET kmsmnscmixerinterface)
    set (KMSMNSCMIXER_INTERFACE_INCLUDE_DIR "${KMSMNSCMIXER_BINARY_DIR_PREFIX}/src/server/interface/generated-cpp")
  else ()
    find_path(KMSMNSCMIXER_INTERFACE_INCLUDE_DIR
      NAMES
        mnscmixer.hpp
        mnscmixerInternal.hpp
      PATH_SUFFIXES
        ${KMSMNSCMIXER_BINARY_DIR_PREFIX}/src/server/interface/generated-cpp
        kurento/modules/mnscmixer
    )
  endif ()

  list (APPEND KMSMNSCMIXER_INCLUDE_DIRS ${KMSMNSCMIXER_INTERFACE_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMIXER_INTERFACE_INCLUDE_DIR)
endif ()

if (NOT "mnscmixerImplFactory.hpp" STREQUAL "")
  if (TARGET kmsmnscmixerimpl)
    set (KMSMNSCMIXER_IMPLEMENTATION_INTERNAL_INCLUDE_DIR "${KMSMNSCMIXER_BINARY_DIR_PREFIX}/src/server/implementation/generated-cpp")
  else ()
    find_path(KMSMNSCMIXER_IMPLEMENTATION_INTERNAL_INCLUDE_DIR
      NAMES
        mnscmixerImplFactory.hpp
      PATH_SUFFIXES
        ${KMSMNSCMIXER_BINARY_DIR_PREFIX}/src/server/implementation/generated-cpp
        kurento/modules/mnscmixer
    )
  endif ()

  list (APPEND KMSMNSCMIXER_INCLUDE_DIRS ${KMSMNSCMIXER_IMPLEMENTATION_INTERNAL_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMIXER_IMPLEMENTATION_INTERNAL_INCLUDE_DIR)
endif ()

if (NOT "mnscmixerImpl.hpp" STREQUAL "")
  if (TARGET kmsmnscmixerimpl)
    set (KMSMNSCMIXER_IMPLEMENTATION_GENERATED_INCLUDE_DIR "${KMSMNSCMIXER_SOURCE_DIR_PREFIX}/src/server/implementation/objects")
  else ()
    find_path(KMSMNSCMIXER_IMPLEMENTATION_GENERATED_INCLUDE_DIR
      NAMES
        mnscmixerImpl.hpp
      PATH_SUFFIXES
        src/server/implementation/objects
        kurento/modules/mnscmixer
    )
  endif ()

  list (APPEND KMSMNSCMIXER_INCLUDE_DIRS ${KMSMNSCMIXER_IMPLEMENTATION_GENERATED_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMIXER_IMPLEMENTATION_GENERATED_INCLUDE_DIR)
endif()

if (NOT "" STREQUAL "")
  if (TARGET kmsmnscmixerimpl)
    set (KMSMNSCMIXER_IMPLEMENTATION_EXTRA_INCLUDE_DIR "${KMSMNSCMIXER_SOURCE_DIR_PREFIX}/")
  else ()
    find_path(KMSMNSCMIXER_IMPLEMENTATION_EXTRA_INCLUDE_DIR
      NAMES
        
      PATH_SUFFIXES
        
        kurento/modules/mnscmixer
    )
  endif ()

  list (APPEND KMSMNSCMIXER_INCLUDE_DIRS ${KMSMNSCMIXER_IMPLEMENTATION_EXTRA_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMIXER_IMPLEMENTATION_EXTRA_INCLUDE_DIR)
endif ()

if (NOT "" STREQUAL "")
  if (TARGET kmsmnscmixerinterface)
    set (KMSMNSCMIXER_INTERFACE_EXTRA_INCLUDE_DIR "${KMSMNSCMIXER_SOURCE_DIR_PREFIX}/")
  else ()
    find_path(KMSMNSCMIXER_INTERFACE_EXTRA_INCLUDE_DIR
      NAMES
        
      PATH_SUFFIXES
        
        kurento/modules/mnscmixer
    )
  endif()

  list (APPEND KMSMNSCMIXER_INCLUDE_DIRS ${KMSMNSCMIXER_INTERFACE_EXTRA_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMIXER_INTERFACE_EXTRA_INCLUDE_DIR)
endif ()

if (TARGET kmsmnscmixerimpl)
  set (KMSMNSCMIXER_LIBRARY kmsmnscmixerimpl)
else ()
  find_library (KMSMNSCMIXER_LIBRARY
    NAMES
      kmsmnscmixerimpl
    PATH_SUFFIXES
      ${KMSMNSCMIXER_BINARY_DIR_PREFIX}/src/server
  )
endif()

set (REQUIRED_LIBS "")
foreach (LIB ${REQUIRED_LIBS})
  string(FIND ${LIB} " " POS)

  if (${POS} GREATER 0)
    string(REPLACE " " ";" REQUIRED_LIB_LIST ${LIB})
    include (CMakeParseArguments)
    cmake_parse_arguments("PARAM" "" "LIBNAME" "" ${REQUIRED_LIB_LIST})

    if (DEFINED PARAM_LIBNAME)
      generic_find (${REQUIRED_LIB_LIST} REQUIRED)
      set (LIB_NAME ${PARAM_LIBNAME})
    else()
      string (SUBSTRING ${LIB} 0 ${POS} LIB_NAME)
      string (SUBSTRING ${LIB} ${POS} -1 LIB_VERSION)
      string (STRIP ${LIB_NAME} LIB_NAME)
      string (STRIP ${LIB_VERSION} LIB_VERSION)
      generic_find (LIBNAME ${LIB_NAME} REQUIRED VERSION "${LIB_VERSION}")
    endif()
  else ()
    string (STRIP ${LIB} LIB_NAME)
    generic_find (LIBNAME ${LIB_NAME} REQUIRED)
  endif ()
  list (APPEND REQUIRED_LIBRARIES ${${LIB_NAME}_LIBRARIES})
  list (APPEND KMSMNSCMIXER_INCLUDE_DIRS ${${LIB_NAME}_INCLUDE_DIRS})

endforeach()

set(KMSMNSCMIXER_INCLUDE_DIRS
  ${KMSMNSCMIXER_INCLUDE_DIRS}
  CACHE INTERNAL "Include directories for KMSMNSCMIXER library" FORCE
)

set (KMSMNSCMIXER_LIBRARIES
  ${KMSMNSCMIXER_LIBRARY}
  ${KMSCORE_LIBRARIES}
  ${KMSELEMENTS_LIBRARIES}
  ${KMSFILTERS_LIBRARIES}
  ${REQUIRED_LIBRARIES}
  CACHE INTERNAL "Libraries for KMSMNSCMIXER" FORCE
)

include (FindPackageHandleStandardArgs)

find_package_handle_standard_args(KMSMNSCMIXER
  FOUND_VAR
    KMSMNSCMIXER_FOUND
  REQUIRED_VARS
    ${REQUIRED_VARS}
  VERSION_VAR
    KMSMNSCMIXER_VERSION
)

mark_as_advanced(
  KMSMNSCMIXER_FOUND
  KMSMNSCMIXER_VERSION
  KMSMNSCMIXER_INTERFACE_INCLUDE_DIR
  KMSMNSCMIXER_IMPLEMENTATION_INTERNAL_INCLUDE_DIR
  KMSMNSCMIXER_IMPLEMENTATION_GENERATED_INCLUDE_DIR
  KMSMNSCMIXER_IMPLEMENTATION_EXTRA_INCLUDE_DIR
  KMSMNSCMIXER_INTERFACE_EXTRA_INCLUDE_DIR
  KMSMNSCMIXER_INCLUDE_DIRS
  KMSMNSCMIXER_LIBRARY
  KMSMNSCMIXER_LIBRARIES
)
