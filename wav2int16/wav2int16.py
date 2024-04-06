# wav2int16

# This converts a .wav file into a 256+1 sample int16_t array. 
# It can be used in the Teensy Audio Library's WaveformModulated object as an arbitrary waveform.

# To run, in Terminal run (for example):
# python3 wav2int16.py analogsine.wav

# Bandlimiting and normalization are on by default but you can disable them by using the --no-bandlimit and/or --no-normalize flags.

# References:
# https://forum.pjrc.com/index.php?threads/wav-to-arbitrary-waveform.64648/
# https://forum.pjrc.com/index.php?threads/arbitrary-waveform-object-issue.51677/
# https://forum.pjrc.com/index.php?threads/teensy-audio-waveform_arbitrary-example.28494/
# https://github.com/DatanoiseTV/AKWF_WaveForms/tree/master
# https://forum.pjrc.com/index.php?threads/how-to-make-wavetables.44057/

import soundfile as sf
import numpy as np
from scipy import signal
import os
import sys
import argparse

def wav_to_int16_array(file_path, cutoff_frequency=5000, apply_bandlimiting=True, apply_normalization=True):
    # Read audio data using soundfile
    data, sample_rate = sf.read(file_path)

    if data.ndim > 1:
        # Stereo file
        left_channel = data[:,0] 
    else:
        # Mono file
        left_channel = data

    # Resample to 256 samples
    resampled_array = signal.resample(left_channel, 256)

    # Peak normalization
    if apply_normalization:
        resampled_array_normalized = resampled_array / np.max(np.abs(resampled_array))
    else:
        resampled_array_normalized = resampled_array

    # Convert normalized array to 16-bit integers
    resampled_ints = (resampled_array_normalized * 32767).astype(np.int16)

    if apply_bandlimiting:
        # Low-pass Butterworth filter
        nyquist_frequency = sample_rate / 2
        normalized_cutoff = cutoff_frequency / nyquist_frequency
        order = 4  # Increasing the order will make the filter steeper
        normalized_coeffs = signal.butter(order, normalized_cutoff, btype='lowpass', analog=False)

        # Apply the filter to the resampled data
        bandlimited_array = signal.filtfilt(normalized_coeffs[0], normalized_coeffs[1], resampled_ints)
    else:
        bandlimited_array = resampled_ints

    # Convert bandlimited data to 16-bit integers
    bandlimited_ints = bandlimited_array.astype(np.int16)

    return bandlimited_ints, sample_rate

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert a WAV file to an int16_t array.")
    parser.add_argument("wave_file_path", help="Path to the wave file")
    parser.add_argument("--no-bandlimit", action="store_false", dest="apply_bandlimiting", help="Disable bandlimiting (low-pass filter)")
    parser.add_argument("--no-normalize", action="store_false", dest="apply_normalization", help="Disable normalization")
    args = parser.parse_args()

    bandlimited_ints, sample_rate = wav_to_int16_array(args.wave_file_path, cutoff_frequency=5000, apply_bandlimiting=args.apply_bandlimiting, apply_normalization=args.apply_normalization)

    # Get the filename without the extension and remove spaces
    filename, _ = os.path.splitext(os.path.basename(args.wave_file_path))
    filename = filename.replace(" ", "")

    # Print a newline before the array
    print()

    print(f"const int16_t {filename}[257] = {{")
    
    # Duplicate first array value for the 257th
    print(', '.join(str(val) for val in bandlimited_ints) + f', {bandlimited_ints[0]}')
    print('};')

    # Print a newline after the array
    print()

    # print(f"Sample Rate: {sample_rate} Hz")