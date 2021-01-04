# - Try to find KMSMNSCMODULE library

#=============================================================================
# Copyright 2014 Kurento
#
#=============================================================================

set(PACKAGE_VERSION "0.0.1~0.g3acb882")
set(KMSMNSCMODULE_VERSION ${PACKAGE_VERSION})

message (STATUS "Looking for KMSMNSCMODULE: 0.0.1~0.g3acb882")

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
  KMSMNSCMODULE_VERSION
  KMSMNSCMODULE_INCLUDE_DIRS
  KMSMNSCMODULE_LIBRARY
  KMSMNSCMODULE_LIBRARIES
)

set (KMSMNSCMODULE_BINARY_DIR_PREFIX "build" CACHE PATH "Path prefix used to look for binary files")
set (KMSMNSCMODULE_SOURCE_DIR_PREFIX "" CACHE PATH "Path prefix used to look for source files")

set(KMSMNSCMODULE_INCLUDE_DIRS
  ${KMSCORE_INCLUDE_DIRS}
  ${KMSELEMENTS_INCLUDE_DIRS}
  ${KMSFILTERS_INCLUDE_DIRS}
)

if (NOT "mnscmodule.hpp mnscmoduleInternal.hpp" STREQUAL " ")
  if (TARGET kmsmnscmoduleinterface)
    set (KMSMNSCMODULE_INTERFACE_INCLUDE_DIR "${KMSMNSCMODULE_BINARY_DIR_PREFIX}/src/server/interface/generated-cpp")
  else ()
    find_path(KMSMNSCMODULE_INTERFACE_INCLUDE_DIR
      NAMES
        mnscmodule.hpp
        mnscmoduleInternal.hpp
      PATH_SUFFIXES
        ${KMSMNSCMODULE_BINARY_DIR_PREFIX}/src/server/interface/generated-cpp
        kurento/modules/mnscmodule
    )
  endif ()

  list (APPEND KMSMNSCMODULE_INCLUDE_DIRS ${KMSMNSCMODULE_INTERFACE_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMODULE_INTERFACE_INCLUDE_DIR)
endif ()

if (NOT "mnscmoduleImplFactory.hpp" STREQUAL "")
  if (TARGET kmsmnscmoduleimpl)
    set (KMSMNSCMODULE_IMPLEMENTATION_INTERNAL_INCLUDE_DIR "${KMSMNSCMODULE_BINARY_DIR_PREFIX}/src/server/implementation/generated-cpp")
  else ()
    find_path(KMSMNSCMODULE_IMPLEMENTATION_INTERNAL_INCLUDE_DIR
      NAMES
        mnscmoduleImplFactory.hpp
      PATH_SUFFIXES
        ${KMSMNSCMODULE_BINARY_DIR_PREFIX}/src/server/implementation/generated-cpp
        kurento/modules/mnscmodule
    )
  endif ()

  list (APPEND KMSMNSCMODULE_INCLUDE_DIRS ${KMSMNSCMODULE_IMPLEMENTATION_INTERNAL_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMODULE_IMPLEMENTATION_INTERNAL_INCLUDE_DIR)
endif ()

if (NOT "mnscmoduleImpl.hpp" STREQUAL "")
  if (TARGET kmsmnscmoduleimpl)
    set (KMSMNSCMODULE_IMPLEMENTATION_GENERATED_INCLUDE_DIR "${KMSMNSCMODULE_SOURCE_DIR_PREFIX}/src/server/implementation/objects")
  else ()
    find_path(KMSMNSCMODULE_IMPLEMENTATION_GENERATED_INCLUDE_DIR
      NAMES
        mnscmoduleImpl.hpp
      PATH_SUFFIXES
        src/server/implementation/objects
        kurento/modules/mnscmodule
    )
  endif ()

  list (APPEND KMSMNSCMODULE_INCLUDE_DIRS ${KMSMNSCMODULE_IMPLEMENTATION_GENERATED_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMODULE_IMPLEMENTATION_GENERATED_INCLUDE_DIR)
endif()

if (NOT "" STREQUAL "")
  if (TARGET kmsmnscmoduleimpl)
    set (KMSMNSCMODULE_IMPLEMENTATION_EXTRA_INCLUDE_DIR "${KMSMNSCMODULE_SOURCE_DIR_PREFIX}/")
  else ()
    find_path(KMSMNSCMODULE_IMPLEMENTATION_EXTRA_INCLUDE_DIR
      NAMES
        
      PATH_SUFFIXES
        
        kurento/modules/mnscmodule
    )
  endif ()

  list (APPEND KMSMNSCMODULE_INCLUDE_DIRS ${KMSMNSCMODULE_IMPLEMENTATION_EXTRA_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMODULE_IMPLEMENTATION_EXTRA_INCLUDE_DIR)
endif ()

if (NOT "" STREQUAL "")
  if (TARGET kmsmnscmoduleinterface)
    set (KMSMNSCMODULE_INTERFACE_EXTRA_INCLUDE_DIR "${KMSMNSCMODULE_SOURCE_DIR_PREFIX}/")
  else ()
    find_path(KMSMNSCMODULE_INTERFACE_EXTRA_INCLUDE_DIR
      NAMES
        
      PATH_SUFFIXES
        
        kurento/modules/mnscmodule
    )
  endif()

  list (APPEND KMSMNSCMODULE_INCLUDE_DIRS ${KMSMNSCMODULE_INTERFACE_EXTRA_INCLUDE_DIR})
  list (APPEND REQUIRED_VARS KMSMNSCMODULE_INTERFACE_EXTRA_INCLUDE_DIR)
endif ()

if (TARGET kmsmnscmoduleimpl)
  set (KMSMNSCMODULE_LIBRARY kmsmnscmoduleimpl)
else ()
  find_library (KMSMNSCMODULE_LIBRARY
    NAMES
      kmsmnscmoduleimpl
    PATH_SUFFIXES
      ${KMSMNSCMODULE_BINARY_DIR_PREFIX}/src/server
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
  list (APPEND KMSMNSCMODULE_INCLUDE_DIRS ${${LIB_NAME}_INCLUDE_DIRS})

endforeach()

set(KMSMNSCMODULE_INCLUDE_DIRS
  ${KMSMNSCMODULE_INCLUDE_DIRS}
  CACHE INTERNAL "Include directories for KMSMNSCMODULE library" FORCE
)

set (KMSMNSCMODULE_LIBRARIES
  ${KMSMNSCMODULE_LIBRARY}
  ${KMSCORE_LIBRARIES}
  ${KMSELEMENTS_LIBRARIES}
  ${KMSFILTERS_LIBRARIES}
  ${REQUIRED_LIBRARIES}
  CACHE INTERNAL "Libraries for KMSMNSCMODULE" FORCE
)

include (FindPackageHandleStandardArgs)

find_package_handle_standard_args(KMSMNSCMODULE
  FOUND_VAR
    KMSMNSCMODULE_FOUND
  REQUIRED_VARS
    ${REQUIRED_VARS}
  VERSION_VAR
    KMSMNSCMODULE_VERSION
)

mark_as_advanced(
  KMSMNSCMODULE_FOUND
  KMSMNSCMODULE_VERSION
  KMSMNSCMODULE_INTERFACE_INCLUDE_DIR
  KMSMNSCMODULE_IMPLEMENTATION_INTERNAL_INCLUDE_DIR
  KMSMNSCMODULE_IMPLEMENTATION_GENERATED_INCLUDE_DIR
  KMSMNSCMODULE_IMPLEMENTATION_EXTRA_INCLUDE_DIR
  KMSMNSCMODULE_INTERFACE_EXTRA_INCLUDE_DIR
  KMSMNSCMODULE_INCLUDE_DIRS
  KMSMNSCMODULE_LIBRARY
  KMSMNSCMODULE_LIBRARIES
)
