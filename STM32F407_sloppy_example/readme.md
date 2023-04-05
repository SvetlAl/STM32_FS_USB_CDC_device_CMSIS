This is a sloppy example, made quickly just to make sure, that the lib is working with F407.
Launched on STM32F407VET6 devboard.

How does it work?

You send data from host to device.
Device sends back all the data with each byte increased by 1.

For example, you send "12345"
You recieve "23456"
