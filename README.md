# DAS
Device Activity Signal

## Requirement
Need to control blink rate proportional to data rate.

### Power Up (before drive comes READY)
Blink ON for 0.5 seconds and OFF for 0.5 seconds.

### Read/Write Operations
Blink rate proportional to I/O rate but not exceeding 4 times per second, pulse width 125±25 milliseconds, nominal 45-55% duty cycle. During very low I/O rate or single commands, the minimum pulse width is 125±25 milliseconds.

### Secure Erase, Sanitize, Drive Self-Test
Blink 2 times per second, nominal 45-55% duty cycle.

### Drive Idle
OFF

## Solution
Update the blink rate every second. The blink rate is related to the data rate during last second.

Data Rate | Blink Rate
--------- | ----------
0         |  off
Non-media | 2 Hz
0-200 MB/s | 2.5 Hz
200-400 MB/s | 3 Hz
400+ MB/s | 4 Hz
