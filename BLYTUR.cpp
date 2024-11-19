#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Definições dos pinos do display TFT
#define TFT_CS  D8
#define TFT_RST D3
#define TFT_DC  D4

// Instâncias dos sensores e do display
Adafruit_BMP280 bmp;
BH1750 lightMeter;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Variáveis globais para controle
float temperature, pressure, lux, voltage;
int displayIndex = 0; // Controle de qual valor está sendo exibido
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 2000; // Atualiza a cada 2 segundos

void setup() {
  Serial.begin(115200);
  
  initializeDisplay();
  initializeBMP280();
  initializeBH1750();
  initializeZMPT101B();

  // Mensagem inicial no display
  showWelcomeMessage();
}

void loop() {
  if (millis() - lastUpdateTime > updateInterval) {
    updateSensorValues();
    updateDisplay();
    lastUpdateTime = millis();
  }
}

// ---------------------------------
// Funções de Inicialização
// ---------------------------------

void initializeDisplay() {
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1);
}

void initializeBMP280() {
  if (!bmp.begin(0x76)) {
    Serial.println("Erro ao inicializar o BMP280!");
    while (1);
  }
}

void initializeBH1750() {
  if (!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23)) {
    Serial.println("Erro ao inicializar o BH1750!");
    while (1);
  }
}

void initializeZMPT101B() {
  // Configuração adicional, se necessária, para o ZMPT101B.
  // Aqui assumimos que o sensor está conectado ao pino A0 do ESP8266.
}

// ---------------------------------
// Funções de Atualização de Sensores
// ---------------------------------

void updateSensorValues() {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0F; // Conversão para hPa
  lux = lightMeter.readLightLevel();
  voltage = readVoltage();
}

float readVoltage() {
  int rawValue = analogRead(A0);
  return (rawValue / 1024.0) * 250.0; // Ajuste com base no divisor de tensão
}

// ---------------------------------
// Funções de Exibição no Display
// ---------------------------------

void showWelcomeMessage() {
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 30);
  tft.print("Inicializando...");
  delay(2000);
  tft.fillScreen(ST77XX_BLACK);
}

void updateDisplay() {
  tft.fillScreen(ST77XX_BLACK);

  switch (displayIndex) {
    case 0: showTemperature(); break;
    case 1: showPressure(); break;
    case 2: showLux(); break;
    case 3: showVoltage(); break;
  }

  // Alterna para o próximo valor
  displayIndex = (displayIndex + 1) % 4;
}

void showTemperature() {
  drawHeader("Temperatura");
  drawIconSun();
  drawValue(temperature, "C");
}

void showPressure() {
  drawHeader("Pressao");
  drawIconDrop();
  drawValue(pressure, "hPa");
}

void showLux() {
  drawHeader("Luz");
  drawIconLight();
  drawValue(lux, "lx");
}

void showVoltage() {
  drawHeader("Tensao");
  drawIconPlug();
  drawValue(voltage, "V");
}

// ---------------------------------
// Funções Auxiliares de Desenho
// ---------------------------------

void drawHeader(const char* title) {
  tft.fillRect(0, 0, 160, 20, ST77XX_BLUE);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(30, 5);
  tft.print(title);
}

void drawValue(float value, const char* unit) {
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.setCursor(20, 50);
  tft.print(value, 1);
  tft.print(" ");
  tft.print(unit);
}

void drawIconSun() {
  tft.fillCircle(30, 90, 10, ST77XX_YELLOW);
  for (int i = 0; i < 360; i += 45) {
    int x1 = 30 + cos(radians(i)) * 15;
    int y1 = 90 + sin(radians(i)) * 15;
    int x2 = 30 + cos(radians(i)) * 20;
    int y2 = 90 + sin(radians(i)) * 20;
    tft.drawLine(x1, y1, x2, y2, ST77XX_YELLOW);
  }
}

void drawIconDrop() {
  tft.fillTriangle(30, 70, 20, 90, 40, 90, ST77XX_CYAN);
}

void drawIconLight() {
  tft.fillRect(25, 80, 10, 20, ST77XX_YELLOW);
  tft.fillCircle(30, 75, 5, ST77XX_YELLOW);
}

void drawIconPlug() {
  tft.drawRect(25, 80, 10, 20, ST77XX_WHITE);
  tft.fillRect(27, 85, 3, 10, ST77XX_WHITE);
  tft.fillRect(30, 85, 3, 10, ST77XX_WHITE);
}
