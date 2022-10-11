set(SOURCES action.hpp middleware.hpp store.hpp dispatcher.hpp)

add_library(flucxx STATIC ${SOURCES})
target_link_libraries(flucxx PUBLIC quickfuture Qt${QT_VERSION_MAJOR}::Core)
