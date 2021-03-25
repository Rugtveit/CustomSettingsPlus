#include <string>
#include "./utils/measurement-utils.hpp"

class HeightSetting {


    public: 
        HeightSetting()
        {
            useImperial = false;
            meterPrecision = 1;
            meterHeight = 0.0;
        }
        void SetMeterPrecision(int steps);
        void SetUseImperial(bool value);
        void SetHeight(float meter);
        std::string GetHeightText();
    private:
        bool useImperial;
        int meterPrecision;
        float meterHeight;
};