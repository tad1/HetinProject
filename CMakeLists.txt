# CMakeList.txt: projekt CMake dla elementu HetinProject, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

project ("HetinProject")

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (HetinProject "HetinProject.cpp" "HetinProject.h")

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
