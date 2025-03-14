# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_livox_mapping_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED livox_mapping_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(livox_mapping_FOUND FALSE)
  elseif(NOT livox_mapping_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(livox_mapping_FOUND FALSE)
  endif()
  return()
endif()
set(_livox_mapping_CONFIG_INCLUDED TRUE)

# output package information
if(NOT livox_mapping_FIND_QUIETLY)
  message(STATUS "Found livox_mapping: 0.0.1 (${livox_mapping_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'livox_mapping' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${livox_mapping_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(livox_mapping_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${livox_mapping_DIR}/${_extra}")
endforeach()
