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
#define GATE3_PIN 29 // Gate out (37)
#define GATE4_PIN 30 // I/O Could be used as MIDI in, needs a stereo jack and more circuitry, though

#define CV1_PIN 15
#define CV2_PIN 16
#define CV3_PIN 17
#define CV4_PIN 18
#define CV5_PIN 19

#define DAC_OUT1_PIN 22
#define DAC_OUT2_PIN 23

namespace protople
{
    using namespace daisy;
    using namespace daisysp;

    // The minimum difference in parameter value to be registered.
    constexpr float kMinValueDelta{0.003f};

    DaisySeed seed;

    CpuLoadMeter cpuMeter;

    enum Control
    {
        TRIM_1, // Mux 1, pin 0 - Simple pin 1
        TRIM_2, // Mux 2, pin 4 - Simple pin 12
        TRIM_3, // Mux 2, pin 0 - Simple pin 22
        TRIM_4, // Mux 1, pin 4 - Simple pin 32
        TRIM_5, // Mux 3, pin 0 - Simple pin 42
        TRIM_6, // Mux 3, pin 4 - Simple pin 52
        TRIM_7, // Mux 4, pin 4 - Simple pin 62
        TRIM_8, // Mux 4, pin 0 - Simple pin 72

        KNOB_1, // Mux 2, pin 2 - Simple pin 8
        KNOB_2, // Mux 1, pin 6 - Simple pin 18
        KNOB_3, // Mux 1, pin 2 - Simple pin 28
        KNOB_4, // Mux 2, pin 6 - Simple pin 38
        KNOB_5, // Mux 3, pin 2 - Simple pin 48
        KNOB_6, // Mux 3, pin 6 - Simple pin 58
        KNOB_7, // Mux 4, pin 6 - Simple pin 68
        KNOB_8, // Mux 4, pin 2 - Simple pin 78

        KNOB_9, // Mux 2, pin 1 - Simple pin 5
        KNOB_10, // Mux 1, pin 5 - Simple pin 15
        KNOB_11, // Mux 1, pin 1 - Simple pin 25
        KNOB_12, // Mux 2, pin 5 - Simple pin 35
        KNOB_13, // Mux 3, pin 1 - Simple pin 45
        KNOB_14, // Mux 3, pin 5 - Simple pin 55
        KNOB_15, // Mux 4, pin 5 - Simple pin 65
        KNOB_16, // Mux 4, pin 1 - Simple pin 75

        TOGGLE_1, // Mux 2 pin 3 - Simple pin 10
        TOGGLE_2, // Mux 1, pin 3 - Simple pin 30
        TOGGLE_3, // Mux 3, pin 3 - Simple pin 50
        TOGGLE_4, // Mux 4, pin 7 - Simple pin 70

        SELECTOR_1, // Maps SELECTOR_1A and SELECTOR_1B
        SELECTOR_1A, // DNU - Mux 5, pin 0 - Simple pin 21
        SELECTOR_1B, // DNU - Mux 5, pin 1 - Simple pin 21
        SELECTOR_2, // Maps SELECTOR_2A and SELECTOR_2B
        SELECTOR_2A, // DNU - Mux 5, pin 6 - Simple pin 51
        SELECTOR_2B, // DNU - Mux 5, pin 7 - Simple pin 51

        BUTTON_1, // Mux 1, pin 7 - Simple pin 20
        BUTTON_2, // Mux 2, pin 7 - Simple pin 40
        BUTTON_3, // Mux 3, pin 7 - Simple pin 60
        BUTTON_4, // Mux 4, pin 3 - Simple pin 80
        CONTROL_LAST,
    };

    enum CvIn
    {
        CV_IN_1, // Simple pin 26 -> Daisy pin 15 (30)
        CV_IN_2, // Simple pin 31 -> Daisy pin 16 (31)
        CV_IN_3, // Simple pin 36 -> Daisy pin 17 (32)
        CV_IN_4, // Simple pin 41 -> Daisy pin 18 (33)
        CV_IN_5, // Simple pin 46 -> Daisy pin 19 (34)
        CV_IN_LAST,
    };

    enum CvOut
    {
        CV_OUT_1, // Simple pin 56 -> Daisy pin 22 (38)
        CV_OUT_2, // Simple pin 61 -> Daisy pin 23 (37)
        CV_OUT_LAST,
    };

