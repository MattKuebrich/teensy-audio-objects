# Comparator
This comparator has 2 inputs and compares them with different operations. It outputs a HIGH value if the operation is true, otherwise it outputs a LOW value. To set a specific threshold level, the DC audio object can be connected to one of the inputs.

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Signal Input A  |
| In 1  | Signal Input B  |
| Out 0  | Compared Output  |

## Functions
### **mode**(mode);


Supported modes:
* LESS
* GREATER
* EQUAL
* NOT_EQUAL

