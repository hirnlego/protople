#pragma once

#include "tableosc.h"
#include "clkdelay.h"
#include "controltools.h"
#include "noisetools.h"

namespace protople
{
    using namespace hlstk;

    TableOsc osc;
    float oscBuffer[2048];

    ClkDelay delay;
    float delayBuffer[48000];

    Phasor phasor;
    float warp;

    Velvet noise;

    Swell swell;
    float rate;
}