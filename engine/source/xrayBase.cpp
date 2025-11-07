#include "xrayBase.hpp"

float XrayBase::CalculateIntensity(float intensity_0, float focusDistance_0, float focusDistance_1) const
{
    return intensity_0 / std::pow((focusDistance_0 / focusDistance_1), 2);
}

float XrayBase::ToMinute(float exposition, float mA) const
{
    return exposition / mA;
}

float XrayBase::ToSecond(float exposition, float mA) const
{
    return (exposition / mA) * 60;
}
