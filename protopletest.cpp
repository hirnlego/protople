#include "protople_hw.h"
#include "protople_ui.h"
#include "commons.h"

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

        leftOut = rightOut = noise.Process();
        reso.Process(leftOut, rightOut);

        OUT_L[i] = leftOut;
        OUT_R[i] = rightOut;
    }
}

int main(void)
{
    InitHw();


    reso.Init(GetAudioSampleRate(), (float *)resoBuffer, 48000);
    noise.Init();

    InitUi();

    StartAudio(AudioCallback);
    StartAdc();

    while (true) {}
}