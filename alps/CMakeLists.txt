pybind11_add_module(alea alea.cpp)
target_link_libraries(alea PUBLIC alps::alps-alea)