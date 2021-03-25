#include <string>
#include "./utils/measurement-utils.hpp"

class HeightSetting {
    public: 
        void SetMeterPrecision(int steps);
        void SetUseImperial(bool value);
        void SetHeight(float meter);
        std::string GetHeightText();
    private:
        bool useImperial = false;
        int meterPrecision = 1;
        float meterHeight = 0.0;
};