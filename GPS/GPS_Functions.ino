unsigned long lastPrintTime_satellite = 0;
unsigned long lastPrintTime_location = 0;
unsigned long lastPrintTime_altitude = 0;

HardwareSerial Serial3 (PB11, PB10);

void setupGPS() {
  Serial1.begin(9600);
  Serial3.begin(115200);
}

void showGPSInformation() {
  
  while (Serial3.available()) {
    char c = Serial3.read();
    gps.encode(c);
    // Serial1.print(c);

    if (gps.satellites.isValid() && millis() - lastPrintTime_satellite >= 2000 && gps.satellites.value() != 0) {
      printSatellite();
      lastPrintTime_satellite = millis();
    } else if (millis() - lastPrintTime_satellite >= 10000) {
      Serial1.println("Satellite data not available.");
      lastPrintTime_satellite = millis();
    }

    if (gps.location.isValid() && millis() - lastPrintTime_location >= 2000) {
      printPosition();
      lastPrintTime_location = millis();
    } else if (millis() - lastPrintTime_location >= 10000) {
      Serial1.println("Location data not available.");
      lastPrintTime_location = millis();
    }

    if (gps.altitude.isValid() && millis() - lastPrintTime_altitude >= 2000) {
      printAltitude();
      lastPrintTime_altitude = millis();
    } else if (millis() - lastPrintTime_altitude >= 10000) {
      Serial1.println("Altitude data not available.");
      lastPrintTime_altitude = millis();
    }
  }
}

void printSatellite() {
  Serial1.print("Satellites: ");
  Serial1.println(gps.satellites.value());
  Serial1.print("HDOP (Horizontal Dilution of Precision): ");
  Serial1.println(gps.hdop.value() / 100.0);
}

void printPosition() {
  Serial1.print("Latitude: ");
  Serial1.print(gps.location.lat(), 6);
  Serial1.println(String(" ") + (gps.location.rawLat().negative ? "S" : "N"));
  Serial1.print("Longitude: ");
  Serial1.print(gps.location.lng(), 6);
  Serial1.println(String(" ") + (gps.location.rawLng().negative ? "W" : "E"));
}

void printAltitude() {
  Serial1.print("Altitude: ");
  Serial1.print(gps.altitude.meters(), 6);
  Serial1.println(" m");
}