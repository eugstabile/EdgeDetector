find_package(Doxygen)

set(DOCS_DIR ${PROJECT_SOURCE_DIR}/docs)

if(DOXYGEN_FOUND)
    set(doxyfile ${DOCS_DIR}/Doxyfile)
    add_custom_target(doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    WORKING_DIRECTORY ${DOCS_DIR}
    COMMENT "Generating Doxygen documentation"
    VERBATIM
)
endif()