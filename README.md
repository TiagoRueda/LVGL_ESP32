# Descrição:

Este repositório contém um código de exemplo que integra interface LVGL com um ESP32. O código demonstra como configurar uma tela LVGL em um painel LCD ILI9341 usando a interface SPI do ESP32 e manipular a entrada do usuário por meio de botões ou pela interface web. O servidor web usa html/css simples, sendo possível controlar remotamente via HTTP. Você pode acessar a interface da web conectando-se ao endereço IP do ESP32.

# Observação:

Verifique se a configuração do SPI corresponde à configuração do hardware.

Este projeto utiliza o componente `esp_lcd_ili9341` do repositório de componentes da Espressif:

```bash
idf.py add-dependency "espressif/esp_lcd_ili9341^2.0.0"
```
Você também pode declarar isso diretamente no seu componente com um arquivo `idf_component.yml` assim:

```yaml
dependencies:
  espressif/esp_lcd_ili9341: "^2.0.0"
```