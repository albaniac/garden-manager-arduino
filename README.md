# GARDEN-MANAGER - a network of arduino-based stuff to help managing your garden

## What is it

It's a "garden assistant" based on 2 parts : One network of sensors and One data management / alerting system.

**Sensor network is based on** :
* One Arduino-uno based simple Humidity / temperature / luminosity tracker, with piloted alim, and Lora connectivity, installed inside a greenhouse
* One Arduino-mega based more complexe sensor relay, with Humidity, temperature, luminisity, water level (from a rain gauge), earth moisture sensor, and optionnaly a basic camera, also with Lora connectivity, installed in a "remote garden"
* One Lora Gateway with ethernet connectivity. Basically based on an Arduino Yum

**Data management** is a custom app. Nothing decided yet on used technology, but probably a NoSql data manager, a Go app server, and a custom android app. Server will probably ran on a Raspberry.

## Why this project

At home we have 2 gardens :
* One at home, with a **greenhouse** where we sprout our vegetables.
* One **associative garden** at ~ 1 km from our home.

The problems we met : 
* The **greenhouse** needs a clean survey, to avoid extensive heat, and check that humidity is good. Something we can do with basic Temp / humidity sensor, with an alerting system (in a custom app) when values exceed a fixed range. 
* The **associative garden** is large, and there is no electricity, no water distribution. We have a well, so we have to water the garden with a watering can. More than 1h of work every two days just for watering, without optimized checking on the opportunity to do it or not, especially at the end of spring / beggining of summer when the weather is not fully sunny. Here again, temp / humidity sensors will help. Rain level check will be also usefull to check variability of water, and a dedicated soil moisture sensor will be able to say if we need to add water or not. I expect to just collect data at begining, and adjust alerting regarding the values. So I will have to collect many values. 

In the same time I'm very interested in IoT world, and wanted from a long time to start a project in it, so I decided to create something from scratch to lean arduino and other funny stuff.

I'm a programer wanting to discover something more fun than the basic entreprise java stuff I usually do. So this project is an opportunity to work with "physical stuff" and Arduino is amazing for this. I will also explore new programming with Go and Kotlin.

I will opensource everything, and will provide every details I can on used components.

## What you need

First, details on expected budget : For now I'm bellow 250€ for everything, including server environnment, but it may change as I will discover things. I try to make everything "reusable" for futur projects, so I will work with prototype shields. For this price I have 2 Arduino Uno, 1 arduino Mega Mega2560, 2 Lora Shield, 1 LoraWan Gateway based on arduino Yum, 1 specific Moisture sensor, various DHT11 temp / humidity sensors, 1 complete Raspeberry Pi 3 Rev A with SD/Alim/Box.

What to buy :
- I started working on Arduino with this very good kit : [Elegoo Mega2560 kit](https://www.elegoo.com/product/elegoo-mega-2560-project-the-most-complete-starter-kit/), at 55€ in every chinese stuff seler (I will buy almost only chinese clones, the standard Arduinos are too expensive)
- I have bought this Lora-based Iot kit : [Dragino Lora kit](https://www.tindie.com/products/edwin/lora-iot-development-kit/#product-name), at 115€ with shipping cost. As it includes the gateway, 2 arduino Uno + 2 Lora shield, the price is very good.
- The moisture sensor is from indie also : [I2C Soil moisture sensor](https://www.tindie.com/products/miceuz/i2c-soil-moisture-sensor/) : 12€ with shipping
- RaspeberryPi kit. But if you want much more power and usability with you "server", for twice the price you can buy a chinese NUC clone. I have for example a celeron (so x64 core, vs the RaspPi 32b arm Core) + 4Gb + 64Gb PC bought at 120€ on Gearbest. It's like 4 times the power of a raspPi, with x64 compatibility (so no custom build linux distrib, full docker compatibility ...). 

What I may add :
- A camera kit like this one [OV7670 Camera Module](http://www.elecfreaks.com/store/ov7670-camera-module-p-705.html)
- A better screen for the Remote-garden relay, like [this one from Adafruit](https://www.adafruit.com/product/358). As it includes a SD card reader, it will be usefull for camera kit.

## About Lora

Just check on Wikipedia... With this you have basically your own "low-power" 868Mhz network with up to 20km range. 

With the gateway you can then "link" the Lora network to any other networks. Some exit with even 3G network connectivity, Wifi connectivity ... I will work with ethernet connectivity.

## Building it

Soon ...

## Programming it

### Arduino codes

For now I have just started a prototype with DHT11 sensor and RTC management. 

Why RTC : I don't expect to collect values at every arduino loop, I suppose I will :
* Use a piloted alim for RTC controled start / shutdown of the sensor relay. Every 5 minutes I guess.
* Even if running this way, I do not need data from all sensors. For example I will expect from the Camera 1 picture every 30 minutes, something like that. So a RTC controlled programming will be usefull. Hopefully, everything is very easy to use, as usual with arduino. 