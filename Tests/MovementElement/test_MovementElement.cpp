#include <gtest/gtest.h>
#include "MovementElement.h"

// MovementElement_AxisZ_Suite

// TEST1:  Creation of MovementElement_AxisZ object
TEST(MovementElement_AxisZ_Suite, CheckObjectCreation)
{
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    ASSERT_NE(&movElemAxisZ, nullptr);
}

// TEST2:  Check that after object initialization the position
//         is equal to 0
TEST(MovementElement_AxisZ_Suite, CheckPositionEqualToZero)
{
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    ASSERT_EQ(movElemAxisZ.GetPositionMmX100(), 0);
}

// TEST3:  Check that object creation with wrong thread pitch does
//         not succeed
TEST(MovementElement_AxisZ_Suite, CheckWrongThreadPitchCompilation)
{
    // Change to 11 to get compilation error
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    ASSERT_NE(&movElemAxisZ, nullptr);
}

// TEST4:  Check that LinToRotRation is set with proper value
//         
TEST(MovementElement_AxisZ_Suite, CheckLinearToRotationalRatioIsSetProperly)
{
    const ThreadPitchMm threadPitch = 8;
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<threadPitch> movElemAxisZ(l293d_DriverMock);
    
    // one step of stepper motor is STEPPERMOTTOR_STEPANGLEX10 (18) - 1.8 deg
    // so one revolution needs: 360 deg / 1.8 deg = 200 steps
    // For thread with 8 mm pitch, the one revolution means that object will move 8 mm.
    // So: 8 mm / 200 * 100 (because x100 times) = 4 (0.04 mm per one motor step)
    LinearToRotationalRatioX100 expectedRatio = 4;

    EXPECT_EQ(movElemAxisZ.GetLinToRotRatio(), expectedRatio);
}

// TEST5: Check setting position works
//
TEST(MovementElement_AxisZ_Suite, CheckSettingPosition)
{
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    movElemAxisZ.SetPositionMmX100(800);

    EXPECT_EQ(movElemAxisZ.GetPositionMmX100(), 800);
}

// TEST6: Check that move up change actual position
//
TEST(MovementElement_AxisZ_Suite, CheckMoveUp)
{
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    EXPECT_CALL(l293d_DriverMock, RotateMotorOneStep())
    .Times(2);
    movElemAxisZ.MoveElementUp();


    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), 4);

    movElemAxisZ.MoveElementUp();
    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), 8);
}

// TEST7: Check that move down change actual position
//
TEST(MovementElement_AxisZ_Suite, CheckMoveDown)
{
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    EXPECT_CALL(l293d_DriverMock, RotateMotorOneStepReverse())
    .Times(2);
    movElemAxisZ.MoveElementDown();

    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), -4);

    movElemAxisZ.MoveElementDown();
    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), -8);
}

// TEST8: After restart (initialization) the actual position is equal 0.
//        Set desired position and check that actual position is not reached.
//        Then set desired position back to 0 and the actual position
//        should be reached
TEST(MovementElement_AxisZ_Suite, CheckReachedPosition)
{
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    movElemAxisZ.SetPositionMmX100(5000);       // Set position to 50 mm

    EXPECT_FALSE(movElemAxisZ.IsPositionReached());

    movElemAxisZ.SetPositionMmX100(0);       // Set position to 0 mm
    EXPECT_TRUE(movElemAxisZ.IsPositionReached());
}

// TEST9: The element should know if it must move up or down.
//        Check movement direction
TEST(MovementElement_AxisZ_Suite, CheckMovementDirection)
{
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    movElemAxisZ.SetPositionMmX100(5000);       // Set position to 50 mm

    EXPECT_EQ(movElemAxisZ.GetMovementDirection(), MovementDirection_e::UP);

    movElemAxisZ.SetPositionMmX100(-3000);       // Set position to -30 mm
    EXPECT_EQ(movElemAxisZ.GetMovementDirection(), MovementDirection_e::DOWN);
}

// TEST10: The Element should aim for the closest possible position
//         Example: if one step of stepper motor cause movement of 0.04 mm
//         and the desired value is 1.03, the element should take position
//         if 1.04 mm because it is closer to 1.03 mm than 1 mm.
//         Include that in IsPositionReached
//
TEST(MovementElement_AxisZ_Suite, CheckMoveElement)
{
    StpMotDriver_L293DMock<18> l293d_DriverMock;
    MovementElement_AxisZ<8> movElemAxisZ(l293d_DriverMock);
    EXPECT_CALL(l293d_DriverMock, RotateMotorOneStep())
    .Times(4);

    movElemAxisZ.SetPositionMmX100(15);       // Set position to 0.15 mm
 
    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), 0);
    EXPECT_FALSE(movElemAxisZ.IsPositionReached());
    movElemAxisZ.MoveElementUp();
    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), 4);
    EXPECT_FALSE(movElemAxisZ.IsPositionReached());
    movElemAxisZ.MoveElementUp();
    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), 8);
    EXPECT_FALSE(movElemAxisZ.IsPositionReached());
    movElemAxisZ.MoveElementUp();
    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), 12);
    EXPECT_FALSE(movElemAxisZ.IsPositionReached());
    movElemAxisZ.MoveElementUp();
    EXPECT_EQ(movElemAxisZ.GetActualPositionMmX100(), 16);
    EXPECT_TRUE(movElemAxisZ.IsPositionReached());
}

