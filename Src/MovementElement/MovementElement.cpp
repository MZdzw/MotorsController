#include <cmath>
#include "MovementElement.h"

template<ThreadPitchMm pitch>
PositionMmX100 MovementElement_AxisZ<pitch>::GetPositionMmX100() const
{
    return m_PositionMmX100;
}

template<ThreadPitchMm pitch>
void MovementElement_AxisZ<pitch>::SetPositionMmX100(PositionMmX100 pos)
{
    m_PositionMmX100 = pos;
}

template<ThreadPitchMm pitch>
PositionMmX100 MovementElement_AxisZ<pitch>::GetActualPositionMmX100() const
{
    return m_ActualPositionMmX100;
}

template<ThreadPitchMm pitch>
LinearToRotationalRatioX100 MovementElement_AxisZ<pitch>::GetLinToRotRatio() const
{
    return m_LinToRotRatio;
}

template<ThreadPitchMm pitch>
void MovementElement_AxisZ<pitch>::MoveElementUp()
{
    m_L293d_Driver.RotateMotorOneStep();
    m_ActualPositionMmX100 += m_LinToRotRatio;
}

template<ThreadPitchMm pitch>
void MovementElement_AxisZ<pitch>::MoveElementDown()
{
    m_L293d_Driver.RotateMotorOneStepReverse();
    m_ActualPositionMmX100 -= m_LinToRotRatio;
}

template<ThreadPitchMm pitch>
bool MovementElement_AxisZ<pitch>::IsPositionReached()
{
    // @TODO - check that division by 2 is optimized by compiler
    if (std::abs(m_ActualPositionMmX100 - m_PositionMmX100) < (m_LinToRotRatio / 2))
        return true;
    return false;
}

template<ThreadPitchMm pitch>
MovementDirection_e MovementElement_AxisZ<pitch>::GetMovementDirection() const
{
    return (m_ActualPositionMmX100 > m_PositionMmX100) ?
            MovementDirection_e::DOWN : MovementDirection_e::UP;
}

// Explicit instantiation of template class for specific values of pitch thread
// Getting linking error without instantation, because compiler can ommit
// generating code in object file (.o) if the method body does not use
// template parameter. 
template class MovementElement_AxisZ<8>;
