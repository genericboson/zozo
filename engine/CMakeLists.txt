file(GLOB_RECURSE CORE_SOURCE *.cpp)
file(GLOB_RECURSE CORE_HEADER *.h)

find_package(Boost REQUIRED COMPONENTS charconv)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(ENGINE STATIC 
	${CORE_SOURCE} ${CORE_HEADER}
)
set_property(TARGET ENGINE PROPERTY CXX_STANDARD 20)
set_property(TARGET ENGINE PROPERTY RUNTIME_OUTPUT_DIRECTORY ../bin)

target_precompile_headers(ENGINE PUBLIC PCH.h)

target_link_directories(ENGINE PRIVATE $ENV{BOOST_ROOT}/stage/lib)
target_link_libraries(ENGINE PRIVATE 
	Boost::charconv 
	Threads::Threads 
	OpenSSL::Crypto 
	OpenSSL::SSL)

target_compile_definitions(ENGINE PRIVATE _UNICODE UNICODE)
target_include_directories(ENGINE PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/.. 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${OPENSSL_INCLUDE_DIR} 
	$ENV{FLAT_BUFFER_INCLUDE} 
	$ENV{BOOST_ROOT})