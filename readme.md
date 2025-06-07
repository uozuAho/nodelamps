# Nodelamps

LED lamps powered by NodeMCU & Neopixels.

# Getting started, testing hardward
See [hardware](./hardware.md) and [hardware tests](./hardware_tests/) to get
started.

# Run lamp
- make the [hardware](./hardware.md)
- flash the hardware with [lamp](./lamp.ino)
- use your TV remote to turn LED brightness up/down

# Configure your remote control
- run [lamp](./lamp.ino) and look at the commands printed in the arduino serial
  monitor when you press your remote control buttons
- modify the IR_PROTOCOL, IR_CMD_UP etc. in [lamp](./lamp.ino) to suit your
  remote
