# Dust

This object generates randomly spaced impulses with random amplitudes. 

This was adapted from Michael Hetrick's [Dust VCV Rack module] (https://github.com/mhetrick/hetrickcv/blob/master/src/Dust.cpp), which was based on the [Dust UGen in Supercollider](https://doc.sccode.org/Classes/Dust.html).

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Density Modulation  |
| Out 0  | Dust Output  |


## Functions
### **density**(amount);
Set the density amount, from 0.0 to 1.0.

### **enableUnipolar**(bool);
This changes the dust output from bipolar (the default) to unipolar. 

