# Quantizer

This quantizer is based on [Jeremy Wentworth's VCV Rack Quantizer](https://github.com/jeremywen/JW-Modules#quantizer). The user defines scales within the sketch. 

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Signal Input |
| Out 0  | Quantized Output  |


## Functions
### **scale**(array, length);
The scale you want to use an array, along with its length. The scale uses the "pitch class set" format. The numbers in the array represent the semitone intervals between each note of the scale. The array must global or static, otherwise it won't work. This is a float array, so you can use fractional semitones to get microtonal scales. 

You define the scale like this:
```
float major[7] = { 0, 2, 4, 5, 7, 9, 11 }; 
```

Then set it like this: 
``quantizer.scale(major, 7);``

### **octave**(int);
Shift the overall octave range up or down. Can go negative.



