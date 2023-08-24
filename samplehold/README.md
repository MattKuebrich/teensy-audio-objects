# Sample and hold
Each time this object is triggered (with a signal going low to high), the signal at the input will be sampled and held at that value until the next trigger. 

Based on code from John-Michael Reed (bleeplabs.com) from the [PJRC forum](https://forum.pjrc.com/threads/29227-Rate-Reduction-effect-for-audio-h-code-and-questions?p=78290&viewfull=1#post78290).

## Audio Connections

| Port  | Purpose |
| ----- | ------- |
| In 0  | Signal Input |
| In 1  | Trigger Input  |
| Out 0  | Sample and Hold Output  |

## Functions
There are no functions to call from the sketch. 
