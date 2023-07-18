# Gate to Trigger

Converts an incoming gate into a short trigger. 

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Gate Input  |
| Out 0  | Trigger Output  |


## Functions
### **threshold**(amount);
Sets the threshold the input gate needs to reach for a trigger to be generated. The default value is 0.2.

### **duration**(milliseconds);
Sets the duration of the trigger output. The default time is 1ms.

### **edge**(mode);
Sets which edge of the incoming gate will generate a trigger. The default is START.

Supported edge modes:
* START
* END
* BOTH

