set(SEARCH_SEM_NEIGHBORHOOD_AGENT "${CMAKE_CURRENT_LIST_DIR}/searchSemNeighborhoodAgent")

file(GLOB SEARCH_SEM_NEIGHBORHOOD_AGENT_SRC ${SEARCH_SEM_NEIGHBORHOOD_AGENT}/*.cpp)

file(GLOB SEARCH_SEM_NEIGHBORHOOD_AGENT_HEADERS ${SEARCH_SEM_NEIGHBORHOOD_AGENT}/*.hpp)

set(SOURCES
	"commonModule.cpp"
	${SEARCH_SEM_NEIGHBORHOOD_AGENT_SRC})

set(HEADERS
	"commonModule.hpp"
	${SEARCH_SEM_NEIGHBORHOOD_AGENT_HEADERS})

include_directories(
        ${CMAKE_CURRENT_LIST_DIR}
        ${SC_MEMORY_SRC}
        ${SC_KPM_SRC}
	${SC_TOOLS_SRC}
	${SEARCH_SEM_NEIGHBORHOOD_AGENT})

add_library(commonModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(commonModule sc-memory sc-agents-common)

sc_codegen_ex(commonModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)
