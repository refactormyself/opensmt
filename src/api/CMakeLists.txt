set(OBJECTS_TO_ADD
$<TARGET_OBJECTS:smtsolvers>
$<TARGET_OBJECTS:parsers>
$<TARGET_OBJECTS:logics>
$<TARGET_OBJECTS:options>
$<TARGET_OBJECTS:symbols>
$<TARGET_OBJECTS:pterms>
$<TARGET_OBJECTS:sorts>
$<TARGET_OBJECTS:tsolvers>
$<TARGET_OBJECTS:cnfizers>
$<TARGET_OBJECTS:common>
$<TARGET_OBJECTS:simplifiers>
)

if(PRODUCE_PROOF)
set(OBJECTS_TO_ADD $<TARGET_OBJECTS:proof> ${OBJECTS_TO_ADD})
endif()

add_library(api OBJECT "")



set(PRIVATE_SOURCES_TO_ADD
	"${CMAKE_CURRENT_SOURCE_DIR}/Interpret.C"
	"${CMAKE_CURRENT_SOURCE_DIR}/MainSolver.C"
)

set(PUBLIC_SOURCES_TO_ADD
	"${CMAKE_CURRENT_SOURCE_DIR}/Interpret.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/MainSolver.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/DimacsParser.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/smt2tokens.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Opensmt.C"
)

target_sources(api
PRIVATE ${PRIVATE_SOURCES_TO_ADD}
PUBLIC ${PUBLIC_SOURCES_TO_ADD}
)

set(OBJECTS_TO_ADD $<TARGET_OBJECTS:api> ${OBJECTS_TO_ADD})

add_library(api_shared SHARED ${OBJECTS_TO_ADD})
add_library(api_static STATIC ${OBJECTS_TO_ADD})



target_link_libraries(api_shared ${Readline_LIBRARY} ${GMP_LIBRARIES} ${GMPXX_LIBRARIES} Threads::Threads)

target_link_libraries(api_static ${Readline_LIBRARY} ${GMP_LIBRARIES} ${GMPXX_LIBRARIES} Threads::Threads)

set_target_properties(api_shared PROPERTIES OUTPUT_NAME opensmt2)

install(TARGETS api_shared DESTINATION lib)

install(FILES Opensmt.h smt2tokens.h MainSolver.h Interpret.h
DESTINATION ${INSTALL_HEADERS_DIR})
