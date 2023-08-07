#include "bank_drum.h"

// suppress warnings 
#pragma GCC diagnostic ignored "-Wparentheses"

uint32_t drum1(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Sqrt Kick
return (((int(sqrt(t % 16384)) << 5) & 64) << 1) * (t<16384); // Sqrt Kick  
}

uint32_t drum2(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Tech kick
return (((1250&t-17)>>6%t)*40) * (t<2000);   
}

uint32_t drum3(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Noise Hit 1
return ((50&t-177)>>356%t)*20 * (t<2000);  
}

uint32_t drum4(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// White noise snare drum
return (w+t+(w>>2))&874356 * (t<2000);    
}

uint32_t drum5(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// rolling hats
return (t<<t/2);
}

uint32_t drum6(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// zap kick
return ((1200/t)*150) * (t<2000);   
}

uint32_t drum7(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// hihat
return (3000-(3000%t))*(23/t)*(w+t) * (t<2000);
}

uint32_t drum8(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// tuned hat
return ((t^99)/(t>>4))<<1;
}

uint32_t drum9(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Simple pulse
return (t/(t>>9));
}

uint32_t drum10(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Noise snare
return ((520 - t%(t%w))/(t>>11));
}

uint32_t drum11(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// double noise snare
return ((800 - t%(t%w))/(t>>11));
}

uint32_t drum12(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// open snare
return ((890&t%(t%126))/(t>>7))<<3;
}

uint32_t drum13(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// metallic
return ((8999&t%(t&11))/(t>>8))<<6;
}

uint32_t drum14(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// vinal pop
return ((28959^(t>>2)%(t%230))/(t>>3))<<2;
}

#pragma GCC diagnostic ignored "-Wparentheses"
