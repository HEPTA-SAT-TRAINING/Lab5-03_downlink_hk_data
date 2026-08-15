#include "src/HeptaSat.h"

HeptaCdh cdh;
HeptaCom com;
HeptaEps eps;
HeptaSensor sensor;

void downlink_hk_data(void) {
  float temp = sensor.get_temperature();
  float bus_voltage = eps.get_bus_voltage();
  float v5 = eps.get_5v_voltage();
  float v3v3 = eps.get_3v3_voltage();
  float sap = eps.get_sap_voltage();
  float isol = eps.get_current_solar();
  float ibus = eps.get_current_bus();
  float ichg = eps.get_current_charge();

  com.printf(
    "TEMP=%.2f,BUS=%.3f,V5=%.3f,V3V3=%.3f,SAP=%.3f,ISOL=%.3f,IBUS=%.3f,ICHG=%.3f\r\n",
    temp, bus_voltage, v5, v3v3, sap, isol, ibus, ichg);

  cdh.printf(
    "HK: TEMP=%.2f C, BUS=%.3f V, V5=%.3f V, V3V3=%.3f V, SAP=%.3f V, ISOL=%.3f A, IBUS=%.3f A, ICHG=%.3f A\r\n",
    temp, bus_voltage, v5, v3v3, sap, isol, ibus, ichg);
}

void setup() {
  cdh.begin();
  eps.init();
  eps.switch_3V3_on();
  sensor.begin();

  com.begin();

  cdh.println("XBee HK data downlink started (1 second interval)");
}

void loop() {
  if (com.available()) {
    char cmd = com.get_char();
    com.printf("command = %c\r\n", cmd);
    cdh.printf("command = %c\r\n", cmd);
  } else {
    downlink_hk_data();
  }

  delay(1000);
}
