#include "../include/height-setting.hpp"

void HeightSetting::SetMeterPrecision(int value)
{
    meterPrecision = value;
}
void HeightSetting::SetUseImperial(bool value)
{
    useImperial = value;
}
void HeightSetting::SetHeight(float value)
{
    meterHeight = value;
}
std::string HeightSetting::GetHeightText()
{
    if (!useImperial)
    {
        std::string preciseMeters = MeasurementsUtils::GetPrecisionFloatString(meterHeight, meterPrecision);
        std::string metricString = "<size=90%>" + preciseMeters + "m" + "</size>";
        return metricString;
    }
    
    auto imperialHeights = MeasurementsUtils::GetImperialHeight(meterHeight);
    int feet = imperialHeights.first;
    float inches = imperialHeights.second;
    std::string preciseInches = MeasurementsUtils::GetPrecisionFloatString(inches, 1);
    std::string imperialString = std::to_string(feet) + "\n" + preciseInches + "\"";
    return imperialString;
}