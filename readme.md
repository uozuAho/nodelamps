# Nodelamps

LED lamps powered by NodeMCU & Neopixels.

# Getting started, testing hardware
See [hardware](./hardware.md) and [hardware tests](./hardware_tests/) to get
started.

# Run lamp
- make hardware TODO: what's the final hardware version?
- configure values at the top of [lamp](./lamp.ino)
- flash the hardware with [lamp](./lamp.ino)
- use your TV remote to turn LED brightness up/down
- use HTTP to set LED values, eg. `curl 'http://nodelamp.local/led?r=10&g=0&b=0'`

# Configure your remote control
- run [lamp](./lamp.ino) and look at the commands printed in the arduino serial
  monitor when you press your remote control buttons
- modify the IR_PROTOCOL, IR_CMD_UP etc. in [lamp](./lamp.ino) to suit your
  remote
