target_sources(tsolvers
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/LASolver.h"
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Simplex.h"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LAVar.h"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LAVarMapper.cpp"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Tableau.cpp"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LABounds.cpp"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Delta.cpp"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LAVar.cpp"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Polynomial.h"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Polynomial.cpp"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Tableau.h"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LAVarMapper.h"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LARefs.h"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LABounds.h"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Delta.h"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LASolver.cpp"
    PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Simplex.cpp"
    )



