#pragma once

#include "protopletest.h"
#include "Utility/dsp.h"
#include <string>

namespace protople
{
    using namespace daisy;
    using namespace daisysp;

    float values[CONTROL_LAST]{};

    bool startUp{true};
    bool first{true};

    inline void ProcessParameter(short idx, float value)
    {
        switch (idx)
        {
        case TRIM_1:
            osc.SetFreq(fmap(value, 20.f, 220.f));
            //osc.SetAmp(value);
            break;
        case TRIM_2:
            break;
        case TRIM_3:
            //osc.SetAmp(value);
            break;
        case TRIM_4:
            break;
        case KNOB_1:
            //osc.SetFreq(fmap(value, 20.f, 220.f));
            break;
        case KNOB_2:
            break;
        case KNOB_3:
            //osc.SetFreq(fmap(value, 20.f, 220.f));
            break;
        case KNOB_4:
            break;
        case KNOB_9:
            break;
        case KNOB_10:
            break;
        case KNOB_11:
            break;
        case KNOB_12:
            break;
        case TOGGLE_1:
            //osc.SetAmp(value);
            break;
        case BUTTON_1:
            //osc.SetAmp(value);
            break;

        default:
            break;
        }
    }

    inline void ProcessCv(short idx, float value)
    {
        switch (idx)
        {
        case CV_IN1:
            //osc.SetFreq(100 + value);
            break;

        default:
            break;
        }
    }

    inline void ProcessControl(int idx, bool check = true)
    {
        float value = GetControlValue(idx);

        // Process the parameter only if it actually changed.
        if (std::abs(values[idx] - value) > kMinValueDelta || !check)
        {
            ProcessParameter(idx, value);

            values[idx] = value;
        }
    }

    inline void ProcessUi()
    {
        for (short i = 0; i < CONTROL_LAST; i++)
        {
            ProcessControl(i);
        }
    }

    inline void InitUi()
    {
        // Set initial values based on the controls.
        for (short i = 0; i < CONTROL_LAST; i++)
        {
            ProcessControl(i, false);
        }
    }
}