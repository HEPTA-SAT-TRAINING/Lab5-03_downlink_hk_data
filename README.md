# Lab5-03: Downlink HK Data

Firmware that downlinks housekeeping (HK) telemetry every second over XBee COM.

## Web Serial Monitor

Open in **Chrome or Edge**, then **Add Port** → **Connect** (38400 baud):

**https://hepta-sat-training.github.io/hepta-serial-viewer/**

HK lines such as `TEMP=...,VBAT=...,V5=...` appear in the output pane every second. You can also send uplink commands from the input bar.

## Firmware

Open `Lab5-03_downlink_hk_data.ino` in the Arduino IDE and upload to your board. For library and submodule setup, see [src/README.md](src/README.md).
