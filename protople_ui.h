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

    /*
        - note
        - pan
        - R/F
        - D/R
        - fx dry/wet

        GRANULATOR:
        - input gain
        - volume

        - speed
        - feedback
        - size
        - grain size

        OSCBANK:
        - volume

        - ratio 1
        - ratio 2
        - ratio 3
        - ratio 4

        RESONATOR:
        - decay
        - ratio
        - (note)

        FILTER:
        - frequency
        - resonance

        DELAY:
        - feedback
        - time

        - ratio 1
        - ratio 2
        - ratio 3
        - ratio 4

        REVERB:
        - decay
        - filter

        Macros:

        1) Resonator decay - Filter resonance
        2) Resonator ratio - Filter frequency
        3) Delay feedback - Reverb decay
        4) Delay time - Reverb filter

        Toggles:

        1) Record
        2) Internal/external
        3) ?
        4) ?

        Buttons:

        1) Randomize all
        2) Randomize osc
        3) Randomize granulator
        4) Randomize fx

    */
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
            break;
        case KNOB_2:
            break;
        case KNOB_3:
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
float min{};
float max{};
    void ProcessCv(short idx, float value)
    {
        switch (idx)
        {
        case CV_IN_1:
        {
            osc.SetAmp(value * 2 - 1); // Handles unipolar value
            break;
        }
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