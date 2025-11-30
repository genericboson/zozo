file(GLOB_RECURSE GAME_SOURCE *.cpp)
file(GLOB_RECURSE GAME_HEADER *.h)

find_package(Boost REQUIRED COMPONENTS charconv)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(GAME_SERVER 
	${GAME_SOURCE} ${GAME_HEADER}
)

target_link_directories(GAME_SERVER PRIVATE $ENV{BOOST_ROOT}/stage/lib)
target_link_libraries(GAME_SERVER PRIVATE 
	ENGINE 
	Boost::charconv 
	Threads::Threads 
	OpenSSL::Crypto 
	OpenSSL::SSL)

set_property(TARGET GAME_SERVER PROPERTY CXX_STANDARD 20)
set_property(TARGET GAME_SERVER PROPERTY RUNTIME_OUTPUT_DIRECTORY ../bin)

target_precompile_headers(GAME_SERVER PUBLIC PCH.h)

target_compile_definitions(GAME_SERVER PRIVATE _UNICODE UNICODE $<$<CONFIG:Debug>:DEBUG>)
target_include_directories(GAME_SERVER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR}/.. 
	${CMAKE_CURRENT_SOURCE_DIR}/../MessageSchema/Common 
	${OPENSSL_INCLUDE_DIR} 
	$ENV{FLAT_BUFFER_INCLUDE} 
	$ENV{BOOST_ROOT})