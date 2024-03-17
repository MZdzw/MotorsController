#include "stepperMotorDriver.h"

template<AngleX10 angle>
void StpMotDriver_L293D<angle>::SetPinOrder(const PinOrder& pinOrder)
{
    m_PinOrder = pinOrder;
}

template<AngleX10 angle>
PinOrder StpMotDriver_L293D<angle>::GetPinOrder()
{
    return m_PinOrder;
}

// Explicit instantiation of template class for specific values of angle
// Getting linking error without instantation, because compiler can ommit
// generating code in object file (.o) if the method body does not use
// template parameter. 
template class StpMotDriver_L293D<18>;

