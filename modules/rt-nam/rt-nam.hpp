#pragma once

#include "wavenet_model.hpp"

namespace wavenet
{

struct NAMMathsProvider
{
#if RTNEURAL_USE_EIGEN
    template <typename Matrix>
    static auto tanh (const Matrix& x) 
    {
        // See: math_approx::tanh<3>
        const auto x_poly = x.array() * (1.0f + 0.183428244899f * x.array().square());
        return x_poly.array() * (x_poly.array().square() + 1.0f).array().rsqrt();
        //return x.array().tanh(); 
        // Tried using Eigen's built in tanh(), also works, failed on the same larger models as above custom tanh
    }
#elif RTNEURAL_USE_XSIMD
    template <typename T>
    static T tanh (const T& x) 
    {
        return math_approx::tanh<3> (x);
    }
#endif
};

/**
 * @brief Implements a NAM Wavenet model using RTNeural.
 * @note Only supports compile-time API for now.
 */
template <unsigned int channels, unsigned int samplesPerBuffer, typename Layer1, typename Layer2>
struct RTWavenet 
{
    wavenet::Wavenet_Model<float, channels, Layer1, Layer2> model;

    void loadModel(std::vector<float> weights) 
    {
        this->model.load_weights(weights);
        this->model.prepare(samplesPerBuffer); // prepare the model for N samples
        this->model.prewarm(); // pre-warm the model
    }
};

} // namespace wavenet