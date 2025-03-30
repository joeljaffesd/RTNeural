# RTNeural (with experimental NAM support)

As the above title suggests, this repo's purpose is to experiment with adding [NAM](https://www.neuralampmodeler.com/) support to [RTNeural](https://github.com/jatinchowdhury18/RTNeural).

The major code infrastructure can be found in [`modules/rt-nam`](./modules/rt-nam). It's mostly from the [RTNeural-NAM repo](https://github.com/jatinchowdhury18/RTNeural-NAM), with some edits from [GuitarML](https://github.com/guitarml) and myself.

Currently, only a compile-time API is supported. See the below example.

## USING
```cpp
#include "model.h" // Generated with `nam_to_header.py`

// example declaration and use in an app
class MyAudioApp {
  ModelWeights weights;
  unsigned int ioChannels = 1, samplesPerBuffer = 1;
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