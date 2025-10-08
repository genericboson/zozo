file(GLOB_RECURSE CORE_SOURCE *.cpp)
file(GLOB_RECURSE CORE_HEADER *.h)

add_library(ENGINE STATIC 
	${CORE_SOURCE} ${CORE_HEADER}
)
set_property(TARGET ENGINE PROPERTY CXX_STANDARD 20)
set_property(TARGET ENGINE PROPERTY RUNTIME_OUTPUT_DIRECTORY ../bin)

target_precompile_headers(ENGINE PUBLIC PCH.h)

target_link_directories(ENGINE PRIVATE $ENV{BOOST_ROOT}/stage/lib)
target_link_libraries(ENGINE PRIVATE libboost_thread-vc143-mt-gd-x64-1_89)

target_compile_definitions(ENGINE PRIVATE _UNICODE UNICODE)
target_include_directories(ENGINE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR} $ENV{FLAT_BUFFER_INCLUDE} $ENV{BOOST_ROOT})