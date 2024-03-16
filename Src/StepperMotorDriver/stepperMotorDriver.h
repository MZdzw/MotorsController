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

enum class ICDriver_e
{
    L293D, A4998, DRV8825
};

enum class StpMotDriverMode_e
{
    GPIO_TOGGLING, PWM
};

template <int N>
struct Angles
{
    constexpr Angles() : values()
    {
        for (auto i = 0; i < N; ++i)
        {
            values[i] = (i + 1) * 0.9f;
        }
    }
    float values[N];
};

constexpr bool CheckAngle(AngleX10 angle)
{
    // Supported angles (x10) of stepper motors (drivers)
    constexpr std::array<AngleX10, 10> AnglesLookUpTable = 
    {9, 18, 27, 36, 45,
    54, 63, 71, 80, 89};
    for (auto a : AnglesLookUpTable)
    {
        if (a == angle)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
class StpMotDriver
{
protected:
    ICDriver_e m_IcName;
    float m_Angle;
    StpMotDriverMode_e m_OperationMode;
    
public:
    constexpr StpMotDriver(const ICDriver_e icName, const AngleX10 angle,
                           const StpMotDriverMode_e operationMode)
    :m_IcName(icName), m_Angle(angle), m_OperationMode(operationMode)
    {}

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

class StpMotDriver_L293D : public StpMotDriver<StpMotDriver_L293D>
{

public:
    constexpr StpMotDriver_L293D(const AngleX10 angle)
    : StpMotDriver(ICDriver_e::L293D, angle, StpMotDriverMode_e::GPIO_TOGGLING)
    {
        THROW_COMPILE_TIME_EXCEPTION(GetICDriver() != ICDriver_e::L293D,
                                     "[ERROR]: Wrong IC, should be L293D\n")
        THROW_COMPILE_TIME_EXCEPTION(GetOperationMode() != StpMotDriverMode_e::GPIO_TOGGLING,
                                     "[ERROR]: This driver operates on GPIOs\n")
        THROW_COMPILE_TIME_EXCEPTION(!CheckAngle(GetAngle()),
                                     "[ERROR]: Not supported angle value\n")
    }

};

#endif

