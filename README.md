[![Build Pi-Summoner](https://github.com/TylerCode/PiSummoner/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/TylerCode/PiSummoner/actions/workflows/c-cpp.yml)

# PiSummoner

This is a utility that solves a very specific problem I have. I like to take my old PCs and stuff them in a server chassis for the ability to boot them up when needed or like for example if there is an old game I want to play on an old OS. 

The problem is that Wake On LAN isn't always available for these machines or its inconsistent. So the easiest solution is just to walk over and turn on the PC, but I'm lazy and sometimes I'm not playing from the same place as the machine. So having a little web utility that can "physically" press the power button is the best option, if a bit janky. 

![image](https://github.com/TylerCode/PiSummoner/assets/18288340/c57e9fff-9693-460a-b0d8-3f9f541ca8bf)


## The Hat

So for the hat, you can really use whatever you like. I personally used [this guy for now](https://www.amazon.com/gp/product/B07CZL2SKN) (not an affiliate link or anything). You can use whatever you like, just be sure to modify the main.c file to include the correct pinouts and such.

## The Setup

For my setup, I repurposed an old Raspberry Pi 1b (the little dude still works after almost a decade) and the hat above. I installed Rasbperry Pi Lite (32-bit). If you're doing this on a newer Pi, you'll want to do the 64 bit version. 

Once that is all setup, install the dependencies and clone this repository

```bash
sudo apt-get install gcc libmicrohttpd-dev pigpio git
git clone https://github.com/TylerCode/PiSummoner
cd PiSummoner
```

Next up, we'll build the application and install it. This will install and start a daemon called `pi-summoner`

```bash
./build.sh
sudo ./install.sh
```

Now, you should be able to visit the webpage at `http://<yourpi-IP>:8080`

Clicking each button should trigger a different relay for 1 second, or on the long press, 8 seconds (to allow for hard resets when a machine is frozen).

## Uninstalling

To uninstall, simply use the uninstall script included. 

```bash
sudo ./uninstall.sh
```

That's it, you can start fresh again by doing a git pull, then running the setup steps again. 

## Contributing

I'm pretty open to any suggestions, feature additions, and code improvements (it's quite messy). This would not be a bad first project to contribute to for someone new to C and contributions are welcomed by developers of any experience level. As such, here is a very detailed guide to get started:

### Getting Started

1. **Fork the Repo**
   - Start by forking the PiSummoner repository on GitHub into your own account.
  
2. **Clone Your Fork**
   - Clone your fork to your local machine:
     ```
     git clone https://github.com/your-username/PiSummoner.git
     ```
     
3. **Create a New Branch**
   - Create a new branch for your feature or fix. Branch names should be descriptive, like `feature/auto-shutdown` or `fix/gpio-bug` but I'm not overly picky:
     ```
     git checkout -b your-branch-name
     ```

### Making Changes

1. **Make Your Changes**
   - Implement your feature or fix. Please keep your code consistent with the project's coding style.

2. **Commit Your Changes**
   - Commit your changes with clear, descriptive commit messages. 
     ```
     git commit -am "Add a brief description of your changes"
     ```

3. **Test Your Changes**
   - Ensure your changes do not break existing functionality. Test your code thoroughly.

4. **Update README or Documentation if Necessary**
   - If your changes require it, update the README or documentation.

### Submitting a Pull Request

1. **Push to Your Fork**
   - Push your changes to your fork on GitHub:
     ```
     git push origin your-branch-name
     ```

2. **Create a Pull Request**
   - Go to the PiSummoner repository on GitHub and click on "Pull Request".
   - Choose your branch and provide a title and description for your changes.
   - Click "Create pull request".

### After Your Pull Request is Merged

- Once your pull request is merged, you can pull the changes from the main repository to your local repo:
  ```shell
  git pull origin master
  ```
- Don't forget to delete your branch if it's no longer needed:
  ```shell
  git branch -d your-branch-name
  ```

### Additional Notes

- By contributing to PiSummoner, you agree that your contributions will be licensed under its MIT License.
- If you have any questions or need help, feel free to open an issue for discussion.


## Final Notes

This project was really just an excuse to do some stuff in C which is not something I get to do super often anymore. If it helps a single solitary person (or just feeds the AI machines) then I'm happy. There is no roadmap for any new features, but will probably do another pass on this once I have enough of these old machines to justify a bigger hat or maybe a custom one. 
