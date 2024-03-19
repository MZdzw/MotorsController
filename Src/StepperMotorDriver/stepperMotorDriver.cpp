#include "stepperMotorDriver.h"

template<AngleX10 angle>
void StpMotDriver_L293D<angle>::SetPinOrder(const PinOrder& pinOrder)
{
    m_PinOrder = pinOrder;
    m_HalWrap.GPIO_WritePin(m_PinOrder.at(0).first, m_PinOrder.at(0).second);
    m_HalWrap.GPIO_ResetPin(m_PinOrder.at(1).first, m_PinOrder.at(1).second);
    m_HalWrap.GPIO_WritePin(m_PinOrder.at(2).first, m_PinOrder.at(2).second);
    m_HalWrap.GPIO_ResetPin(m_PinOrder.at(3).first, m_PinOrder.at(3).second);
}

template<AngleX10 angle>
const PinOrder& StpMotDriver_L293D<angle>::GetPinOrder() const
{
    return m_PinOrder;
}

template<AngleX10 angle>
void StpMotDriver_L293D<angle>::RotateMotorOneStep()
{
    const auto& index = 2 * m_PhaseToChange;
    m_HalWrap.GPIO_TogglePin(m_PinOrder.at(index).first,
                             m_PinOrder.at(index).second);
    m_HalWrap.GPIO_TogglePin(m_PinOrder.at(index + 1).first,
                             m_PinOrder.at(index + 1).second);
    m_PhaseToChange ^= 0x01;
}

template<AngleX10 angle>
void StpMotDriver_L293D<angle>::RotateMotorOneStepReverse()
{
    m_PhaseToChange ^= 0x01;
    const auto& index = 2 * m_PhaseToChange;
    m_HalWrap.GPIO_TogglePin(m_PinOrder.at(index).first,
                             m_PinOrder.at(index).second);
    m_HalWrap.GPIO_TogglePin(m_PinOrder.at(index + 1).first,
                             m_PinOrder.at(index + 1).second);
}

// Explicit instantiation of template class for specific values of angle
// Getting linking error without instantation, because compiler can ommit
// generating code in object file (.o) if the method body does not use
// template parameter. 
template class StpMotDriver_L293D<18>;

