
include_directories(../GameLogic/)

add_executable(ControllerAngleTestExec ControllerAngleTest.cpp)
target_link_libraries(ControllerAngleTestExec GameLogic)
