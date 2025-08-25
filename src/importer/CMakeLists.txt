add_library(sprocket-importer MeshToBlueprint.cpp ObjReader.cpp)
target_include_directories(sprocket-importer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/lib)
