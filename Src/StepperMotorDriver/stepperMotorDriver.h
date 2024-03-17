#ifndef __STEPPERMOTORDRIVER_H__
#define __STEPPERMOTORDRIVER_H__
#include <array>
#include "HalWrapper.h"

#ifdef TESTING
#define THROW_COMPILE_TIME_EXCEPTION(condition, text) \
    if (condition) { throw text; }
#else
#define THROW_COMPILE_TIME_EXCEPTION(condition, text)
#endif

using AngleX10 = uint8_t;
using PinNr = uint16_t;
using PinOrder = std::array<std::pair<GPIO_TypeDef*, PinNr>, 4>;

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
protected:
    ICDriver_e m_IcName;
    float m_Angle;
    StpMotDriverMode_e m_OperationMode;
    
public:
    StpMotDriver()
    { }

    constexpr StpMotDriver(const ICDriver_e icName, const AngleX10 angle,
                           const StpMotDriverMode_e operationMode)
    :m_IcName(icName), m_Angle(angle), m_OperationMode(operationMode)
    { }

    constexpr ICDriver_e GetICDriver() const
    {
        return m_IcName;
    }

    constexpr StpMotDriverMode_e GetOperationMode() const
    {
        return m_OperationMode;
    }

    constexpr AngleX10 GetAngle() const
    {
        return m_Angle;
    }

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
    constexpr void CheckCompileTime();

    PinOrder m_PinOrder;

public:
    StpMotDriver_L293D()
    : StpMotDriver<StpMotDriver_L293D<angle>>(ICDriver_e::L293D, angle, StpMotDriverMode_e::GPIO_TOGGLING)
    {
        CheckCompileTime();
    }

    void SetPinOrder(const PinOrder& pinOrder);
    PinOrder GetPinOrder();
    
};

template<AngleX10 angle>
constexpr void StpMotDriver_L293D<angle>::CheckCompileTime()
{
    constexpr StpMotDriver_CheckCompileTime obj(ICDriver_e::L293D, angle, StpMotDriverMode_e::GPIO_TOGGLING);
    static_assert(obj.GetICDriver() == ICDriver_e::L293D,
                  "[ERROR]: Wrong IC, should be L293D\n");
    static_assert(CheckAngle(angle) == angle, "[ERROR]: Not supported angle value\n");
    static_assert(obj.GetOperationMode() == StpMotDriverMode_e::GPIO_TOGGLING,
                  "[ERROR]: This driver operates on GPIOs\n");
}

#endif

