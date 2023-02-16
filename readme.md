# API DOCS

## Button.h
*Button.h is a class for detecting button presses asynchronous with the rest of the code, using interupts.*

>`Button::Button(int pin)`

The constructor registers an interupt to the specified pin and > starts listening for button presses.

>`bool Button::wasPressed();`
 
When called it returns if the button was pressed since the last call. Therefore you always get the correct reponse regardless of any processes halting the program during the press.

If you wan't to clear any button presses you can call `wasPressed();` without using the return value.

<br/><br/>

---
## Motor.h
*Motor.h is used for controling a motor controller with a PWM speed input.*

>`Motor::Motor(int pin)`

The constructor takes the pin number that the motor controller is connected to and initialises the connection. 

>`void Motor::start(int speed)`

This function starts the motor with the specified speed, a value between 0-255. 

>`void Motor::stop()`

Stops the motor, the same as calling `Motor::start(0)`

<br/><br/>

---
## Network.h
*Network.h is used as an abstraction layer to access EPS8266 network functions*

>`Network::init(Pushbullet pushbullet)`

**Needs to be called before any other network functions**

This function connects and setups and connects to network.

Needs a pushbullet object to handle errors.

>`Network::httpGETRequest(const char* serverName, String access_token)`

Sends a get request to specified url with an access_token

`serverName` is the full url for the get request.

`access_token` is a bearer token, this gets wrapped with `Authorization Bearer` in the function.

<br/><br/>

---
## RGBLED.h
*This function controlls a common cathode rgb led*

> `RGBLED::RGLED(int pinR, int pinG, int pinB)`

Initialises the pins and led.

> `void RGBLED::loop()`

**Needs to be run continously for blink functionality to work. If you are not using blink you can leave this out.**

> `void RGBLED::setColor(int R, int G, int B)`

Sets the led to the color specified.
All values are between 0-255.


> `void RGBLED::blink(int R, int G, int B, int ms)`

Blinks the led with the interval specified in the `ms` var.

R, G and B values are color values between 0-255


<br/><br/>

---
## Pushbullet.h
*Handles communication with pushbullet, a service that pushes notifications to your phone*

> `void Pushbullet::push(String title, String message)`

Use this function to push a note to the phone specified in store.
both title and message has to be supplied as pushbullet can't handle empty titles or messages.

<br/><br/>

---
## Nordigen.h
*Handles communication with the bank to check if any new transactions exist*

> `bool Nordigen:newCrustiTransactionExists(Network network)`

Checks if there are any new transactions that matches the criteria for a "crusti transaction" and returns true or false.

<br/><br/>

---
## Store.h
*Handles both config store and how many crustis are left*

> `bool Store::checkTransaction(String id)`

Checks wether or not a transaction already has been handled and reported. If not return true and reports the id so later calls of the same id returns false.

> `int Store::getCrustis()`

Returns the current amount of crustis in store.

> `int Store::setCrustis(int amount)`

Sets the current amount of crustis in store.

> `int Store::addCrustis(int amount)`

Adds the amount of crustis to the store.
Negative values are accepted.

> `String Store::getConfigValue(String key)`

Gets the config value with the specifed key

> `String Store::setConfigValue(String key, String val)`

Set the config value of key to val.