    enum Gate
    {
        GATE_IN_1, // Simple pin 66 -> Daisy pin 26 (34)
        GATE_IN_2, // Simple pin 71 -> Daisy pin 27 (35)
        GATE_OUT_, // Simple pin 76 -> Daisy pin 29 (37)
        GATE_LAST,
    };

    AnalogControl controls[CONTROL_LAST];
    AnalogControl cvIns[CV_IN_LAST];
    GateIn gateIns[2];
    dsy_gpio gateOut;

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

        short cvPins[CV_IN_LAST] = {
            CV1_PIN,
            CV2_PIN,
            CV3_PIN,
            CV4_PIN,
            CV5_PIN,
        };

        AdcChannelConfig adcChannels[N_MUXES + CV_IN_LAST];
        for (short i = 0; i < N_MUXES; i++)
        {
            adcChannels[i].InitMux(seed.GetPin(muxAdcPins[i]), 8, seed.GetPin(muxAPins[i]), seed.GetPin(muxBPins[i]), seed.GetPin(muxCPins[i]));
        }
        for (short i = N_MUXES; i < N_MUXES + CV_IN_LAST; i++)
        {
            adcChannels[i].InitSingle(seed.GetPin(cvPins[i - N_MUXES]));
        }
        seed.adc.Init(adcChannels, N_MUXES + CV_IN_LAST);

        // Mux'd controls.
        controls[TRIM_1].Init(seed.adc.GetMuxPtr(0, 0), seed.AudioCallbackRate(), true);
        controls[TRIM_2].Init(seed.adc.GetMuxPtr(1, 4), seed.AudioCallbackRate(), true);
        controls[TRIM_3].Init(seed.adc.GetMuxPtr(1, 0), seed.AudioCallbackRate(), true);
        controls[TRIM_4].Init(seed.adc.GetMuxPtr(0, 4), seed.AudioCallbackRate(), true);
        controls[TRIM_5].Init(seed.adc.GetMuxPtr(2, 0), seed.AudioCallbackRate(), true);
        controls[TRIM_6].Init(seed.adc.GetMuxPtr(2, 4), seed.AudioCallbackRate(), true);
        controls[TRIM_7].Init(seed.adc.GetMuxPtr(3, 7), seed.AudioCallbackRate(), true);
        controls[TRIM_8].Init(seed.adc.GetMuxPtr(3, 3), seed.AudioCallbackRate(), true);

        controls[KNOB_1].Init(seed.adc.GetMuxPtr(1, 2), seed.AudioCallbackRate(), true);
        controls[KNOB_2].Init(seed.adc.GetMuxPtr(0, 6), seed.AudioCallbackRate(), true);
        controls[KNOB_3].Init(seed.adc.GetMuxPtr(0, 2), seed.AudioCallbackRate(), true);
        controls[KNOB_4].Init(seed.adc.GetMuxPtr(1, 6), seed.AudioCallbackRate(), true);
        controls[KNOB_5].Init(seed.adc.GetMuxPtr(2, 2), seed.AudioCallbackRate(), true);
        controls[KNOB_6].Init(seed.adc.GetMuxPtr(2, 6), seed.AudioCallbackRate(), true);
        controls[KNOB_7].Init(seed.adc.GetMuxPtr(3, 5), seed.AudioCallbackRate(), true);
        controls[KNOB_8].Init(seed.adc.GetMuxPtr(3, 1), seed.AudioCallbackRate(), true);

        controls[KNOB_9].Init(seed.adc.GetMuxPtr(1, 1), seed.AudioCallbackRate(), true);
        controls[KNOB_10].Init(seed.adc.GetMuxPtr(0, 5), seed.AudioCallbackRate(), true);
        controls[KNOB_11].Init(seed.adc.GetMuxPtr(0, 1), seed.AudioCallbackRate(), true);
        controls[KNOB_12].Init(seed.adc.GetMuxPtr(1, 5), seed.AudioCallbackRate(), true);
        controls[KNOB_13].Init(seed.adc.GetMuxPtr(2, 1), seed.AudioCallbackRate(), true);
        controls[KNOB_14].Init(seed.adc.GetMuxPtr(2, 5), seed.AudioCallbackRate(), true);
        controls[KNOB_15].Init(seed.adc.GetMuxPtr(3, 6), seed.AudioCallbackRate(), true);
        controls[KNOB_16].Init(seed.adc.GetMuxPtr(3, 2), seed.AudioCallbackRate(), true);

