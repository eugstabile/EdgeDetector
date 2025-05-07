set(COPY_DIR TRUE)

if(BUILD_TESTS)
    set(COPY_DIR FALSE)
    add_custom_command(TARGET ${TEST_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Resources"
            "$<TARGET_FILE_DIR:${TEST_NAME}>/Resources"
    )
elseif(BUILD_BENCHMARKS AND COPY_DIR)
    add_custom_command(TARGET ${BENCHMARK_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Resources"
            "$<TARGET_FILE_DIR:${BENCHMARK_NAME}>/Resources"
    )
endif()