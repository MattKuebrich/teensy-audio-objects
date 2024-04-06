# wav2int16 for Teensy
This Python script can be used to convert a single-cycle .wav file into a 256+1 sample int16_t array. The array can then be used in the Teensy Audio Library's [Waveform](https://www.pjrc.com/teensy/gui/?info=AudioSynthWaveform) and [WaveformModulated](https://www.pjrc.com/teensy/gui/?info=AudioSynthWaveformModulated) objects as an arbitrary waveform. The script should work with stereo .wav files and will automatically bandlimit and normalize them. I've included an example Teensy sketch and .wav file. 

## Similar scripts
Here are some similar scripts that might work better for your needs.  DatanoiseTV made a similar [Python script](https://github.com/DatanoiseTV/AKWF_WaveForms/tree/master/utils) (10 years ago!) and shaitanbaali recently made a [Mathematica script](https://github.com/shaitanbaali/TeensyAudioWaveformCollection/blob/main/tools/TeensyArbitraryWaveformConvertAKWF.nb). Both these projects focused on converting the Adventure Kid Waveforms (AKWF) for Teensy. If you're just looking for a TON of waveforms to use in your project, check those out!

## Requirements
This script requires the [soundfile](https://pypi.org/project/soundfile/), [numpy](https://numpy.org/) and [scipy](https://scipy.org/) Python libraries.

## Usage
To run the script, use:
``python3 wav2int16.py yourfile.wav``

Bandlimiting and normalization are on by default but you can disable them by using the ``--no-bandlimit`` and/or ``--no-normalize`` flags. 

The array will be printed to the terminal in a format like this (except with all 257 values!) that you can paste into your Teensy sketch:

``const int16_t yourfile[257] = {
-73, 410, 894, 1377, 1862, 2349, 2841, 3338, 3838, 4339, 4837, 5327, 5804, 6263 ...
};
``

Then you can apply it to your oscillator as a custom waveform like so:
``osc.arbitraryWaveform(yourfile, 1200);
``

See the included .ino file for a full example. 

## References
* https://github.com/DatanoiseTV/AKWF_WaveForms
* https://github.com/shaitanbaali/TeensyAudioWaveformCollection/tree/main
* https://forum.pjrc.com/index.php?threads/wav-to-arbitrary-waveform.64648/
* https://forum.pjrc.com/index.php?threads/arbitrary-waveform-object-issue.51677/
* https://forum.pjrc.com/index.php?threads/teensy-audio-waveform_arbitrary-example.28494/
* https://forum.pjrc.com/index.php?threads/how-to-make-wavetables.44057/
* https://forum.pjrc.com/index.php?threads/howto-convert-adventurekid-wav-samples-for-use-with-arbitrarywaveform.57766/
* https://udo-audio.zendesk.com/hc/en-gb/articles/360017735020-How-do-I-create-my-own-alternative-waveforms