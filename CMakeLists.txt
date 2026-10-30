cmake_minimum_required(VERSION 3.16)

project(BundleAdjustmentXA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)

# Bibliothèque pour le module data
add_library(xa_data
    src/data/Loader.cpp
    src/data/Metadata.cpp
    src/data/Annotations.cpp
)

target_include_directories(xa_data PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(xa_data PUBLIC
    ${OpenCV_LIBS}
    nlohmann_json::nlohmann_json
)

# Exécutable principal
add_executable(angiography
    main.cpp
    src/geometry/Camera.cpp
    src/geometry/Projection.cpp
    src/geometry/Transforms.cpp
    src/simulation/SyntheticPoints.cpp
)

# L'exécutable utilise la bibliothèque xa_data
target_link_libraries(angiography PRIVATE
    xa_data
    Eigen3::Eigen
)