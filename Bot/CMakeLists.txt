file(GLOB_RECURSE BOT_SOURCE *.cpp)
file(GLOB_RECURSE BOT_HEADER *.h)

#set_source_files_properties(${BOT_SOURCE} PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")

add_executable(BOT 
	${BOT_SOURCE} ${BOT_HEADER}
)
set_property(TARGET BOT PROPERTY CXX_STANDARD 20)
set_property(TARGET BOT PROPERTY RUNTIME_OUTPUT_DIRECTORY ../bin)

target_compile_definitions(BOT PRIVATE _UNICODE UNICODE)
target_include_directories(BOT PRIVATE $ENV{FLAT_BUFFER_INCLUDE} $ENV{BOOST_ROOT})