# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\PIC_SIM_QT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PIC_SIM_QT_autogen.dir\\ParseCache.txt"
  "PIC_SIM_QT_autogen"
  )
endif()