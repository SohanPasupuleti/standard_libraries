function(copy_target_dll executable imported_target)
    get_target_property(DLL_PATH ${imported_target} IMPORTED_LOCATION_RELEASE)

    if(NOT DLL_PATH)
        get_target_property(DLL_PATH ${imported_target} IMPORTED_LOCATION)
    endif()

    if(DLL_PATH AND EXISTS "${DLL_PATH}")
        add_custom_command(TARGET ${executable} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${DLL_PATH}"
                "$<TARGET_FILE_DIR:${executable}>"
            COMMENT "Copying ${imported_target} DLL"
        )
    endif()
endfunction()