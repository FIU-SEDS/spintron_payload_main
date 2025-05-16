# 'Spintron' - IREC 2025 Payload -> Subsystem Main

The software is split into 2 parts a spin subsystem and a main subsystem. The main subsystem is responsible for collecting data from the spin subsystem and processing it. The spin subsystem is responsible for collecting data from the load cell and sending it to the main subsystem.

## Main Subsystem

1. Receives data from the spin subsystem via ESP Now.
2. Processes the data, and saves it to a CSV file on the SD card.
3. Determines when to start the activation of the subsystem based on the acceleration data.


The software is built and tested using the Ardiuno IDE on a ESP 32 S3 board.
