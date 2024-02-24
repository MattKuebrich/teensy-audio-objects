# Ladder Lite

This is a more CPU-friendly version of the Teensy ladder filter which uses 2x oversampling (instead of 4x). It uses the changes Richard van Hoesel outlined [in this post on the PJRC forum](https://forum.pjrc.com/index.php?threads/porting-moog-ladder-filters-to-audio-objects.60488/post-272591) - all credit goes to him.

I'm using this ladder filter with the slow-ish [Adafruit ItsyBitsy M4 Express](https://www.adafruit.com/product/3800), which works with the [Adafruit fork of the Teensy Audio Library](https://github.com/adafruit/Audio). It could also be useful for the similarly spec'd Teensy 3.5.

The functions are the same as the [library version of the ladder filter](https://www.pjrc.com/teensy/gui/?info=AudioFilterLadder), aside from how you set the ``interpolationMethod()``. For that use ``LADDERLITE_FILTER_INTERPOLATION_FIR_POLY`` or ``LADDERLITE_FILTER_INTERPOLATION_LINEAR``. If CPU usage is critical, use the linear option. 

Note: The included sketch is written for the Adafruit ItsyBitsy M4 Express, but could be easily updated to work for Teensy. 
