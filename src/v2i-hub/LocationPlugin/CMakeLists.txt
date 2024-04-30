project(LocationPlugin VERSION 3.3.0 LANGUAGES CXX)

SET(TMX_PLUGIN_NAME Location)

BuildTmxPlugin()

find_path(GPS_INCLUDE_DIR NAMES gps.h HINTS /usr /usr/local PATH_SUFFIXES include)

# Check if GPS_INCLUDE_DIR is found
if(NOT GPS_INCLUDE_DIR)
    message(FATAL_ERROR "GPS header file (gps.h) not found.")
endif()

find_library(GPS_LIBRARY NAMES gps)

# Check if GPS_LIBRARY is found
if(NOT GPS_LIBRARY)
    message(FATAL_ERROR "GPS library (libgps) not found.")
endif()

# Check the version of the found GPSD is at least to API 9
file(STRINGS "${GPS_INCLUDE_DIR}/gps.h" GPSD_API_MAJOR_VERSION REGEX GPSD_API_MAJOR_VERSION)
string(REGEX REPLACE "^#define GPSD_API_MAJOR_VERSION\t\t*([0-9]*).*" "\\1" GPSD_API_MAJOR_VERSION "${GPSD_API_MAJOR_VERSION}")

set(GPSD_MIN_API_MAJOR_VERSION 9)

if(${GPSD_API_MAJOR_VERSION} LESS ${GPSD_MIN_API_MAJOR_VERSION})
    message(STATUS "GPS API Version ${GPSD_API_MAJOR_VERSION} does not meet the minimum ${GPSD_MIN_API_MAJOR_VERSION}")
    message(STATUS "Resorting to static GPSD library")

    unset(GPS_INCLUDE_DIR CACHE)
    unset(GPS_LIBRARY CACHE)

    find_path(GPS_INCLUDE_DIR NAMES gps.h
               PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../../tmx-build/gpsd/usr/local/include
               NO_DEFAULT_PATH)          
    find_library(GPS_LIBRARY NAMES gps
                 PATHS ${GPS_INCLUDE_DIR}/../lib
                 NO_DEFAULT_PATH)
endif()

message(STATUS "GPS_INCLUDE_DIR: ${GPS_INCLUDE_DIR}")    
message(STATUS "GPS_LIBRARY: ${GPS_LIBRARY}")

target_include_directories(${PROJECT_NAME} PUBLIC ${GPS_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} tmxutils rt ${GPS_LIBRARY})

