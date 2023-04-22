set(PROJECT_SOURCES
        main.cpp

        actions/CMakeLists.txt
        actions/DialogActions.hpp
        actions/NavigationActions.hpp
        actions/QmlActions.hpp
        actions/TodoActions.hpp

        middlewares/CMakeLists.txt
        middlewares/DialogMiddleware.hpp
        middlewares/LoggingMiddleware.hpp
        middlewares/SleepMiddleware.hpp

        models/CMakeLists.txt
        models/NavigationModel.hpp
        models/TodoItem.hpp
        models/TodoListModel.hpp

        stores/CMakeLists.txt
        stores/MainStore.hpp
        stores/NavigationStore.hpp
)

qt5_add_resources(PROJECT_SOURCES qml/qml.qrc)

add_executable(todo_flucxx ${PROJECT_SOURCES})

target_link_libraries(todo_flucxx
  PRIVATE Qt5::Core Qt5::Quick flucxx)

install(TARGETS todo_flucxx
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

