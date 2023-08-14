// SOME HELPER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// floating point map function taken from https://forum.arduino.cc/index.php?topic=361046.0
double mapf(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//fscale for log response on frequency
//https://playground.arduino.cc/Main/Fscale/
float fscale( float originalMin, float originalMax, float newBegin, float
              newEnd, float inputValue, float curve) {

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;

  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin) {
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd;
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float


  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0) {
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  {
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange);
  }

  return rangedValue;
}

float fastTanh(float x) {
  //https://www.musicdsp.org/en/latest/Other/238-rational-tanh-approximation.html
  if ( x < -3 )
    return -1;
  else if ( x > 3 )
    return 1;
  else
    return x * ( 27 + x * x ) / ( 27 + 9 * x * x );
}

float clip(float sample) {
    if (sample < -1.f) {
        return -1.f;
    }
    else if (sample > 1.f) {
        return 1.f;
    }
    else {
        return sample;
    }
}

float fastAcosh(float val) {
  // https://github.com/heldervasc/Audio-DSP-Library/blob/7aed4e9845d335816cb17c617319ccd6a66f89ad/Utils/Utils.cpp
  return log(val + sqrt(val * val - 1));
}

float fastAtan(float x) {
  // https://nghiaho.com/?p=997
  return M_PI_4 * x - x * (fabsf(x) - 1) * (0.2447 + 0.0663 * fabsf(x));
}

float fastAtan2(float y, float x)
{
  float coeff_1 = PI / 4;
  float coeff_2 = 3 * coeff_1;
  float abs_y = fabs(y) + 1e-10;  // kludge to prevent division by zero

  float r, angle;

  if (x >= 0)
  {
    r = (x - abs_y) / (x + abs_y);
    angle = coeff_1 - coeff_1 * r;
  }
  else
  {
    r = (x + abs_y) / (abs_y - x);
    angle = coeff_2 - coeff_1 * r;
  }

  if (y < 0)
    return -angle;  // negate if in quadrant III or IV
  else
    return angle;
}

float fastSin(float x)  {
  if (M_PI < x) {
    x = x - static_cast<int>((x + M_PI) / (TWO_PI)) * TWO_PI;
  }
  else if (x < -M_PI) {
    x = x - static_cast<int>((x - M_PI) / (TWO_PI)) * TWO_PI;
  }

  return x * (1 - x * x * (0.16666667f - x * x * (0.00833333f - x * x * (0.0001984f - x * x * 0.0000027f))));
}

double fastPow(double a, double b) // martin.ankerl.com
{
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;
  return u.d;
}

float fastCos(float x)
// https://karmafx.net/docs/karmafx_floattricks.pdf
{
 const float x2 = x*x;
 const float x4 = x2*x*x;
 const float x6 = x4*x*x;
 return 1.0f - (x2 * 0.5f)
 + (x4 * 0.041666666666f)
 - (x6 * 0.00138888888888f);
}


float mod(float n, float d) {
  n = fmod(n, d);
  if (n < 0) n += d;
  return n;
}


//random float
float randomf(float min, float max) {
  if (min > max) {
    // Swap min and max
    float temp = min;
    min = max;
    max = temp;
  }
  float random = ((float) rand()) / (float) RAND_MAX;
  float range = max - min;
  return (random * range) + min;
}

int sgn(float x) {
  // return -1 if x is negative or +1 if xn is 0 or greater
  return (x > 0) - (x < 0);
}

//Based on JUCE jlimit (https://github.com/juce-framework/JUCE/blob/master/modules/juce_core/maths/juce_MathsFunctions.h)
float limit(float lowerLimit, float upperLimit, float valueToConstrain) {

  // avoid errors
  if (lowerLimit > upperLimit) {
    float temp = lowerLimit;
    lowerLimit = upperLimit;
    upperLimit = temp;
  }

  return valueToConstrain < lowerLimit ? lowerLimit : (upperLimit < valueToConstrain ? upperLimit : valueToConstrain);
}

// Linearly interpolates between `a` and `b`, from `p = 0` to `p = 1`.
// https://github.com/search?q=repo%3AVCVRack%2FRack%20crossfade&type=code
float crossfade(float a, float b, float p) {
  return a + (b - a) * p;
}
