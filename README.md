# Don't Touch It!

Inspired by a funny video where a colleague asked about a mysterious breadboard, we've embarked on an adventure combining hardware and software to monitor my Kubernetes cluster.
![Screenshot 2024-10-09 at 15 35 46](https://github.com/user-attachments/assets/63dff54c-8176-4efa-9bce-1b4b0389b0d4)

## Overview

This project aims to display cluster metrics on an OLED screen connected to an ESP32S3 microcontroller. The data is fetched from a Node.js server that communicates with a Kubernetes cluster running on GKE.

## Setup

1. **Clone the repository:**
   ```
   git clone https://github.com/yourusername/dont-touch-it.git
   cd dont-touch-it
   cd fetch-gke-metrics-data

    Install dependencies: For the Node.js server:

npm install

Configure your environment variables (e.g., GKE Cluster Endpoint, Access Token).

Upload the code to your ESP32S3 using PlatformIO or Arduino IDE.

Run the Node.js server:

    npm start

VSCode + PlatformIO
- Create any helloworld project, and copy paste the src, make sure to update the platform.ini accordingly.

Components Used

    ESP32S3 Microcontroller - $5
    Breadboard - $1
    Resistors, Diodes, 3V LEDs - $5
    OLED Screen - $8
    Wires - as needed

Features

    Displays metrics from the Kubernetes cluster on an OLED screen.
    Utilizes the onboard LED on the ESP32S3 to indicate the status (red for danger, orange for warning).
    Fetches data from a Node.js server that collects metrics from GKE.

## Usage

Once the setup is complete, you can power your ESP32S3 and view the metrics displayed on the OLED screen. The LED will change color based on the current status of your cluster.
Screenshots & Memes

## Contributing

Feel free to fork the repository and submit pull requests. Any feedback or suggestions are welcome!
License
- None

I hope you enjoy this project as much as I enjoyed creating it! Don’t forget to check out my Medium post for more details and a deeper dive into my journey.
