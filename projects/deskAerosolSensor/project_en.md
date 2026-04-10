# Desktop Air Quality Monitor

This project turns an ***Cheap Yellow Display*** into a live indoor air quality 
dashboard using a SEN66 sensor and a color-coded 3x3 tile interface.
It continuously shows particulate matter (PM1.0, PM2.5, PM4.0, PM10), CO2, 
VOC index, NOx index, temperature, and humidity.

A clear startup flow handles connectivity, sensor warm-up, and status 
feedback directly on screen.
If no network is available, a captive WiFi portal allows configuration 
without reflashing.
When configured, measurements can be published as JSON messages to an MQTT 
broker at a chosen interval.
Time synchronization enables reliable timestamps for telemetry and diagnostics.

A simulation mode is included to validate dashboard behavior without physical 
sensor input.

The result is a practical, readable, and deployable desktop monitor for 
real-time environmental awareness.
