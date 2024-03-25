#ifndef __STEPPERMOTORDRIVER_H__
#define __STEPPERMOTORDRIVER_H__
#include <array>
#include <stdint.h>
#include "HalWrapper.h"

#ifndef TESTING
#define HAL_WRAPPER HalWrapper
#else
#include "Mocks/HalWrapperMock.h"
#define HAL_WRAPPER HalWrapperMock
#endif

using AngleX10 = uint8_t;
using PinNr = uint16_t;
using PinOrder = std::array<std::pair<GPIO_TypeDef*, PinNr>, 4>;
using PhaseToChange = uint8_t;

enum class ICDriver_e
{
    L293D, A4998, DRV8825
};

enum class StpMotDriverMode_e
{
    GPIO_TOGGLING, PWM
};

constexpr AngleX10 CheckAngle(AngleX10 angle)
{
    // Supported angles (x10) of stepper motors (drivers)
    constexpr std::array<AngleX10, 10> AnglesLookUpTable = 
    {9, 18, 27, 36, 45,
    54, 63, 71, 80, 89};
    for (auto a : AnglesLookUpTable)
    {
        if (a == angle)
        {
            return angle;
        }
    }
    return 0;
}

template <typename T>
class StpMotDriver
{
private:
    ICDriver_e m_IcName;
    AngleX10 m_Angle;
    StpMotDriverMode_e m_OperationMode;
    AngleX10 m_AnglePosition;
    
public:
    StpMotDriver()
    { }

    constexpr StpMotDriver(const ICDriver_e icName, const AngleX10 angle,
                           const StpMotDriverMode_e operationMode)
    : m_IcName(icName), m_Angle(angle), m_OperationMode(operationMode), 
      m_AnglePosition(0)
    { }

    // Common method for each derived classes
    constexpr ICDriver_e GetICDriver() const;
    constexpr StpMotDriverMode_e GetOperationMode() const;
    constexpr AngleX10 GetAngle() const;
    void IncrementPosition();
    void DecrementPosition();
    AngleX10 GetAnglePosition() const;

    // Interface methods, must be overwritten by derived classes
    void SetPinOrder(PinOrder& pinOrder);
    const PinOrder& GetPinOrder() const;
    void RotateMotorOneStep();
    void RotateMotorOneStepReverse();

};

class StpMotDriver_CheckCompileTime : public StpMotDriver<StpMotDriver_CheckCompileTime>
{
public:
    constexpr StpMotDriver_CheckCompileTime(const ICDriver_e icName, const AngleX10 angle,
                                  const StpMotDriverMode_e opMode)
    : StpMotDriver(icName, angle, opMode)
    {
    }

};

template<AngleX10 angle>
class StpMotDriver_L293D : public StpMotDriver<StpMotDriver_L293D<angle>>
{
private:
    constexpr void m_CheckCompileTime();
    PinOrder m_PinOrder;
    PhaseToChange m_PhaseToChange;
    HalWrapperInterface<HAL_WRAPPER>& m_HalWrapper;

public:
    StpMotDriver_L293D(HAL_WRAPPER& halWrapper)
    : StpMotDriver<StpMotDriver_L293D<angle>>(ICDriver_e::L293D, angle, StpMotDriverMode_e::GPIO_TOGGLING),
      m_PhaseToChange(0), m_HalWrapper(halWrapper)
    {
        m_CheckCompileTime();
    }

    void SetPinOrder(PinOrder& pinOrder);
    const PinOrder& GetPinOrder() const;
    void RotateMotorOneStep();
    void RotateMotorOneStepReverse();
    
};

// CRTP interface methods implementation

template <typename T>
constexpr ICDriver_e StpMotDriver<T>::GetICDriver() const
{
    return m_IcName;
}

template <typename T>
constexpr StpMotDriverMode_e StpMotDriver<T>::GetOperationMode() const
{
    return m_OperationMode;
}

template <typename T>
constexpr AngleX10 StpMotDriver<T>::GetAngle() const
{
    return m_Angle;
}

template <typename T>
void StpMotDriver<T>::IncrementPosition()
{
    m_AnglePosition += m_Angle;
}

template <typename T>
void StpMotDriver<T>::DecrementPosition()
{
    m_AnglePosition -= m_Angle;
}

template <typename T>
AngleX10 StpMotDriver<T>::GetAnglePosition() const
{
    return m_AnglePosition;
}

template <typename T>
void StpMotDriver<T>::SetPinOrder(PinOrder& pinOrder)
{
    static_cast<T&>(*this).SetPinOrder(pinOrder);
}

template <typename T>
const PinOrder& StpMotDriver<T>::GetPinOrder() const
{
    return static_cast<const T&>(*this).GetPinOrder();
}

template <typename T>
void StpMotDriver<T>::RotateMotorOneStep()
{
    static_cast<T&>(*this).RotateMotorOneStep();
}

template <typename T>
void StpMotDriver<T>::RotateMotorOneStepReverse()
{
    static_cast<T&>(*this).RotateMotorOneStepReverse();
}

template<AngleX10 angle>
constexpr void StpMotDriver_L293D<angle>::m_CheckCompileTime()
{
    constexpr StpMotDriver_CheckCompileTime obj(ICDriver_e::L293D, angle, StpMotDriverMode_e::GPIO_TOGGLING);
    static_assert(obj.GetICDriver() == ICDriver_e::L293D,
                  "[ERROR]: Wrong IC, should be L293D\n");
    static_assert(CheckAngle(angle) == angle, "[ERROR]: Not supported angle value\n");
    static_assert(obj.GetOperationMode() == StpMotDriverMode_e::GPIO_TOGGLING,
                  "[ERROR]: This driver operates on GPIOs\n");
}

#endif

