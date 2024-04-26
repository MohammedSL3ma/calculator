<h1>Hello,</h1>
<p>It is a project using a simulation site to implement a simple calculator by using:</p>
<ul>
  <li>ESP32 microcontroller with <code>Serial.begin(9600)</code>.</li>
  <li>LCD of type 16x2.</li>
  <li>Keypad of type 4x4.</li>
</ul>

<hr/>

<h2>Keypad GPIO Connections</h2>
<pre>
byte rowPins[ROWS] = {21, 19, 18, 5}; // Row pin connections
byte colPins[COLS] = {23, 22, 1, 3}; // Column pin connections
</pre>

<h2>Define LCD Connections (16x2 in 4-bit mode)</h2>
<pre>
LiquidCrystal lcd(14, 13, 12, 27, 26, 25); // RS, E, D4, D5, D6, D7
</pre>
