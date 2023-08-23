# Shift Register

This an 8-bit shift register with a 3-bit DAC output. The example sketch is similar to Rob Hordijk's Benjolin, without the filter. It uses the shift register object to implement the ["Rungler"](https://modwiggler.com/forum/viewtopic.php?t=92049).


## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Data Input |
| In 1  | Clock Input |
| Out 0  | Bit 0 Output  |
| Out 1  | Bit 1 Output  |
| Out 2  | Bit 2 Output  |
| Out 3  | Bit 3 Output  |
| Out 4  | Bit 4 Output  |
| Out 5  | Bit 5 Output  |
| Out 6  | Bit 6 Output  |
| Out 7  | Bit 7 Output  |
| Out 8  | 3-bit DAC (Rungler) Output  |

## Functions

### **loopEnable**(bool);
When this is enabled, the last bit of the shift register will be fed back into the first bit, looping them. 
Default is 0 (disabled).

### **xorEnable**(bool);
This XORs the input of the shift register with the last stage of the shift register, as in the Benjolin's rungler. I'm not sure if this is working correctly, but you can sometimes hear a difference. Default is 0 (disabled).

### **readBit0**();
### **readBit1**();
### **readBit2**();
### **readBit3**();
### **readBit4**();
### **readBit5**();
### **readBit6**();
### **readBit7**();
### **readBit8**();

These read a specific bit back to the sketch. Not sure how useful this is. I had used to make a "visual" shift register on an OLED display. I suppose I could have also used my readout object for that.


