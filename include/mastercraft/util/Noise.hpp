#ifndef MASTERCRAFT_NOISE_HPP
#define MASTERCRAFT_NOISE_HPP

#include <cstdint>
#include <type_traits>


namespace mastercraft::util {
    
    /**
     * Functor creating a fractal Brownian Motion (fBM) given noise function.
     *
     * fBm are amplitude and frequency modulated noise created by adding different iterations of noise (octaves),
     * where we successively increment the frequency in regular steps (lacunarity) and decrease the amplitude (gain).
     *
     * @tparam T         Input type of the noise function.
     * @tparam PRECISION Precision used to compute the noise, must be a floating point type.
     * @tparam NOISE     Function used to create the noise.
     */
    template<typename T, typename PRECISION, PRECISION (*NOISE)(const T &)>
    class Noise {
            static_assert(std::is_floating_point<PRECISION>::value, "Floating point type is required");
        
        private:
            const T seed;
            const uint8_t octaves;      /**< Number of iteration of the noise. */
            const PRECISION amplitude;  /**< Initial amplitude of the noise. */
            const PRECISION frequency;  /**< Initial frequency of the noise. */
            const PRECISION gain;       /**< Value the amplitude is multiplied each octave. */
            const PRECISION lacunarity; /**< Value the frequency is multiplied each octave. */
        
        public:
            Noise(T t_seed, uint8_t t_octaves, PRECISION t_amplitude, PRECISION t_frequency, PRECISION t_gain,
                  PRECISION t_lacunarity) :
                seed(t_seed), octaves(t_octaves), amplitude(t_amplitude), frequency(t_frequency), gain(t_gain),
                lacunarity(t_lacunarity) {
                
                assert(t_gain <= static_cast<PRECISION>(1.0) && "Gain must not be greater than 1.");
                assert(t_lacunarity >= static_cast<PRECISION>(1.0) && "Lacunarity must not be lesser than 1.");
            }
            
            
            PRECISION operator()(T x) {
                PRECISION value = 0.f;
                PRECISION freq = this->frequency;
                PRECISION ampl = this->amplitude;
                
                PRECISION totalAmp = ampl;
                
                for (int i = 0; i < octaves; i++) {
                    value += ampl * NOISE(freq * (x + seed));
                    ampl *= this->gain;
                    totalAmp += ampl;
                    freq *= this->lacunarity;
                }
                
                return value / totalAmp;
            }
            
            
            PRECISION operator()(T x, PRECISION oldMin, PRECISION oldMax, PRECISION newMin, PRECISION newMax) {
                PRECISION value = (*this)(x);
                
                PRECISION oldRange = (oldMax - oldMin);
                PRECISION newRange = (newMax - newMin);
                
                return (((value - oldMin) * newRange) / oldRange) + newMin;
            }
    };
}

#endif //MASTERCRAFT_NOISE_HPP
