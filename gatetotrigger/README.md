# Gate to Trigger

Converts an incoming gate into a short trigger.

Disclaimer: This object works as intended, but as the Teensy Audio Library stands now, isn't _super_ useful, as no other objects really expect triggers. I could see using this if you were sending the trigger to an external drum machine that expected a trigger of a certain length.

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Gate Input  |
| Out 0  | Trigger Output  |


## Functions
### **threshold**(amount);
Sets the threshold the input gate needs to reach for a trigger to be generated. The default value is 0.2.

### **duration**(milliseconds);
Sets the duration of the trigger output. The default time is 1ms, which is a pretty standard trigger length.

### **edge**(mode);
Sets which edge of the incoming gate will generate a trigger. The default is AudioEffectGateToTrigger::START.

Supported edge modes:
* AudioEffectGateToTrigger::START
* AudioEffectGateToTrigger::END
* AudioEffectGateToTrigger::BOTH



