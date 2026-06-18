# espunix

![espunix_logo](assets/logo.png)

> **"A minimal Unix-like OS for ESP32-S3"** system designed for ESP32-S3 microcontrollers, built on a robust **dual-bus (SPI2 and SPI3)** architecture.
> 
## Preview
Here is how `espunix` looks and operates in real-time. Whether you are checking system status or managing files, everything is handled via your terminal:

```text
Starting espunix OS...
espunix v1.0 Ready
/ $ fastfetch
--- espunix ---
Kernel: v1.0
Uptime: 42s
RAM Free: 184KB
SD: 64MB
CPU: S3 Dual-Core
/ $ echo "hello world" > sa.txt
/ $ cat sa.txt
hello world
```
![preview](assets/preview.jpg)


a frame from developer!
## Features

- **Dual-Bus Architecture:** Independent and isolated SPI buses for the display and SD card to prevent hardware conflicts.
- **Unix-like Shell:** Full support for essential commands: `ls`, `cd`, `cat`, `touch`, `echo`.
- **Fastfetch:** Built-in system information tool to display uptime, RAM usage, and SD card status.
- **Non-blocking Console:** Optimized display driver to prevent system hangs during I/O operations.

## Hardware & Compatibility

### Supported Hardware
Currently, this repository is optimized for the following board:
- [ESP32-S3-N16R8](board/esp32-s3-n16r8.md)

### Porting to Other Boards
Hardware configurations vary significantly. If you are porting `espunix` to a different board (e.g., ESP32-EU, ESP32-C3), please create a new Markdown file and add it to the documentation. If you succeed, feel free to open a Pull Request!

> [!NOTE]
> If you port this project to another board, please submit your hardware documentation as a new `.md` file to help the community.


## TESTED Hardware (which i used)
![my esp](assets/esp32s3n16r8.jpg)
![my_display](assets/tft1.8inch.jpg)


> [!IMPORTANT]
> The SD card must be formatted as **FAT32**. Ensure the physical "LOCK" switch on your SD card adapter is in the unlocked position.

## Contributing

`espunix` is open to community contributions. To contribute:

1. Fork the repository.
2. Create a new feature branch.
3. Commit your changes and open a Pull Request (PR).

---
*Created by REDBITH!*
