list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_LIST_DIR}/cmake)
get_filename_component(EUDAQ_USERNAME ${CMAKE_CURRENT_LIST_DIR} NAME)

set(EUDAQ_MODULE module_${EUDAQ_USERNAME})
set(USER_HARDWARE_LIBRARY ${EUDAQ_USERNAME}_static)

option(USER_EUDET_BUILD "build eudet" ON)

if(NOT USER_EUDET_BUILD)
  message(STATUS "user/eudet is NOT to be built (USER_EUDET_BUILD=OFF)")
  unset(USER_EUDET_BUILD_NI CACHE)
  unset(USER_EUDET_BUILD_TLU CACHE)
  unset(USER_EUDET_BUILD_FMCTLU CACHE)
  return()
endif()

message(STATUS "user/eudet is to be built (USER_EUDET_BUILD=ON)")

include_directories(${EUDAQ_INCLUDE_DIRS})

# for the NI producer
option(USER_EUDET_BUILD_NI "build user/eudet ni" ON)
set(USER_BUILD_NI ${USER_EUDET_BUILD_NI})

# for the AIDA TLU
find_package(CACTUS)
cmake_dependent_option(USER_EUDET_BUILD_FMCTLU "build user/eudet FMC TLU" ON
  "CACTUS_FOUND" OFF)
set(USER_BUILD_FMCTLU ${USER_EUDET_BUILD_FMCTLU})

# for the EUDET TLU
find_package(ZestSC1)
find_package(LIBUSB)
find_package(TLUFirmware)
cmake_dependent_option(USER_EUDET_BUILD_TLU "build user/eudet tlu" ON
  "LIBUSB_FOUND;ZESTSC1_FOUND;TLUFIRMWARE_FOUND" OFF)
set(USER_BUILD_TLU ${USER_EUDET_BUILD_TLU})

include_directories(hardware/include)
add_subdirectory(hardware)
add_subdirectory(module)
