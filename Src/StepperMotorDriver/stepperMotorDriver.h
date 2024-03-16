#ifndef __STEPPERMOTORDRIVER_H__
#define __STEPPERMOTORDRIVER_H__

enum class ICDriver_e
{
    L293D, A4998, DRV8825
};

template <typename T>
class StpMotDriver
{
protected:
    ICDriver_e m_IcName;
    float m_Angle;
    
public:
    constexpr StpMotDriver(ICDriver_e icName, float angle)
    :m_IcName(icName), m_Angle(angle) {}

    constexpr ICDriver_e GetICDriver() const
    {
        return m_IcName;
    }

};

class StpMotDriver_L293D : public StpMotDriver<StpMotDriver_L293D>
{

public:
    constexpr StpMotDriver_L293D(float angle)
    :StpMotDriver(ICDriver_e::L293D, angle) {}
};

#endif

