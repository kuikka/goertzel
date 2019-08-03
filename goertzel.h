#pragma once
#include <math.h>
#include <iostream>

class Goertzel
{
public:
    Goertzel(float sampling_rate,
        float target_frequency,
        size_t block_size)
    {
        float N = block_size;
        int k = (int) (0.5 + ((N * target_frequency) / sampling_rate));
        float omega = (2.0f * M_PI * k) / N;
        sine = sin(omega);
        cosine = cos(omega);
        coeff = 2.0 * cosine;

        reset();

        std::cout << "Goertzel SR=" << sampling_rate << " N=" << block_size << " FREQ=" << target_frequency << "\n";
        std::cout << "k=" << k << " coeff=" << coeff << "\n";
    }

    void reset()
    {
        Q1 = Q1 = 0.0f;
    }

    void process_sample(float sample)
    {
        const float Q0 = coeff * Q1 - Q2 + sample;
        Q2 = Q1;
        Q1 = Q0;
    }

    void get_result(float *realPart, float *imagPart)
    {
        *realPart = (Q1 - Q2 * cosine);
        *imagPart = (Q2 * sine);
    }

    float get_magnitude_squared()
    {
        return Q1 * Q1 + Q2 * Q2 - Q1 * Q2 * coeff;
    }

private:
    float sine;
    float cosine;
    float coeff;
    float Q1;
    float Q2;
};
