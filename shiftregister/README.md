# Shift Register

This an 8-bit shift register with a 3-bit DAC output.  The example sketch shows how to implement a simple version of [https://modwiggler.com/forum/viewtopic.php?t=92049](Rob Hordijk's "Rungler").


## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Data Input |
| In 1  | Clock Input |
| Out 0  | Bit 0  |
| Out 1  | Bit 1  |
| Out 2  | Bit 2  |
| Out 3  | Bit 3  |
| Out 4  | Bit 4  |
| Out 5  | Bit 5  |
| Out 6  | Bit 6  |
| Out 7  | Bit 7  |
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


