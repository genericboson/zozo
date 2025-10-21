file(GLOB_RECURSE LOBBY_SOURCE *.cpp)
file(GLOB_RECURSE LOBBY_HEADER *.h)

find_package(Boost REQUIRED COMPONENTS charconv)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(LOBBY_SERVER 
	${LOBBY_SOURCE} ${LOBBY_HEADER}
)

target_link_directories(LOBBY_SERVER PRIVATE $ENV{BOOST_ROOT}/stage/lib)
target_link_libraries(LOBBY_SERVER PRIVATE 
	DBCACHE_CLIENT 
	ENGINE 
	Boost::charconv 
	Threads::Threads 
	OpenSSL::Crypto 
	OpenSSL::SSL)

set_property(TARGET LOBBY_SERVER PROPERTY CXX_STANDARD 20)
set_property(TARGET LOBBY_SERVER PROPERTY RUNTIME_OUTPUT_DIRECTORY ../bin)

target_precompile_headers(LOBBY_SERVER PUBLIC PCH.h)

target_compile_definitions(LOBBY_SERVER PRIVATE _UNICODE UNICODE)
target_include_directories(LOBBY_SERVER PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR}/.. 
	${CMAKE_CURRENT_SOURCE_DIR}/../MessageSchema/Common 
	${OPENSSL_INCLUDE_DIR} 
	$ENV{FLAT_BUFFER_INCLUDE} 
	$ENV{BOOST_ROOT})