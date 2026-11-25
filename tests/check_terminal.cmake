execute_process(COMMAND "${APP}"
    INPUT_FILE "${INPUT}"
    OUTPUT_VARIABLE output
    RESULT_VARIABLE result
    ENCODING UTF-8
    TIMEOUT 5
)
if(NOT result STREQUAL "0")
    message(FATAL_ERROR "Terminal exited with ${result}")
endif()

foreach(expected IN ITEMS "שימוש: הוסף <מספר שלם תקין>" "המספרים: [-2, 10, 30]"
                          "סכום: 38 | ממוצע:" "אין מספרים לחישוב." "להתראות!")
    string(FIND "${output}" "${expected}" found)
    if(found EQUAL -1)
        message(FATAL_ERROR "Missing terminal output '${expected}'.\n${output}")
    endif()
endforeach()
