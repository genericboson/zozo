cmake_minimum_required (VERSION 3.17.0)

# !!! Very Very important !!!
# enable_testing must be in main CMakeLists.txt for being searched by Test Explorer
enable_testing()

project (ZozoTown)

add_subdirectory ("engine")
add_subdirectory ("game")
add_subdirectory ("test")

#add_subdirectory ("flatbuffers")

set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT Sample)