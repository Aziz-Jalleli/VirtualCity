# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VirtualCity_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VirtualCity_autogen.dir\\ParseCache.txt"
  "VirtualCity_autogen"
  )
endif()
