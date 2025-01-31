arduino-cli compile --fqbn Inkplate_Boards:esp32:Inkplate2 -p COM3 --build-property "build.libraries=Inkplate,WiFi,HTTPClient" WiFi.ino
arduino-cli upload --fqbn Inkplate_Boards:esp32:Inkplate2 -p COM3 WiFi.ino
