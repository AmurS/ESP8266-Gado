# ESP8266 with Grafana and InfluxDB

The ghetto way to setup an IoT for your glorious Grafana Dashboard.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

## Prerequisites

Ingredients :

```
1. ESP8266
2. BM180 Barometer 
3. DHT11 or DHT22 Temperature and Humidity sensor 
3. 10k Resistors for pull up DHT
4. 100nF Capacitors 
5. 3.3V LDO regulator to supply your ESP
6. Proto board, scrap PCB, or wire to connect everything

```
## ESP8266

### Schematic
Using ESP8266 NodeMCU v3 LoLin with a simple 3.3V LDO Regulator.

![Schematic with battery](https://i.imgur.com/jvp7zIF.png)

GPIO used on ESP8266 NodeMCU v3:
```
BMP180 I2C_SCL on D1 or GPIO 5  
BMP180 I2C_SDA on D2 or GPIO 4
DHT1 I/O on D4 or GPIO 2
```

### Place Holder

Using two different sensor to get a single data.


### Flashing ESP8266

Place Holder
```
Place Holder
```

Place Holder

## MQTT Broker
### Manual Install
Install Mosquitto to your ubuntu server.
```
sudo apt-get update
sudo apt install mosquitto mosquitto-clients
```

Configure your /etc/mosquitto/mosquitto.conf
```
# /etc/mosquitto/mosquitto.conf

pid_file /var/run/mosquitto.pid
log_dest file /var/log/mosquitto/mosquitto.log
include_dir /etc/mosquitto/conf.d
persistence true
persistence_location /var/lib/mosquitto/
allow_anonymous false
password_file /etc/mosquitto/passwd
```

Create a password file for your MQTT broker by running this command.

```
sudo mosquitto_passwd -c /etc/mosquitto/passwd someguy
```
After that don't forget to restart Mosquitto.
```
sudo systemctl restart mosquitto
```

### Auto Install
```
Place Holder
```
### Check your MQTT Broker
Before we continue we could try to check if our broker receive the payload from our ESP. 
Run this command on our broker server to see the payload. If there's no results, check your connection and your configuration on both devices.
```
mosquitto_sub -h localhost -t test -u "someguy" -P "SuperSekritPassword"
```
![Broker Results](https://i.imgur.com/cIbYKx4.png)


## InfluxDB

* [Place Holder](http://place-holder/) - The Place Holder


## Grafana

Please read [Place Holder](https://place-holder) for Place Holder.


## Authors

* **Place Holder** - *Place Holder* - [Place Holder](https://place-holder)

Place Holder


## Acknowledgments

* Ayylmao

