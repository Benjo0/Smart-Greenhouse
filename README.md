
<a name="readme-top"></a>



<br />
<div align="center">




<h3 align="center">Smart greenhouse</h3>

</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>




## About The Project

![overviewOfProject](https://github.com/Benjo0/Smart-Greenhouse/assets/45501925/27b705b8-b67f-4d14-8ec7-137841bc7698)


This project task provides a comprehensive description of the design of an automated greenhouse for plants. The system operates in a fully automated manner, ensuring optimal conditions for the growth of specific plant species. It meticulously monitors the greenhouse temperature, soil moisture levels, and greenhouse lighting, making necessary adjustments to achieve optimal parameters. 

The system incorporates humidity and lighting sensors, along with a temperature probe and a water level float sensor. The control components of the system consist of a motor pump for efficient plant irrigation and a servo motor responsible for regulating the greenhouse window. To facilitate plant growth, specialized UV LED lights are installed as a supplementary light source. These lights are activated when the light sensor, in this case a photoresistor, detects insufficient light levels.

Overall, the project focuses on creating an advanced and sophisticated automated greenhouse that ensures optimal plant growth conditions through precise monitoring and intelligent adjustment of various environmental factors.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Getting Started

First of all you have to get all hardware components and connect them same how is showed on scheme photo. 
After that you should upload code on your arduino and that's it.





For this project, the Arduino Nano microcontroller has been chosen as the control unit. The selected control elements include an electric submersible pump for plant watering and a servo motor for opening the greenhouse window. UV LEDs have been chosen as the light source. The plant, along with the soil, is contained within a closed system, the greenhouse. Above the plant, UV LEDs are positioned, which only turn on when the photosensor does not detect sufficient light, indicating that the plant lacks adequate light. The greenhouse also features a window that is controlled by the servo motor. This servo motor is activated to open the window when the temperature rises above the optimal range and closes it in case of low temperatures. This helps to regulate the greenhouse temperature, which is measured by a temperature probe, ensuring optimal conditions. Additionally, a soil moisture sensor is placed, which sends a specific parameter to the Arduino. In the code, this parameter represents the threshold between dry, excessively wet, and optimally moist soil. Based on this parameter, the motor pump in the water reservoir is activated for a specific duration, providing water to the plant's roots. The water reservoir is filled and sufficient for a designated watering period. A float sensor is placed on the reservoir to measure the water level. If the water level drops below a certain point, indicating insufficient water, a GSM module sends a message to the user indicating the water shortage, and the water pump is turned off. The GSM module requires a constant 4V, so a step-down converter is used at the input to convert the 9V input voltage to 5V. Additionally, a relay is required, which utilizes the low current of the float sensor to activate its electromagnet, enabling a power circuit connection with the motor. The system states are displayed on an LCD screen.

List of components that are used: 
    <ul>
    <li>Arduino Nano</li>
    <li>GSM SIM800l modul</li>
    <li>LCD 16X2 I2C display</li>
    <li> DC 5V motor pump</li>
    <li> LM 2596 DC Buck Converter</li>
    <li> Float sensor</li>
    <li> LED diodes and resistors for them</li>
    <li> Relay 5V </li>
    <li> Sensor for humidity </li>
    <li> Photoresistor </li>
    <li> Temperature probe DS1820</li>
    <li> Arduino Micro Servo 9g SG90 </li>
    <li> Switch </li>
    </ul>

![shema](https://github.com/Benjo0/Smart-Greenhouse/assets/45501925/1b3a7596-a190-48da-9d92-1eb06b3b3527)

<p align="right">(<a href="#readme-top">back to top</a>)</p>








## Contact

Benjamin Galić -  benjogalic64@gmail.com

Project Link: [https://github.com/github_username/repo_name](https://github.com/Benjo0/Smart-Greenhouse.git)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


