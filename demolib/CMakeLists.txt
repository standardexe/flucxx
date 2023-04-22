cmake_minimum_required(VERSION 3.14)

set(PROJECT_SOURCES )

qt5_add_resources(PROJECT_SOURCES 3rdparty/quickpromise/qml/quickpromise.qrc)

add_library(demolib)

target_include_directories(demolib PRIVATE ../3rdparty/asyncfuture)
target_include_directories(demolib PRIVATE ../)
target_include_directories(demolib INTERFACE ./)

add_subdirectory(models/)
add_subdirectory(stores/)
add_subdirectory(actions/)
add_subdirectory(middlewares/)

target_link_libraries(demolib
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
  quickfuture
  flucxx)

install(TARGETS demolib
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

