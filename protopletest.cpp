#include "protople_hw.h"
#include "protople_ui.h"
#include "protopletest.h"
#include <cstring>

using namespace protople;
using namespace daisysp;


void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    //ProcessControls();
    ProcessUi();

    for (size_t i = 0; i < size; i++)
    {
        float leftIn{IN_L[i]};
        float rightIn{IN_R[i]};

        float leftOut{};
        float rightOut{};

        leftOut = rightOut = osc.Process();

        OUT_L[i] = leftOut;
        OUT_R[i] = rightOut;
    }
}

int main(void)
{
    InitHw();

    osc.Init(GetAudioSampleRate());
    osc.SetFreq(220);
    osc.SetWaveform(Oscillator::WAVE_SIN);

    InitUi();

    StartAudio(AudioCallback);
    StartAdc();

    while (true) {}
}