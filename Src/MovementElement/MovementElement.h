#ifndef __MOVEMENTELEMENT_H__
#define __MOVEMENTELEMENT_H__
#include <stdint.h>
#include "stepperMotorDriver.h"
#include "HalWrapper.h"

#define STEPPERMOTTOR_STEPANGLEX10 18

#ifndef TESTING
#define STPMOTDRIVER_L293D StpMotDriver_L293D
#else
#include "Mocks/StepperMotor_L293DMock.h"
#define STPMOTDRIVER_L293D StpMotDriver_L293DMock
#endif

using PositionMmX100 = int32_t;
using LinearToRotationalRatioX100 = uint32_t;
using ThreadPitchMm = uint8_t;

enum class AxisPlane_e
{
    X, Y, Z, XY, XZ, YZ
};

enum class MovementDirection_e
{
    UP, DOWN
};

template<typename T>
class MovementElement
{
private:
    AxisPlane_e m_AxisPlane;

public:
    constexpr MovementElement(const AxisPlane_e axisPlane)
    : m_AxisPlane(axisPlane) { }

    constexpr AxisPlane_e GetAxisOrPlane() const;

    // Interface methods, must be overwritten by derived classes
    PositionMmX100 GetPositionMmX100() const;
    void SetPositionMmX100(PositionMmX100 pos);
    PositionMmX100 GetActualPositionMmX100() const;
    LinearToRotationalRatioX100 GetLinToRotRatio() const;
    void MoveElementUp();
    void MoveElementDown();
    bool IsPositionReached();
    MovementDirection_e GetMovementDirection() const;
};

class MovementElement_CompileTime : public MovementElement<MovementElement_CompileTime>
{
public:
    constexpr MovementElement_CompileTime(const AxisPlane_e axisPlane)
    : MovementElement(axisPlane) { }
};

template<ThreadPitchMm pitch>
class MovementElement_AxisZ : MovementElement<MovementElement_AxisZ<pitch>>
{
private:
    constexpr void m_CheckCompileTime();
    PositionMmX100 m_PositionMmX100;
    PositionMmX100 m_ActualPositionMmX100;
    StpMotDriver<STPMOTDRIVER_L293D<STEPPERMOTTOR_STEPANGLEX10>>& m_L293d_Driver;
    LinearToRotationalRatioX100 m_LinToRotRatio;

public:
    MovementElement_AxisZ(STPMOTDRIVER_L293D<STEPPERMOTTOR_STEPANGLEX10>& l293d_Driver)
    : MovementElement<MovementElement_AxisZ<pitch>>(AxisPlane_e::Z), m_PositionMmX100(0),
      m_ActualPositionMmX100(0), m_L293d_Driver(l293d_Driver),
      m_LinToRotRatio(STEPPERMOTTOR_STEPANGLEX10 * pitch * 10 / 360)
    {
        m_CheckCompileTime();
    }

    PositionMmX100 GetPositionMmX100() const;
    void SetPositionMmX100(PositionMmX100 pos);
    PositionMmX100 GetActualPositionMmX100() const;
    LinearToRotationalRatioX100 GetLinToRotRatio() const;
    void MoveElementUp();
    void MoveElementDown();
    bool IsPositionReached();
    MovementDirection_e GetMovementDirection() const;
};

template<typename T>
constexpr AxisPlane_e MovementElement<T>::GetAxisOrPlane() const
{
    return m_AxisPlane;
}

template<typename T>
PositionMmX100 MovementElement<T>::GetPositionMmX100() const
{
    return static_cast<const T&>(*this).GetPositionMmX100();
}

template<typename T>
void MovementElement<T>::SetPositionMmX100(PositionMmX100 pos)
{
    static_cast<T&>(*this).SetPositionMmX100(pos);
}

template<typename T>
PositionMmX100 MovementElement<T>::GetActualPositionMmX100() const
{
    return static_cast<const T&>(*this).GetActualPositionMmX100();
}

template<typename T>
LinearToRotationalRatioX100 MovementElement<T>::GetLinToRotRatio() const
{
    return static_cast<const T&>(*this).GetLinToRotRatio();
}

template<typename T>
void MovementElement<T>::MoveElementUp()
{
    static_cast<T&>(*this).MoveElementUp();
}

template<typename T>
void MovementElement<T>::MoveElementDown()
{
    static_cast<T&>(*this).MoveElementDown();
}

template<typename T>
bool MovementElement<T>::IsPositionReached()
{
    return static_cast<T&>(*this).IsPositionReached();
}

template<typename T>
MovementDirection_e MovementElement<T>::GetMovementDirection() const
{
    return static_cast<const T&>(*this).GetMovementDirection();
}

template<ThreadPitchMm pitch>
constexpr void MovementElement_AxisZ<pitch>::m_CheckCompileTime()
{
    constexpr MovementElement_CompileTime compileTimeObj(AxisPlane_e::Z);
    static_assert(compileTimeObj.GetAxisOrPlane() == AxisPlane_e::Z,
                     "[ERROR]: This Element should work in Z axis\n");
    static_assert(pitch >= 1 && pitch <= 10,
                     "[ERROR]: The screw should with following pitch does not exist\n");
}

#endif
