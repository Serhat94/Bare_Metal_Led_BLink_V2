
LED lighting and extinguishing application via Uart. Pin Library was specially created. To use the library, just enter PinMode("GPIO pin number", "Pin state(1-0)")


![image](https://github.com/user-attachments/assets/5c2c29f9-4a5d-4047-bdd8-83cad81b1149)

![image](https://github.com/user-attachments/assets/5bf27687-cbf6-4cfc-995a-d88ba425786e)

**Parity Bit** 


Parity bit allows the receiver to check the correctness of the received data. Parity is a low–level error checking mechanism and has two different options to choose from: Even Parity and Odd Parity. After the receiver UART reads the data frame, it counts the number of bits with a value of 1 and checks if the total value is an even or odd number. If the parity bit is a 0 (even parity), the number of bits with a value of 1 in the data frame should sum-up to an even number. If the parity bit is a 1 (odd parity), the number of bits with a value of 0 in the data frame should sum-up to an odd number. When the parity bit matches the data, the receiver UART knows that the transmission was a success. Frankly speaking, the parity bit is optional and it’s actually not widely used.


**Baud Rate**


The Baud Rate specifies how fast the data is sent over the bus and it is specified in bits-per-second or bps. You can actually choose any speed for the baud rate. However, there are some specific values that are known to be the industry standards. The most common and widely-used standardized value is 9600. Other standard baud rates include: 1200, 2400, 4800, 19200, 38400, 57600 and 115200. Obviously, baud rates are always multiples of 300. Baud rates higher than 115200(bps) can be used with an additional probability of having, at best, missing data packets. The rule of thumb in UART communication is, both the transmitter and the Receiver UART must agree on the exact same Baud Rate for a successful data transmission.
