# PiSummoner

This is a utility that solves a very specific problem I have. I like to take my old PCs and stuff them in a server chassis for the ability to boot them up when needed or like for example if there is an old game I want to play on an old OS. 

The problem is that Wake On LAN isn't always available for these machines or its inconsistent. So the easiest solution is just to walk over and turn on the PC but sometimes that isn't possible. So having a little web utility that can "physically" press the power button is the best option, if a bit janky. 


## The Hat

So for the hat, you can really use whatever you like. I personally used !(this guy for now)[https://www.amazon.com/gp/product/B07CZL2SKN]. You can use whatever you like, just be sure to modify the main.c file to include the additional ones.

## The Setup

For this I just did a default Raspberry Pi OS install on a Zero W. 

Once that is all setup, install the libs and clone this repository
```
sudo apt-get install gcc libmicrohttpd-dev pigpio
git clone https://github.com/TylerCode/PiSummoner
cd PiSummoner
```

Next up, we'll build the application and run it

```
gcc main.c -o main -lpigpio -lmicrohttpd -lrt
chmod +x main
./main
```

Now, you should be able to visit the webpage at `http://<yourpi-IP>:8080`

Clicking each button should trigger a different relay for 1 second.


For a more... permanent solution, you can run this in a tmux window or daemonize the application (which is probably what I will end up doing)


## Final Notes

This project was really just an excuse to do some stuff in C which is not something I get to do super often anymore. 
