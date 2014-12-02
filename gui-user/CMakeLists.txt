
# Automatically link Qt executables to qtmain target on Windows
cmake_policy(SET CMP0020 OLD)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Widgets)
if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif(Qt5_POSITION_INDEPENDENT_CODE)


# allow the user to choose if GUI is being build
# by default, if Qt was found it is build
if (Qt5Core_FOUND)
    option(BUILD_GUI_COMPONENTS "Activate or deactivate building of GUI components"
             ON)
else (Qt5Core_FOUND)
    option(BUILD_GUI_COMPONENTS "Activate or deactivate building of GUI components"
             OFF)
endif (Qt5Core_FOUND)


if (NOT INCLUDE_PILE_SOURCES_DIRECTLY)
    set (USERMSG_LIBRARY usermsg)
endif()

include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}/build/include"
)
set ( CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_ui(LIB_UIS_SRC
    "messagebx.ui"
    "mainwindow.ui")

add_executable(gui-user
    ${USERMSG_SOURCES}
    ${USERMSG_HEADERS}
    ${LIB_UIS_SRC}
    messagebx.cpp
    mainwindow.cpp
    main.cc)

qt5_use_modules(gui-user Core Widgets)

if (USERMSG_LIBRARY)
	target_link_libraries(gui-user
		${USERMSG_LIBRARY})
endif()
