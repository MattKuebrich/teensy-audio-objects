#include "bank_sobek.h"

// suppress warnings 
#pragma GCC diagnostic ignored "-Wparentheses"

uint32_t sobek1(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// VAKoder - heavily modded MorphWiz patch
return(p2^((t>>((p1>>2)%20)))+t%(43+6*(t>>(p1%12)&3^1)))/2+p3;
}

uint32_t sobek2(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Membrane
return (t/((t+81+(p1<<4)|t)%((t*(p3+1))&(t|t)-(935+(p2<<2)))));
}

uint32_t sobek3(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Hannah
return ((t<<t+(t%(w>>2)-t+(p1>>4)))>>(p3>>10))+p2;
}

uint32_t sobek4(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Mobius Loop
return ((w&p1)|(69*p2)|(p3^t))+((w%(4333-p1))>>2);
}

uint32_t sobek5(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Kricket
return (((p1>>6)+1)^(t>>(p3>>14))/(w*((p2>>4)+1)));
}

uint32_t sobek6(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// lunar lander
return (t+5-p2*(t&p1))*t/t%(p3+556); 
}

uint32_t sobek7(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Foreground
return (t>>(p1>>4)>>t*((t>>5)%((186*p2)+1)))-p3;
}

uint32_t sobek8(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Pins and needles
return t*(869-p3)<<((t+(p2<<1)&65-t)%t)%p1;
}

uint32_t sobek9(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// odd scales
return (3-(((1063-p3)*(t>>3))%(254&p2)))|(3-((1063*(t>>2))%(254%p1)));
}

uint32_t sobek10(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Clickers
return (((570%((t>>2)%(1613+p1)))-((p2|(t>>2))>>(710-p2)))-1-p3);
}

uint32_t sobek11(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Tone Sweeper
return ((t&p2&t)*p1+(t>>(p3>>6)))>>1;
}

uint32_t sobek12(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Detunef
return ((t-p3)|t+(t+t%p1))-p2;
}

uint32_t sobek13(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Autodrums (p1, p2, and p3 control drum patterns)
return ((((int(sqrt(t%16384))<<5)&64) *(((p1<<1) >> ((t>>14)%8))&1))<<1) + // Sqrt Kick
(((random(25))*(( p2 >>((t>>10)%8))&1))&344) + // hat
((((random(18000)))>>7) * (( p3 >> ((t>>13)%8))&1)&422); // snare          
}

uint32_t sobek14(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Burst Thinking
return (1099991*t&t<<(p2-t%p1)+t)>>(p3>>6);
}

uint32_t sobek15(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Bit Futurist
return (((1317-p1)*t)|w/p2%t)>>(p3>>6);
}

uint32_t sobek16(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Tinbot
return (t/(40+p1)*(t+t|4-(p2+20)))+(t*(p3>>5));
}

#pragma GCC diagnostic ignored "-Wparentheses"
