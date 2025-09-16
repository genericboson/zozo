file(GLOB_RECURSE CORE_SOURCE *.cpp)
file(GLOB_RECURSE CORE_HEADER *.h)

#set_source_files_properties(${CORE_SRC} PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

add_library(Engine STATIC 
	${CORE_SOURCE} ${CORE_HEADER}
)
set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
set_property(TARGET Engine PROPERTY RUNTIME_OUTPUT_DIRECTORY ../bin)

target_compile_definitions(Engine PRIVATE _UNICODE UNICODE)
target_include_directories(Engine PRIVATE $ENV{FLAT_BUFFER_INCLUDE} $ENV{BOOST_ROOT})