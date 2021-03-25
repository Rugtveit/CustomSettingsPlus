#include "../include/utils/measurement-utils.hpp"

std::pair<int, float> MeasurementsUtils::GetImperialHeight(float meters)
{
    float totalInches = meters / 0.0254;
    int feet = floor(totalInches/12);
    float inches = totalInches - (feet * 12);
    return std::make_pair(feet, inches);
}
std::string MeasurementsUtils::GetPrecisionFloatString(float value, int precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    std::string precisionFloatString = stream.str();
    return precisionFloatString;
}