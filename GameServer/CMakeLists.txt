file(GLOB_RECURSE GAME_SOURCE *.cpp)
file(GLOB_RECURSE GAME_HEADER *.h)
file(GLOB_RECURSE GAME_MEM_SOURCE ../MessageSchema/External/GameServerMem/*.cpp)
file(GLOB_RECURSE GAME_MEM_HEADER ../MessageSchema/External/GameServerMem/*.h)

# DataConverter가 엑셀에서 생성한 정적 데이터 클래스.
# 전역 초기화로 자신을 등록하므로 반드시 실행 파일에 직접 링크되어야 한다
# (정적 라이브러리에 넣으면 참조가 없어 링커가 통째로 버린다).
file(GLOB_RECURSE STATIC_DATA_SOURCE ../StaticData/json/*.cpp)
file(GLOB_RECURSE STATIC_DATA_HEADER ../StaticData/json/*.h)

find_package(Boost REQUIRED COMPONENTS charconv)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(GAME_SERVER
	${GAME_SOURCE} ${GAME_HEADER} ${GAME_CACHE_SOURCE} ${GAME_CACHE_HEADER}
	${STATIC_DATA_SOURCE} ${STATIC_DATA_HEADER}
)

target_link_directories(GAME_SERVER PRIVATE $ENV{BOOST_ROOT}/stage/lib)
target_link_libraries(GAME_SERVER PRIVATE 
	ENGINE 
	Boost::charconv 
	Threads::Threads 
	OpenSSL::Crypto 
	OpenSSL::SSL )

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