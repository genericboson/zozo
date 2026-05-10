cmake_minimum_required (VERSION 3.17.0)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5 CACHE STRING "" FORCE)

# !!! Very Very important !!!
# enable_testing must be in main CMakeLists.txt for being searched by Test Explorer
enable_testing()

project (ZozoTown)

add_subdirectory (ThirdParty/OpenXLSX)

#add_subdirectory ("Bot")
add_subdirectory ("Engine")
add_subdirectory ("GameServer")
add_subdirectory ("LobbyServer")
#add_subdirectory ("Test")
add_subdirectory ("TestConsole")

set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT Sample)