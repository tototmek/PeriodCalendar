set(MODULE_NAME calendar)
set(LIBRARY_NAME "${MODULE_NAME}")

set(MODULE_SRC 
calendar.cpp
calendar_wrapper.cpp
io.cpp
)

add_library(${LIBRARY_NAME} STATIC ${MODULE_SRC})