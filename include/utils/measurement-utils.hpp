#include <utility>
#include <math.h>
#include <iomanip>
#include <sstream>

class MeasurementsUtils {
    public:
        static std::pair<int, float> GetImperialHeight(float heightMeter);
        static std::string GetPrecisionFloatString(float value, int precision);

};