# ESP8266 with Grafana and InfluxDB

The shit you setup for your glorious Grafana Dashboard.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

## Prerequisites

Ingredients :

```
1. ESP8266
2. A bunch of Sensor you want to use like BM180 or DHT11
3. 10k Resistors for pull up/down
4. 100nF Capacitors for power
5. LDO regulator to 3.3V
6. Proto board
```

## Flashing ESP8266

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

## License


This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Ayylmao