        controls[TOGGLE_1].Init(seed.adc.GetMuxPtr(1, 3), seed.AudioCallbackRate());
        controls[TOGGLE_2].Init(seed.adc.GetMuxPtr(0, 3), seed.AudioCallbackRate());
        controls[TOGGLE_3].Init(seed.adc.GetMuxPtr(2, 3), seed.AudioCallbackRate());
        controls[TOGGLE_4].Init(seed.adc.GetMuxPtr(3, 0), seed.AudioCallbackRate());

        controls[SELECTOR_1A].Init(seed.adc.GetMuxPtr(4, 2), seed.AudioCallbackRate());
        controls[SELECTOR_1B].Init(seed.adc.GetMuxPtr(4, 3), seed.AudioCallbackRate());
        controls[SELECTOR_2A].Init(seed.adc.GetMuxPtr(4, 0), seed.AudioCallbackRate());
        controls[SELECTOR_2B].Init(seed.adc.GetMuxPtr(4, 1), seed.AudioCallbackRate());

        controls[BUTTON_1].Init(seed.adc.GetMuxPtr(0, 7), seed.AudioCallbackRate());
        controls[BUTTON_2].Init(seed.adc.GetMuxPtr(1, 7), seed.AudioCallbackRate());
        controls[BUTTON_3].Init(seed.adc.GetMuxPtr(2, 7), seed.AudioCallbackRate());
        controls[BUTTON_4].Init(seed.adc.GetMuxPtr(3, 0), seed.AudioCallbackRate());

        // Non-mux'd controls.
        cvIns[CV_IN_1].Init(seed.adc.GetPtr(N_MUXES), seed.AudioCallbackRate(), true);
        cvIns[CV_IN_2].Init(seed.adc.GetPtr(N_MUXES + 1), seed.AudioCallbackRate());
        cvIns[CV_IN_3].Init(seed.adc.GetPtr(N_MUXES + 2), seed.AudioCallbackRate());
        cvIns[CV_IN_4].Init(seed.adc.GetPtr(N_MUXES + 3), seed.AudioCallbackRate());
        cvIns[CV_IN_5].Init(seed.adc.GetPtr(N_MUXES + 4), seed.AudioCallbackRate());
    }

    void InitCvOuts()
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
        // Gate ins.
        dsy_gpio_pin pin;
        pin = seed.GetPin(GATE1_PIN);
        gateIns[GATE_IN_1].Init(&pin);
        pin = seed.GetPin(GATE2_PIN);
        gateIns[GATE_IN_2].Init(&pin);

        // Gate out.
        gateOut.pin  = seed.GetPin(GATE3_PIN);
        gateOut.mode = DSY_GPIO_MODE_OUTPUT_PP;
        gateOut.pull = DSY_GPIO_NOPULL;
        dsy_gpio_init(&gateOut);
    }

    inline void InitHw()
    {
        seed.Configure();
        seed.Init(true);
        seed.SetAudioBlockSize(48);

        InitControls();
        InitCvOuts();
        InitGates();

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
        float value{};
        if (idx == SELECTOR_1 || idx == SELECTOR_2)
        {
            // Selectors use two controls, one for the up position (1) and one
            // for the down position (-1). When both are > 0.f, the switch is in
            // the center.
            float a = controls[idx + 1].Process();
            float b = controls[idx + 2].Process();
            if (a > kMinValueDelta && b > kMinValueDelta)
            {
                value = 0.f;
            }
            else if (a > kMinValueDelta)
            {
                value = -1.f;
            }
            else if (b > kMinValueDelta)
            {
                value = 1.f;
            }
        }
        else
        {
            value = controls[idx].Process();

            // Toggles only have two values.
            if (idx >= TOGGLE_1 && idx <= TOGGLE_4)
            {
                value = value > kMinValueDelta ? 1.f : 0.f;
            }
            // Buttons too, but inverted ('cause I soldered them to GND...).
            // Selectors are inverted in the up position.
            else if (idx >= BUTTON_1 && idx <= BUTTON_4)
            {
                value = value > kMinValueDelta ? 0.f : 1.f;
            }
        }

        return value;
    }

    void GateOut(uint8_t state)
    {
        dsy_gpio_write(&gateOut, state);
    }

    void CvOut(DacHandle::Channel channel, float value)
    {
        seed.dac.WriteValue(channel, static_cast<uint16_t>(fmap(value, 0, 4095)));
    }
}