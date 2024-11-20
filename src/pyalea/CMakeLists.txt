python_add_library(_core MODULE alea.cpp WITH_SOABI)
target_link_libraries(_core PUBLIC alps::alps-alea MPI::MPI_CXX PRIVATE pybind11::headers)
install(TARGETS _core DESTINATION pyalea)

# pybind11_add_module(alea alea.cpp)
# target_link_libraries(alea PUBLIC alps::alps-alea MPI::MPI_CXX)
