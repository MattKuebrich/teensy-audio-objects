#include "bank_khepri.h"

// suppress warnings 
#pragma GCC diagnostic ignored "-Wparentheses"

uint32_t khepri1(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Arpeggiation
return (t >> (t / (t / (500 * p2) % 5 + 1) % (t / (1236 + p1) % 128 & ((t >> (p3 >> 5)) * 232))) >> (p1 >> 5)) + (t / (t >> ((p3 >> 5) & 12)) >> (t / (1236 + p1) % 128 & ((t >> (p3 >> 5)) * 232)));
}

uint32_t khepri2(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Landing Gear
return ((p1&t^(t>>2)%p2)&w+1393+p3);
}

uint32_t khepri3(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Alpha
return (((t^(p1>>3)-456)*(p2+1))/(((t>>(p3>>3))%14)+1))+(t*((182>>(t>>15)%16))&1);
}

uint32_t khepri4(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Omega
return (((t>>5)|(t<<((p3>>4)+1))>>4)*p1-(t/((1853>>(t>>(p2>>4))%15))&1)>>(t>>12)%6)>>4;
}

uint32_t khepri5(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Widerange
return (((p1^(t>>(p2>>3)))-(t>>(p3>>2))-t%(t&p2)));
}

uint32_t khepri6(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Toner
return ((t>>((t>>12)%(p3>>4)))+((p1|t)%p2))<<2;
}

uint32_t khepri7(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Defender
return ((w-482+(w^(3456-p1)))%(p2*t>>5&(1030-(p3<<2))));
}

uint32_t khepri8(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Exploratorium
return ((t%(p1+(t%p2)))^(t>>(p3>>5)))*2;
}

uint32_t khepri9(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Filtered Triangles
return ((t%(512-(t*351)+16))^((t>>(p1>>5))))*(2+(t>>14)%6)|((t*p2)&(t>>(p3>>5)));
}

uint32_t khepri10(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Vocalizer
return ((t%p1>>2)&p2)*(t>>(p3>>5));
}

uint32_t khepri11(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// A bit high-frequency, but keeper anyhow
return (t+w+p2/p1)%(p1|t+p3);
}

uint32_t khepri12(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Hooks
return (t&(p1+2))-(t/p2)/w/p3;
}

uint32_t khepri13(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Melodic
return ( t* (( t>>9| t>>p1 ) & p2)) & (p3+5);
}

uint32_t khepri14(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
//classic Downward Wiggle
return (t*9&t>>4|t*p1&t>>(5+ (p3>>4))|t*3&t/p2)-1;
}

uint32_t khepri15(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Digital Memory
return (p2>>((((p1%w)+w)>>t)^(t/p3))^(p2<<2)*p1)%((t>>(p3>>4))%p1*14-t);
}

uint32_t khepri16(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Modern
return (((t%4069)^p1+t)+(w/257)+(w/300%t)+(w/p2^t%65))%(p3*4);
}

uint32_t khepri17(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
//chewie
return (p1-(((p3+1)/t)^p1|t^922+p1))*(p3+1)/p1*((t+p2)>>p2%19);
}

uint32_t khepri18(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// The Smoker
return w^(t>>(p3>>4)) >> (t/6988*t%(p1+1))+(t<<t/(p2 * 4));
}

uint32_t khepri19(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Bit Tweaker
return ((t/339+p1)+t/(t/4334+p2&t))+t%p3+455;
}

uint32_t khepri20(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Wingless
return (t^p1)+p2&t-(w&t/p3)/3;
}

#pragma GCC diagnostic ignored "-Wparentheses"
