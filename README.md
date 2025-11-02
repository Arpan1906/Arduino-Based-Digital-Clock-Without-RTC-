# Arduino-Based-Digital-Clock-Without-RTC-
The following project demonstrates "A Real-Time Digital Clock" built using Arduino Uno R3, a 16x2 LCD display, and push buttons—no RTC module required. The project uses Arduino’s internal timing and interrupts to display accurate time and allows manual time setting via buttons. Simple, reliable, and fully customizable. I hope this will be helpful..

![WhatsApp Image 2025-11-02 at 20 53 50_1d695cb6](https://github.com/user-attachments/assets/68578f93-e7bd-4755-af60-ff37cd234fbd)



# Project Overview
This project shows how to build a functional, low-cost digital clock using basic electronic components and Arduino’s core capabilities. It uses a 16x2 LCD display to show hours, minutes, and seconds while relying on Arduino’s internal timer functions to maintain time accuracy. Push buttons allow users to set and adjust the time manually. A small onboard buzzer is connected to acknowledge every action along with led indicators.

Let's get started...

# Features
- Low Cost.
- Low power consumption.
- Functional and reliable.
- Manual time setting.
- Temperature visibility.
- Buzzer acknowledgement.

# Future works 
- Adding a IR sensor to make changes of time.
- Alarm functionality.
- Backup power supply for load shedding conditions.
- Voice feedback for HOUR acknowledgement.
- Date and weekdays showing.

# Applications
The project or the clock is suitable for -
- Home (Such cases some modifications are required)
- Offices (Such cases some modifications are required)
- Experimental studies of Embedded System for begginers.

# Core Components used in this project
- Arduino Uno (Main MCU)
- 16*2 LCD Display
- Push Buttons
- Red led
- 5V onboard buzzer
- 1k ohm resistor
- 10K potentiometer
- LM35 temperature sensor

# Working Principle

Timing Control and Display
- The Arduino’s internal millis() function is used to measure elapsed time in milliseconds. When 1000 milliseconds have passed, the code increments the seconds counter. Upon reaching 60 seconds, the minutes counter is increased, and similarly, when minutes reach 60, the hour counter advances. This ensures continuous and accurate time progression.


LCD Display Functionality
- A 16x2 LCD module is initialized to display real-time hours, minutes, and seconds. The time is refreshed every second. When switched to edit mode, the display shows the temporary editable time values, allowing the user to modify them before saving.
![WhatsApp Image 2025-11-02 at 20 53 49_dcf705bd](https://github.com/user-attachments/assets/f28c283d-ff7d-4cc1-ad36-ff13aa6ab65e)



Modes of Operation

- Normal Mode: The clock runs automatically, updating and displaying real-time values.

- Edit Mode: Triggered by pressing the mode button. In this state, the user can manually set hours, minutes, and seconds using the navigation and edit buttons.

Push Button Interface
- Four push buttons are connected to the Arduino:

- Mode Button: Switches between normal and edit modes.(M)

- Position Button: Moves the cursor among hour, minute, and second fields.(P)

- Edit Button: Increases the selected time value.(E)

- OK Button: Confirms new time settings and returns to normal mode.(O)

![WhatsApp Image 2025-11-02 at 20 44 06_bcf93752](https://github.com/user-attachments/assets/84c122ba-9364-4fa0-b1b2-6ac7c0c87bf6)

Non-Blocking Delay Logic
- Instead of using traditional delay functions, the program uses non-blocking timing with millis() to keep all operations (time update and button reading) running simultaneously, ensuring smooth real-time performance.

Buzzer Acknowledgment
- Every valid button press triggers a short tone on the buzzer connected to pin 8, providing auditory feedback for user actions.
![WhatsApp Image 2025-11-02 at 20 44 05_cc80335e](https://github.com/user-attachments/assets/efbf97c5-4f9d-4683-a870-754f8254b01e)


# Additional Feature
I wanted to print the temperature value on the lcd screen along with the time. For this feature, I have connected LM35 temperature sensor with the A4 pin of arduino uno and 5v and GND pins with the respective pins pf arduino uno. Since it is an analog sensor that is why analog pin is used. This sensor enables an extra feature at a very low cost.
![image](https://github.com/user-attachments/assets/5afd4cec-a70e-4fb8-902e-6b4dafebebaf)


# Video Presentation
- ![YouTube](www.youtube.com)

# Note
The red led's I have used in this project are optiuonal. My intention was just to give  it a more cool and nice look. Consumes some extra power and the led pattern changes along with the modes. (Refered to the video for clear understanding).

# Summary
- Project Abstract: Arduino-Based-Digital-Clock-Without-RTC-

- RTC or a Real time clock provides precise time and date.

- My goal was to give you  a practical understanding of various phases that an embedded project goes through.

- Development Phases: Requirement Analysis, Design, Implementation (Wiring & Coding) and Testing phase.

The finalized requirements:

- Real Time Clock using Arduino Uno with no time preservation 
- Display the Time in H:M:S format on a 16x2 LCD.
- Provision for Editing Time using Push buttons.
- Each Key press should be acknowledged using buzzer sound
