add_library(proof OBJECT "")

target_sources(proof
PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/PG.h"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGBuild.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGCheck.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGHelp.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGHeuristics.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGInterAux.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGInterCheck.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGInterpolator.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGMain.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGPrint.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGRules.C"
PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PGTransformationAlgorithms.C"
)

#install(FILES PG.h
#DESTINATION ${INSTALL_HEADERS_DIR})

