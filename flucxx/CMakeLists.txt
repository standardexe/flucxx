set(SOURCES action.hpp middleware.hpp store.hpp dispatcher.hpp promise.hpp)

add_library(flucxx STATIC ${SOURCES})
target_link_libraries(flucxx PUBLIC Qt5::Core Qt5::Quick)
target_include_directories(flucxx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
