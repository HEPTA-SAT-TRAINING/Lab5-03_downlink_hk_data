#include "src/HeptaSat.h"

HeptaCdh cdh;
HeptaCom com;
HeptaEps eps;
HeptaSensor sensor;

void downlink_hk_data(void) {
  float temp = sensor.get_temperature();
  float vbat = eps.get_battery_voltage();
  float v5 = eps.get_5v_voltage();
  float v3v3 = eps.get_3v3_voltage();
  float sap = eps.get_sap_voltage();
  float idis = eps.get_current_discharge();
  float ichg = eps.get_current_charge();

  com.printf(
    "TEMP=%.2f,VBAT=%.3f,V5=%.3f,V3V3=%.3f,SAP=%.3f,IDIS=%.3f,ICHG=%.3f\n",
    temp, vbat, v5, v3v3, sap, idis, ichg);

  cdh.printf(
    "HK: TEMP=%.2f C, VBAT=%.3f V, V5=%.3f V, V3V3=%.3f V, SAP=%.3f V, IDIS=%.3f A, ICHG=%.3f A\n",
    temp, vbat, v5, v3v3, sap, idis, ichg);
}

void setup() {
  cdh.begin();
  cdh.wait_for_serial();

  eps.init();
  eps.switch_3V3_on();
  sensor.begin();

  com.begin(9600);

  cdh.println("XBee HK data downlink started (1 second interval)");
}

void loop() {
  if (com.available()) {
    char cmd = com.get_char();
    com.printf("command = %c\n", cmd);
    cdh.printf("command = %c\n", cmd);
  } else {
    downlink_hk_data();
  }

  delay(1000);
}
