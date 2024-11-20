configure_file(__init__.py __init__.py COPYONLY)

pybind11_add_module(_core MODULE alea.cpp)
target_link_libraries(_core PUBLIC alps::alps-alea MPI::MPI_CXX PRIVATE pybind11::headers)
install(TARGETS _core DESTINATION pyalea)
