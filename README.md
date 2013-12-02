K_Controller
============

Simple Timelapse Motion Controller

The K_Controller is probably the most simplistic (ans smallest) approach to a timelapse motion controller.
It is Arduino based and runs on an Atmega328. It has very little part count and can be used with dedicated hardware 
(eagle files are on the way...) or with basically any Arduino, a motor shield that uses a L293 driver chip and a 
protoype board for the optocouplers (you could probably use a relay shield, too). 


The user can set the camera interval with a potentiometer and the motor speed with another pot. 
The motor move mode can be switched from Shoot-Move-Shoot to continous by pushing a button. 

User Manual: 

1. Connect your motor of choice (12V, max 1 A) to the DC Output of the K_Controller (5.5/2.5 mm DC jack)
2. Connect your camera using an off-the-shelf 2.5 mm camera cable (made by Pixxel and others)
3. Supply 12 V power to the DC in jack of the K_Controller
4. Set the camera interval with the interval potentiometer. The interval led will give you visual feedback. 
5. If you need to move your motor before exposing, push the speed potentiometer and turn it in one way or the other. 
  You will see your motor moving. If you reach your starting position, just push the button again or set the motor speed to zero. 
6. You can now either let the motor run in continous mode or Shoot-Move-Shoot. Set the motor speed, or in SMS mode the motor running time per interval with the speed pot.
    In SMS mode the motor will only run when the intervallometer is running, so you might want to test drive it quickly. 
7. When you push the interval pot/ button, the program starts and runs basically forever or until the battery is dead. 


