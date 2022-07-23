#pragma once

#include "protopletest.h"

namespace protople
{
    float values[CONTROL_LAST]{};

    bool startUp{true};
    bool first{true};

    inline void ProcessParameter(short idx, float value)
    {
        switch (idx)
        {
        case TRIM_1:
            break;
        case TRIM_2:
            break;
        case TRIM_3:
            break;
        case TRIM_4:
            break;
        case TRIM_5:
            break;
        case TRIM_6:
            break;
        case TRIM_7:
            break;
        case TRIM_8:
            break;
        case KNOB_1:
            reso.SetDecay(value);
            break;
        case KNOB_2:
            reso.SetFrequency(Map(value, 0.f, 1.f, 20.f, 4000.f));
            break;
        case KNOB_3:
            reso.SetRatio(std::floor(Map(value, 0.f, 1.f, 1, 7)));
            break;
        case KNOB_4:
            break;
        case KNOB_5:
            break;
        case KNOB_6:
            break;
        case KNOB_7:
            break;
        case KNOB_8:
            break;
        case KNOB_9:
            break;
        case KNOB_10:
            break;
        case KNOB_11:
            break;
        case KNOB_12:
            break;
        case KNOB_13:
            break;
        case KNOB_14:
            break;
        case KNOB_15:
            break;
        case KNOB_16:
            break;
        case TOGGLE_1:
            break;
        case TOGGLE_2:
            break;
        case TOGGLE_3:
            break;
        case TOGGLE_4:
            break;
        case SELECTOR_1:
            break;
        case SELECTOR_2:
            break;
        case BUTTON_1:
            break;
        case BUTTON_2:
            break;
        case BUTTON_3:
            break;
        case BUTTON_4:
            break;

        default:
            break;
        }
    }

    void ProcessCv(short idx, float value)
    {
        switch (idx)
        {
        case CV_IN_1:
            break;
        case CV_IN_2:
            break;
        case CV_IN_3:
            break;
        case CV_IN_4:
            break;
        case CV_IN_5:
            break;

        default:
            break;
        }
    }

    inline void ProcessControl(int idx, bool check = true)
    {
        float value = GetControlValue(idx);

        // Handle range limits.
        if (idx >= TRIM_1 && idx <= KNOB_16)
        {
            if (value < kMinValueDelta)
            {
                value = 0.f;
            }
            else if (value > 1 - kMinValueDelta)
            {
                value = 1.f;
            }

            // Process the parameter only if it actually changed.
            if (std::abs(values[idx] - value) > kMinValueDelta || !check)
            {
                ProcessParameter(idx, value);

                values[idx] = value;
            }
        }
        else
        {
            // Process the parameter only if it actually changed.
            if (value != values[idx] || !check)
            {
                ProcessParameter(idx, value);

                values[idx] = value;
            }
        }
    }

    inline void ProcessCvIn(int idx)
    {
        float value = GetCvValue(idx);

        ProcessCv(idx, value);
    }

    inline void ProcessUi()
    {
        for (short i = 0; i < CONTROL_LAST; i++)
        {
            ProcessControl(i);
        }
        for (short i = 0; i < CV_IN_LAST; i++)
        {
            ProcessCvIn(i);
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