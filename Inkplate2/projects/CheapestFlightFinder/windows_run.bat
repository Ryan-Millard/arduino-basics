arduino-cli compile --fqbn Inkplate_Boards:esp32:Inkplate2 -p COM3 --build-property "build.libraries=Inkplate,WiFi,HTTPClient,ArduinoJson" CheapestFlightFinder.ino
arduino-cli upload --fqbn Inkplate_Boards:esp32:Inkplate2 -p COM3 CheapestFlightFinder.ino
arduino-cli monitor -p COM3 --config 115200
