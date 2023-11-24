// PARAMETER VARIABLES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float paramMin = 0.0; //set min for the distortion parameters
float paramMax = 1.0; //set max for the distortion parameters


// WAVESHAPER functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fast approximations of some C++ math functions have been used to speed things up. Those are in the helperfunctions.ino file.

float function1(float x, float r, float a, float b, float c) {
  //clean pass-through
  return (x);
}

float function2(float x, float r, float a, float b, float c) {
  //hyperbolic tangent soft clipping
  return fastTanh(x);
}

float function3(float x, float r, float a, float b, float c) {
  //foldback distortion (https://www.musicdsp.org/en/latest/Effects/203-fold-back-distortion.html)
  float threshold = mapf(a, paramMin, paramMax, 0.01, 0.08); //scale down parameter a to work well
  if (x > threshold || x < -threshold)
  {
    x = fabs(fabs(fmod(x - threshold, threshold * 4)) - threshold * 2) - threshold;
  }
  return x;
}


float function4(float x, float r, float a, float b, float c) {
  //Splatty
  return (x >= 1.0) ? sin(tanh(acosh(x))) : 0.0; 
}

float function5(float x, float r, float a, float b, float c) {
  return fastSin(x) * min(1, fabs(x));
}

float function6(float x, float r, float a, float b, float c) {
  return fastSin(fastTanh((fastCos(x))));
}

float function7(float x, float r, float a, float b, float c) {
  //Smooth distortion https://dsp.stackexchange.com/questions/13142/digital-distortion-effect-algorithm
  return (x > 0 ? 1 - exp(-x) : -1 + exp(x));
}

float function8(float x, float r, float a, float b, float c) {
  // a and b control soft / hard clipping
  // https://www.youtube.com/watch?v=4khNxfDcjg0
  //return limit(-0.8f, 0.8f, x * xGax); //soft-clipping
  //return limit(-0.3f, 0.3f, x * xGax); //hard-clipping
  a = mapf(a, paramMin, paramMax, -1.0, 1.0); //adjust to -1.0 to 1.0 for adjustable clipping
  b = mapf(b, paramMin, paramMax, -1.0, 1.0);
  return limit(a, b, x); //adjustable clipping
}

float function9(float x, float r, float a, float b, float c) {
  //Gross fuzz using r
  float fuzz = mapf(a, paramMin, paramMax, 0.75, 0.99); 
  return min(r, x) * fuzz;
}

float function10(float x, float r, float a, float b, float c) {
  //Wiggly Fuzz
  //http://rs-met.com/freebies.html
  a = mapf(a, paramMin, paramMax, 0.0, 1.0);
  b = mapf(b, paramMin, paramMax, 0.0, 10.0);
  return x+a*fastSin(2*PI*b*x);
}

float function11(float x, float r, float a, float b, float c) {
  //Wavefolding
  float a2 = 0.05;
  return fabs(fmod(x, a2) - 0.5 * a2) - 0.25 * a2;
}

float function12(float x, float r, float a, float b, float c) {
  //Bitcrusher
  float reduction_factor = mapf(a, paramMin, paramMax, 0.5, 8.0);
  float z = fastPow(2.0f, reduction_factor);
  return (1.0f / 0.5 * z) * (int)((x) * 0.5 * z);

}

float function13(float x, float r, float a, float b, float c) {
  //Chebyshev, has control over harmonics with a, b and c
  //https://github.com/colonelwatch/teensy-harmonic-distortion/blob/master/teensy-harmonic-distortion/teensy-harmonic-distortion.ino

  float output = 0.0;
  float y = limit(-1, 1, x);
  int MAX_ORDER = 4;
  a = mapf(a, paramMin, paramMax, 0.0, 1.0); //scale down parameter a to be in the sweet spot
  b = mapf(b, paramMin, paramMax, 0.0, 1.0); //scale down parameter a to be in the sweet spot
  c = mapf(c, paramMin, paramMax, 0.0, 1.0); //scale down parameter a to be in the sweet spot

  float alpha[MAX_ORDER - 1] = {a, b, c}; // First entry is second-order
  float cheby_poly_0 = 1.0;
  float cheby_poly_1 = y;

  output = cheby_poly_1;

  for (int k = 2; k <= MAX_ORDER; k++) {
    float next_cheby_poly = 2.0 * y * cheby_poly_1 - cheby_poly_0;
    output += alpha[k - 2] * next_cheby_poly;

    cheby_poly_0 = cheby_poly_1;
    cheby_poly_1 = next_cheby_poly;
  }

  return output;
}

float function14(float x, float r, float a, float b, float c) {
  //Nasty symmetrical 'non-limiting' distortion: (based on asinh)
  //https://www.kvraudio.com/forum/viewtopic.php?p=4914150&sid=6185438ec59a4a909dda0f24ee00e00c#p4914150
  return (log(x + sqrt(x * x) + 1)) * 0.5;
}

float function15(float x, float r, float a, float b, float c) {
  //Mojo
  //https://github.com/airwindows/airwindows/blob/master/plugins/MacVST/Distortion/source/DistortionProc.cpp
  float output = 0.0;
  double mojo = fastPow(fmax(x, -x), 0.25);
  if (mojo > 0.0) output = (fastSin(x * mojo * M_PI * 0.5) / mojo) * 0.987654321;
  return output;
}

float function16(float x, float r, float a, float b, float c) {
  //Dyno
  //https://github.com/airwindows/airwindows/blob/master/plugins/MacVST/Distortion/source/DistortionProc.cpp
  float output = 0.0;
  double dyno = fastPow(fmax(x, -x), 4);
  if (dyno > 0.0) output = (fastSin(x * dyno) / dyno) * 1.1654321;
  return output; 
}

float function17(float x, float r, float a, float b, float c) {
  //Asymmetric waveshaper taken from Doidic/Line 6 patent (functions in Pakarinen & Yeh 2009)
  //https://github.com/jcugnoni/TeensyDist/blob/master/Library/TeensyDistLib/TD_waveshaper.cpp
  float out;
  float xb = limit(-1.0, 1.0, x + a);

  float x2 = xb * xb;
  float x3 = xb * x2;
  if (xb < -0.08905) {
    out = -3. / 4.*(1 - fastPow(1 - (fabs(xb) - 0.032847), 12) + 1. / 3.*(fabs(xb) - 0.032847)) + 0.01;
  } else if (xb < 0.320018) {
    out = -6.153 * x3 + 3.9375 * xb;
  } else {
    out = 0.630035;
  }
  return out;
}

float function18(float x, float r, float a, float b, float c) {
  //Square waveshaper
  //https://www.youtube.com/watch?v=oIChUOV_0w4
  return (x >= 0 ? 1.f : -1.f) / 2.5; //reduced gax a bit cause it's really loud!
}

float function19(float x, float r, float a, float b, float c) {
  //111c algo from True Iron
  return fastTanh(1 * x) + fabs(fastTanh(0.1 * x)) / 30;
}

float function20(float x, float r, float a, float b, float c) {
  //Omega-N, a = intensity, b = mix
  //https://www.reddit.com/r/audioengxeerxg/comments/1345uvs/i_reverse_engxeered_the_kush_omegan_saturation/
  float Av = mapf(a, paramMin, paramMax, 1.0, 50.0); //scale down parameter a to be x the sweet spot
  return ((x + b) * fastTanh(Av * x));
}
