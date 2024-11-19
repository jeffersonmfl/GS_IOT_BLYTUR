# Projeto: Monitoramento de Turbina Eólica
Este projeto utiliza um NodeMCU ESP8266 V3 para monitorar e exibir valores de sensores em um turbina eólica. O sistema mede tensão, temperatura, pressão atmosférica e luminosidade, apresentando os dados em uma interface gráfica ilustrada.

# 📋 Funcionalidades

- Medição de tensão com o sensor ZMPT101B.
- Medição de temperatura e pressão com o sensor BMP280.
- Medição de luminosidade com o sensor BH1750.
- Exibição dos dados no display TFT ST7735 com ícones representativos:
 - ☀️ Temperatura: Sol estilizado.
 - 🌊 Pressão: Gota de água.
 - 🔌 Tensão: Plugue elétrico.
 - 💡 Luminosidade: Lâmpada.

# 🛠️ Componentes Utilizados

# Hardware

1. NodeMCU ESP8266 V3
2. Display LCD TFT 1.8" (ST7735, resolução 128x160)
3. Sensor de Tensão ZMPT101B (0 a 250 V)
4. Sensor de Pressão e Temperatura BMP280
5. Sensor de Luminosidade BH1750 (GY-302)
6. Protoboard e Jumpers para conexão
7. Turbina eólica

# Software

1. Arduino IDE (versão mais recente)
2. IoT Cloud do Arduino (para o dashboard)

# Bibliotecas:

- Adafruit_GFX e Adafruit_ST7735 (para o display TFT)
- Adafruit_BMP280 (para o BMP280)
- BH1750 (para o sensor de luz)
- Wire (para comunicação I2C)

# ⚙️ Como Funciona

1. Leitura dos Sensores:

- A turbina gera tensão elétrica
- O BMP280 fornece a temperatura e a pressão atmosférica.
- O BH1750 mede a intensidade da luz em lux.
- O ZMPT101B mede a tensão elétrica da rede.

2. Exibição no Display:

- Os dados são exibidos sequencialmente no display a cada 2 segundos.
- Cada valor é acompanhado de um ícone ilustrativo.

3. Ciclo de Exibição:

- O sistema alterna automaticamente entre as medições de tensão, temperatura, pressão e luminosidade.

# 🚀 Configuração do Ambiente

1. Instale as Bibliotecas Necessárias:

- No Arduino IDE, vá até Sketch > Incluir Biblioteca > Gerenciar Bibliotecas e procure pelas bibliotecas abaixo:

 - Adafruit_GFX
 - Adafruit_ST7735
 - Adafruit_BMP280
 - BH1750

2. Configure o Arduino IDE:

- Instale o suporte à placa ESP8266:
  1. Abra o Gerenciador de Placas e adicione o URL no menu Preferências:

Copie o link abaixo:
* http://arduino.esp8266.com/stable/package_esp8266com_index.json

   2. Instale a placa ESP8266.


3. Carregue o Código:

* Conecte o NodeMCU ESP8266 ao computador.
* Configure a porta e selecione a placa NodeMCU 1.0 (ESP-12E Module).
* Faça o upload do código para a placa.

4. Conecte os Sensores:

* Siga o esquema de ligação abaixo para conectar os sensores e o display.

# 🔌 Esquema de Ligação

- https://github.com/jeffersonmfl/GS_IOT_BLYTUR/blob/main/Esquema%20de%20Liga%C3%A7%C3%A3o.png

# 📊 Interface Gráfica

A interface gráfica no display inclui:

* Títulos para identificar os sensores.
* Ícones representativos de cada medida.
* Valores atualizados a cada 2 segundos.


# Exemplo de Tela

* Temperatura:
Ícone do sol com valor em graus Celsius.

* Pressão:
Gota de água com valor em hPa.

* Luminosidade:
Lâmpada com valor em lux.

* Tensão:
Plugue com valor em volts.


# 🛠️ Possíveis Melhorias

* Adicionar Wi-Fi para enviar os dados para um servidor remoto.
* Incluir alertas visuais no display para valores fora da faixa ideal.
* Personalizar o tempo de atualização via interface web.

