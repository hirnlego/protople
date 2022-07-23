#pragma once

#include "effects/resonator2.h"
#include "noisetools.h"
#include "dev/sdram.h"

namespace protople
{
    using namespace hlstk;
    using namespace daisy;

    float DSY_SDRAM_BSS resoBuffer[2][3][48000];
    Resonator reso;
    Noise noise;
}