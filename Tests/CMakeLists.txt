cmake_minimum_required(VERSION 3.22)

add_subdirectory(StepperMotorDriver)
add_subdirectory(MovementElement)

add_test(NAME Test_StepperMotorDriver COMMAND Test_StepperMotorDriver)
add_test(NAME Test_MovementElement COMMAND Test_MovementElement)
