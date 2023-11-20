set(PROJECT_SOURCES
        main.cpp

        actions/GalleryActions.hpp
        actions/NavigationActions.hpp
        actions/QmlActions.hpp

        middlewares/LoggingMiddleware.hpp

        models/NavigationModel.hpp
        models/ArtworkModel.hpp

        stores/MainStore.hpp
        stores/NavigationStore.hpp
)

qt5_add_resources(PROJECT_SOURCES qml/qml.qrc)

set(PROJECT artworks_flucxx)

add_executable(${PROJECT} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT}
  PRIVATE Qt5::Core Qt5::Quick flucxx)

install(TARGETS ${PROJECT}
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

