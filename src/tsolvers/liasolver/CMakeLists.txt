target_sources(tsolvers
PUBLIC "${CMAKE_CURRENT_LIST_DIR}/LIASolver.h"
PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Matrix.h"

PRIVATE "${CMAKE_CURRENT_LIST_DIR}/LIASolver.C"
PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Matrix.cpp"

)

