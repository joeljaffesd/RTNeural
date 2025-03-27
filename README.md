# RTNeural (with experimental NAM support)

As the above title suggests, this repo's purpose is to experiment with adding [NAM](https://www.neuralampmodeler.com/) support to [RTNeural](https://github.com/jatinchowdhury18/RTNeural).

The major code infrastructure can be found in [`modules/rt-nam`](./modules/rt-nam). It's mostly from the [RTNeural-NAM repo](https://github.com/jatinchowdhury18/RTNeural-NAM), with some edits from [GuitarML](https://github.com/guitarml) and myself.

Currently, only a compile-time API is supported. See the below example.

## USING
```cpp
#include <RTNeural/RTNeural.h>
#include <RtNeural/modules/rt-nam/rt-nam.hpp>

// wavenet layer arrays generated from a .nam file
using Layer1 =
wavenet::Layer_Array<float, 
                     1, // input_size
                     1, // condition_size
                     2, // head_size
                     2, // channels
                     3, // kernel_size
                     wavenet::Dilations<1, 2, 4, 8, 16, 32, 64>, // dilations
                     false, // head_bias
                     wavenet::NAMMathsProvider>; // maths provider

using Layer2 = 
wavenet::Layer_Array<float, 
                     2, // input_size
                     1, // condition_size
                     1, // head_size
                     2, // channels
                     3, // kernel_size
                     wavenet::Dilations<128, 256, 512, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512>, // dilations
                     true, // head_bias
                     wavenet::NAMMathsProvider>; // maths provider

// weights generated from a .nam file
struct ModelWeights {
  std::vector<float> weights = { ... };
};

// example declaration and use in an app
class MyAudioApp {
  ModelWeights weights;
  ioChannels = 1;
  samplesPerBuffer = 1;
  wavenet::RTWavenet<ioChannels, 
                     samplesPerBuffer, 
                     Layer1, 
                     Layer2> 
    model;

  float myAudioCallback(float inputSample) {
    return model.model.forward(inputSample);
  }
};
```

## TODO
- Runtime (dynamic) API
- Python script for parsing NAM files
- Let me know what else.