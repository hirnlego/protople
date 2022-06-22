#pragma once

#include "Utility/dsp.h"
#include "util/CpuLoadMeter.h"
#include "daisy_seed.h"
#include <time.h>

#define ADC_MUX1_PIN 28
#define ADC_MUX2_PIN 25
#define ADC_MUX3_PIN 24
#define ADC_MUX4_PIN 21
#define ADC_MUX5_PIN 20

#define MUX1_A_PIN 0
#define MUX1_B_PIN 1
#define MUX1_C_PIN 2
#define MUX2_A_PIN 3
#define MUX2_B_PIN 4
#define MUX2_C_PIN 5
#define MUX3_A_PIN 6
#define MUX3_B_PIN 7
#define MUX3_C_PIN 8
#define MUX4_A_PIN 9
#define MUX4_B_PIN 10
#define MUX4_C_PIN 11
#define MUX5_A_PIN 12
#define MUX5_B_PIN 13
#define MUX5_C_PIN 14

#define MAX_RESOLUTION 65400.f

namespace protople
{
    using namespace daisy;
    using namespace daisysp;

    // The minimum difference in parameter value to be registered.
    constexpr float kMinValueDelta{0.001f};

    DaisySeed seed;

    CpuLoadMeter cpuMeter;

    enum Control
    {
        TRIM_1,
        TRIM_2,
        TRIM_3,
        TRIM_4,
        TRIM_5,
        TRIM_6,
        TRIM_7,
        TRIM_8,
        KNOB_1,
        KNOB_2,
        KNOB_3,
        KNOB_4,
        KNOB_5,
        KNOB_6,
        KNOB_7,
        KNOB_8,
        KNOB_9,
        KNOB_10,
        KNOB_11,
        KNOB_12,
        KNOB_13,
        KNOB_14,
        KNOB_15,
        KNOB_16,
        TOGGLE_1,
        TOGGLE_2,
        TOGGLE_3,
        TOGGLE_4,
        THREEWAY_1,
        THREEWAY_2,
        BUTTON_1,
        BUTTON_2,
        BUTTON_3,
        BUTTON_4,
        CONTROL_LAST,
    };

    AnalogControl controls[CONTROL_LAST];
    //Parameter knobs[Knob::KNOB_LAST];
    GateIn gate_in;

    bool gate_in_trig_;    // True when triggered.

    inline void InitHw()
    {
        seed.Configure();
        seed.Init(true);
        seed.SetAudioBlockSize(48);
        float blockRate = seed.AudioSampleRate() / (float)seed.AudioBlockSize();

        short muxAdcPins[5] = {
            ADC_MUX1_PIN,
            ADC_MUX2_PIN,
            ADC_MUX3_PIN,
            ADC_MUX4_PIN,
            ADC_MUX5_PIN,
        };

        short muxAPins[5] = {
            MUX1_A_PIN,
            MUX2_A_PIN,
            MUX3_A_PIN,
            MUX4_A_PIN,
            MUX5_A_PIN,
        };

        short muxBPins[5] = {
            MUX1_B_PIN,
            MUX2_B_PIN,
            MUX3_B_PIN,
            MUX4_B_PIN,
            MUX5_B_PIN,
        };

        short muxCPins[5] = {
            MUX1_C_PIN,
            MUX2_C_PIN,
            MUX3_C_PIN,
            MUX4_C_PIN,
            MUX5_C_PIN,
        };

        AdcChannelConfig muxes[5];

        for (short i = 0; i < 5; i++)
        {
            muxes[i].InitMux(seed.GetPin(muxAdcPins[i]), 8, seed.GetPin(muxAPins[i]), seed.GetPin(muxBPins[i]), seed.GetPin(muxCPins[i]));
        }
        seed.adc.Init(muxes, 5);

        controls[TRIM_1].Init(seed.adc.GetMuxPtr(0, 0), seed.AudioCallbackRate(), true);
        controls[TRIM_2].Init(seed.adc.GetMuxPtr(0, 4), seed.AudioCallbackRate(), true);

        controls[KNOB_1].Init(seed.adc.GetMuxPtr(0, 2), seed.AudioCallbackRate(), true);
        controls[KNOB_2].Init(seed.adc.GetMuxPtr(0, 6), seed.AudioCallbackRate(), true);

        controls[KNOB_9].Init(seed.adc.GetMuxPtr(0, 1), seed.AudioCallbackRate(), true);
        controls[KNOB_10].Init(seed.adc.GetMuxPtr(0, 5), seed.AudioCallbackRate(), true);

        controls[TOGGLE_1].Init(seed.adc.GetMuxPtr(0, 3), seed.AudioCallbackRate());

        controls[BUTTON_1].Init(seed.adc.GetMuxPtr(0, 7), seed.AudioCallbackRate());


/*
        for (short i = 0; i < BUTTON_LAST; i++)
        {
            dsy_gpio_pin p = seed.GetPin(buttonPins[i]);
            buttons[i].Init(p);
        }

        dsy_gpio_pin gate_in_pin;
        gate_in_pin = seed.GetPin(GATE_IN1_PIN);
        gate_in.Init(&gate_in_pin);
*/
        srand(time(NULL));
    }

    float GetControlValue(short idx)
    {
        float value = controls[idx].Process();

        // Handle range limits.
        if (value < kMinValueDelta)
        {
            value = 0.f;
        }
        else if (value > 1 - kMinValueDelta)
        {
            value = 1.f;
        }

        // Toggles only have two values.
        if (idx >= TOGGLE_1 && idx <= TOGGLE_4)
        {
            value = value > 0.f ? 1.f : 0.f;
        }
        // Buttons too, but inverted.
        else if (idx >= BUTTON_1 && idx <= BUTTON_4)
        {
            value = value > 0.f ? 0.f : 1.f;
        }

        return value;
    }

    void StartAudio(AudioHandle::AudioCallback cb)
    {
        seed.StartAudio(cb);
    }

    void StartAdc()
    {
        seed.adc.Start();
    }

    float GetAudioSampleRate()
    {
        return seed.AudioSampleRate();
    }

    void InitCpuMeter(float sampleRate, int blockSize)
    {
        cpuMeter.Init(sampleRate, blockSize);
    }

    void StartCpuMeter()
    {
        cpuMeter.OnBlockStart();
    }

    void StopCpuMeter()
    {
        cpuMeter.OnBlockEnd();
    }

    inline void ProcessControls()
    {
        for (short i = 0; i < CONTROL_LAST; i++)
        {
            controls[i].Process();
        }

        // Gate Input
        gate_in_trig_ = gate_in.Trig();
    }
}