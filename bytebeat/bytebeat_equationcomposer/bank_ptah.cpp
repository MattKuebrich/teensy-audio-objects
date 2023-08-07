#include "bank_ptah.h"

// suppress warnings 
#pragma GCC diagnostic ignored "-Wparentheses"

uint32_t ptah1(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Buildup
return (((t/(p3+1)*t)%p1)&(t-t/p2*632)); 
}

uint32_t ptah2(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Silent treatment
return t-t+t*p1|t&(p3+1)|t/p2;   
}

uint32_t ptah3(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Ryg's musical one-liner (with variations) - keeper, not good for looper though
return ((t*("363646292929289"[t>>13&14]&15))/p1&p2)+(((((t>>12)^(t>>12)-2)%11*t)/4|t&(t%(p3 * 100)))&63); 
}

uint32_t ptah4(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// The Signs
return ((0&(251&(t/(100+p1))))|((w/t|(t/(100*(p2+1))))*(t|p3)));
}
 
uint32_t ptah5(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Degraded Thumper
return (t*(p1/(t%+10))&t>>(p3>>4))&((t*(p1>>5))&t>>(p2>>5))|(t>>4&p2);
}

uint32_t ptah6(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// BitWiz Transplant
return (t-((t&p1)*p2-1668899)*((t>>15)%15*t))>>((t>>12)%16)>>(p3%15);
}

uint32_t ptah7(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Derived Grit
return (w|((t>>2)+6)+t%(p1<<3))/(((p2<<3)+1)/(p1+1))+p3;
}

uint32_t ptah8(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Screetchy
return (t*((t>>(p1%16)|p2>>9)&63-p3&t>>4))>>((t>>12)%15);
}
uint32_t ptah9(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Arp Rotator
return ((t>>(p1>>4))&(t<<3)/(t*p2*(t>>11)%(3+((t>>(16-(p3>>4)))%22))));
}

uint32_t ptah10(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Question / Answer
return ((t*(t>>8|t>>p3)&p2&t>>8))^(t&t>>p1|t>>6);
}

uint32_t ptah11(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Magnified
return (p1&t%p3)^(t/p2);
}

uint32_t ptah12(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Triangle Wiggler
return (t*(4|7&t>>13)>>((~t>>p1)&1)&p3) + ((t)*(t>>11&t>>13)*((~t>>9)&3)&p2);
}

uint32_t ptah13(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Triangle Wiggler 2
return ((t>>(p1>>4))|t|t>>6)*p3+4*(t&(t>>(p2>>4))|t>>(p1>>4));
}

uint32_t ptah14(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// GGT2
return ((p1|(t>>(t>>13)%14))*((t>>(p1%12))-p2&249))>>((t>>13)%6)>>((p3>>4)%12);
}

uint32_t ptah15(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Abducted
return (p1+t>>p2%12)|((w%(p1+t>>p1%4))+11+p3^t)>>(p3>>12);
}

uint32_t ptah16(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// My quiet friend
return (((t>>((p1>>12)%12))%(t>>((p2%12)+1))%(t>>((t>>(p3%10))%12)))/((t>>((p2>>2)%15))%15))<<2;
}

uint32_t ptah17(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// My loud friend
return (((t>>((p1>>12)%12))%(t>>((p2%12)+1))-(t>>((t>>(p3%10))%12)))/((t>>((p1>>2)%15))%15))<<4;
}

uint32_t ptah18(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Light reactor
return ((t>>3)*(p1-643|(325%t|p2)&t)-((t>>6)*35/p3%t))>>6;
}

uint32_t ptah19(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Timing master
return (((t>>(t>>(p2%15))%16)/((t>>((t>>(p3%15))%15))%12)+p1)*((t>>(p1%12))+15))<<4;
}

uint32_t ptah20(uint32_t t, uint8_t w, uint32_t p1, uint32_t p2, uint32_t p3) {
// Pulse click beat - from MorphWiz, modified by Bret
return ((t*((50*p1)/(t%20011))&t>>(p1>>12))-((t*3)&t>>((p3>>5)%255))|(t>>4&(255-p2)));
}

#pragma GCC diagnostic ignored "-Wparentheses"


  






 
 


 

 




  
  
