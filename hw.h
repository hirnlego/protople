#pragma once

#include "Utility/dsp.h"
#include "util/CpuLoadMeter.h"
#include "daisy_seed.h"
#include <time.h>

#define N_MUXES 5

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

#define GATE1_PIN 26 // I/O
#define GATE2_PIN 27 // I/O
#define GATE3_PIN 29 // I/O
#define GATE4_PIN 30 // I/O Could be used as MIDI in, needs a stereo jack and more circuitry, though

#define CV1_PIN 15
#define CV2_PIN 16
#define CV3_PIN 17
#define CV4_PIN 18
#define CV5_PIN 19

#define DAC_OUT1_PIN 22 // Also CV6
#define DAC_OUT2_PIN 23 // Also CV7

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
        TRIM_1, // Mux 1, pin 0 - Simple pin 1
        TRIM_2, // Mux 1, pin 4 - Simple pin 12
        TRIM_3, // Mux 2, pin 2 - Simple pin 22
        TRIM_4, // Mux 2, pin 6 - Simple pin 32
        TRIM_5, // Mux 3, pin 2 - Simple pin 42
        TRIM_6, // Mux 4, pin 0 - Simple pin 52
        TRIM_7, // Mux 4, pin 4 - Simple pin 62
        TRIM_8, // Mux 5, pin 0 - Simple pin 72
        KNOB_1, // Mux 1, pin 2 - Simple pin 8
        KNOB_2, // Mux 1, pin 6 - Simple pin 18
        KNOB_3, // Mux 2, pin 4 - Simple pin 28
        KNOB_4, // Mux 3, pin 0 - Simple pin 38
        KNOB_5, // Mux 3, pin 4 - Simple pin 48
        KNOB_6, // Mux 4, pin 2 - Simple pin 58
        KNOB_7, // Mux 4, pin 6 - Simple pin 68
        KNOB_8, // Mux 5, pin 2 - Simple pin 78
        KNOB_9, // Mux 1, pin 1 - Simple pin 5
        KNOB_10, // Mux 1, pin 5 - Simple pin 15
        KNOB_11, // Mux 2, pin 3 - Simple pin 25
        KNOB_12, // Mux 2, pin 7 - Simple pin 35
        KNOB_13, // Mux 3, pin 3 - Simple pin 45
        KNOB_14, // Mux 4, pin 1 - Simple pin 55
        KNOB_15, // Mux 4, pin 5 - Simple pin 65
        KNOB_16, // Mux 5, pin 1 - Simple pin 75
        TOGGLE_1, // Mux 1, pin 3 - Simple pin 10
        TOGGLE_2, // Mux 2, pin 5 - Simple pin 30
        TOGGLE_3, // Mux 3, pin 5 - Simple pin 50
        TOGGLE_4, // Mux 4, pin 7 - Simple pin 70
        SELECTOR1_A, // Mux 2, pin 0 - Simple pin 21
        SELECTOR1_B, // Mux 2, pin 1 - Simple pin 21
        SELECTOR2_A, // Mux 3, pin 6 - Simple pin 51
        SELECTOR2_B, // Mux 3, pin 7 - Simple pin 51
        BUTTON_1, // Mux 1, pin 7 - Simple pin 20
        BUTTON_2, // Mux 3, pin 1 - Simple pin 40
        BUTTON_3, // Mux 4, pin 3 - Simple pin 60
        BUTTON_4, // Mux 5, pin 3 - Simple pin 80
        CONTROL_LAST,
    };

    enum Cv
    {
        CV1,
        CV2,
        CV3,
        CV4,
        CV5,
        CV6, // Also DAC out 1
        CV7, // Also DAC out 2
        CV_LAST,
    };

    enum Gate
    {
        GATE_IN1,
        GATE_IN2, // Also MIDI IN, see comment above
        GATE_OUT1,
        GATE_OUT2,
        GATE_LAST,
    };

    AnalogControl controls[CONTROL_LAST];
    //Parameter knobs[Knob::KNOB_LAST];
    GateIn gateIns[2];
    dsy_gpio gateOuts[2];

    void InitControls()
    {
        short muxAdcPins[N_MUXES] = {
            ADC_MUX1_PIN,
            ADC_MUX2_PIN,
            ADC_MUX3_PIN,
            ADC_MUX4_PIN,
            ADC_MUX5_PIN,
        };

        short muxAPins[N_MUXES] = {
            MUX1_A_PIN,
            MUX2_A_PIN,
            MUX3_A_PIN,
            MUX4_A_PIN,
            MUX5_A_PIN,
        };

        short muxBPins[N_MUXES] = {
            MUX1_B_PIN,
            MUX2_B_PIN,
            MUX3_B_PIN,
            MUX4_B_PIN,
            MUX5_B_PIN,
        };

        short muxCPins[N_MUXES] = {
            MUX1_C_PIN,
            MUX2_C_PIN,
            MUX3_C_PIN,
            MUX4_C_PIN,
            MUX5_C_PIN,
        };

        short cvPins[CV_LAST] = {
            CV1_PIN,
            CV2_PIN,
            CV3_PIN,
            CV4_PIN,
            CV5_PIN,
            DAC_OUT1_PIN,
            DAC_OUT2_PIN,
        };

        AdcChannelConfig adcChannels[N_MUXES + CV_LAST];
        for (short i = 0; i < N_MUXES; i++)
        {
            adcChannels[i].InitMux(seed.GetPin(muxAdcPins[i]), 8, seed.GetPin(muxAPins[i]), seed.GetPin(muxBPins[i]), seed.GetPin(muxCPins[i]));
        }
        for (short i = N_MUXES; i < N_MUXES + CV_LAST; i++)
        {
            adcChannels[i].InitSingle(seed.GetPin(cvPins[i - N_MUXES]));
        }
        seed.adc.Init(adcChannels, N_MUXES + CV_LAST);

        // Mux'd controls.
        controls[TRIM_1].Init(seed.adc.GetMuxPtr(0, 0), seed.AudioCallbackRate(), true);
        controls[TRIM_2].Init(seed.adc.GetMuxPtr(0, 4), seed.AudioCallbackRate(), true);

        controls[KNOB_1].Init(seed.adc.GetMuxPtr(0, 2), seed.AudioCallbackRate(), true);
        controls[KNOB_2].Init(seed.adc.GetMuxPtr(0, 6), seed.AudioCallbackRate(), true);

        controls[KNOB_9].Init(seed.adc.GetMuxPtr(0, 1), seed.AudioCallbackRate(), true);
        controls[KNOB_10].Init(seed.adc.GetMuxPtr(0, 5), seed.AudioCallbackRate(), true);

        controls[TOGGLE_1].Init(seed.adc.GetMuxPtr(0, 3), seed.AudioCallbackRate());

        controls[BUTTON_1].Init(seed.adc.GetMuxPtr(0, 7), seed.AudioCallbackRate());

        // Direct controls.
        controls[CV1].Init(seed.adc.GetPtr(N_MUXES), seed.AudioCallbackRate());
        controls[CV2].Init(seed.adc.GetPtr(N_MUXES + 1), seed.AudioCallbackRate());
        controls[CV3].Init(seed.adc.GetPtr(N_MUXES + 2), seed.AudioCallbackRate());
        controls[CV4].Init(seed.adc.GetPtr(N_MUXES + 3), seed.AudioCallbackRate());
        controls[CV5].Init(seed.adc.GetPtr(N_MUXES + 4), seed.AudioCallbackRate());
    }

    void InitCvOutputs()
    {
        //    dsy_dac_init(&seed.dac_handle, DSY_DAC_CHN_BOTH);
        //    dsy_dac_write(DSY_DAC_CHN1, 0);
        //    dsy_dac_write(DSY_DAC_CHN2, 0);
        DacHandle::Config cfg;
        cfg.bitdepth   = DacHandle::BitDepth::BITS_12;
        cfg.buff_state = DacHandle::BufferState::ENABLED;
        cfg.mode       = DacHandle::Mode::POLLING;
        cfg.chn        = DacHandle::Channel::BOTH;
        seed.dac.Init(cfg);
        seed.dac.WriteValue(DacHandle::Channel::BOTH, 0);
    }

    void InitGates()
    {
        // Gate outs.
        gateOuts[0].pin  = seed.GetPin(GATE1_PIN);
        gateOuts[0].mode = DSY_GPIO_MODE_OUTPUT_PP;
        gateOuts[0].pull = DSY_GPIO_NOPULL;
        dsy_gpio_init(&gateOuts[0]);

        gateOuts[1].pin  = seed.GetPin(GATE2_PIN);
        gateOuts[1].mode = DSY_GPIO_MODE_OUTPUT_PP;
        gateOuts[1].pull = DSY_GPIO_NOPULL;
        dsy_gpio_init(&gateOuts[1]);

        // Gate Inputs
        dsy_gpio_pin pin;
        pin = seed.GetPin(GATE3_PIN);
        gateIns[GATE_IN1].Init(&pin);
        pin = seed.GetPin(GATE4_PIN);
        gateIns[GATE_IN2].Init(&pin);
    }

    inline void InitHw()
    {
        seed.Configure();
        seed.Init(true);
        seed.SetAudioBlockSize(48);

        InitControls();
        InitCvOutputs();
        InitGates();

/*
        for (short i = 0; i < BUTTON_LAST; i++)
        {
            dsy_gpio_pin p = seed.GetPin(buttonPins[i]);
            buttons[i].Init(p);
        }

*/
        srand(time(NULL));
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
}