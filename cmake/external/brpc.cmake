include (ExternalProject)

SET(BRPC_SOURCES_DIR ${THIRD_PARTY_PATH}/brpc)
SET(BRPC_INSTALL_DIR ${THIRD_PARTY_PATH}/install/brpc)
SET(BRPC_INCLUDE_DIR "${BRPC_INSTALL_DIR}/include/" CACHE PATH "brpc include directory." FORCE)
set(BRPC_LIBRARY "${BRPC_INSTALL_DIR}/lib/libbrpc.a" CACHE FILEPATH "BRPC_LIBRARIES" FORCE)
include_directories(${BRPC_INCLUDE_DIR})

SET(BUILD_CMD sh config_brpc.sh --headers=/usr/include --libs=/usr/lib && make -j)
set(INSTALL_CMD cp -rp ${BRPC_SOURCES_DIR}/src/brpc/output/ ${BRPC_INSTALL_DIR})

ExternalProject_Add(
    brpc
    DEPENDS protobuf
    GIT_REPOSITORY "https://github.com/brpc/brpc.git"
    PREFIX          ${BRPC_SOURCES_DIR}
    UPDATE_COMMAND  ""
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND  ${BUILD_CMD}
    INSTALL_COMMAND ${INSTALL_CMD}
)

LIST(APPEND external_project_dependencies brpc)
ADD_LIBRARY(brpc_target STATIC IMPORTED GLOBAL)
SET_PROPERTY(TARGET brpc_target PROPERTY IMPORTED_LOCATION ${BRPC_LIBRARY})
