# Minimum required CMake version (updated for compatibility)
cmake_minimum_required(VERSION 3.10...3.16 FATAL_ERROR)

# Project name
project(Simulation)

# Find the required Geant4 package, including UI and visualization drivers
set(Geant4_DIR "/home/pawan/Software/Geant4/geant4-v11.1.0-install/share/Geant4-11.1.0")

find_package(Geant4 REQUIRED ui_all vis_all)

# Include the Geant4 configuration file for CMake
include(${Geant4_USE_FILE})

# Specify source and header files
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

# Add the executable, including source and header files
add_executable(sim sim.cc ${sources} ${headers})

# Link the executable to the Geant4 libraries
target_link_libraries(sim ${Geant4_LIBRARIES})

# Add a custom target called 'Simulation', which depends on the 'sim' executable
add_custom_target(Simulation DEPENDS sim)

