import board
import busio
import digitalio
import keypad
# IO Expander used in relay board
from adafruit_mcp230xx.mcp23008 import MCP23008  # My stuff
import i2c_scanner
from cart import Cart

# Get the bus so we can talk to the screen
i2c = busio.I2C(board.SCL, board.SDA)

# What's on the bus?
i2c_scanner.scan(i2c)

# Setup relay board
mcp = MCP23008(i2c)
for i in range(0, 8):
    pin = mcp.get_pin(i)
    pin.direction = digitalio.Direction.OUTPUT

# Setup some buttons to control this thing!
button_pins = (
    board.D0, board.D1, board.D2, board.D3, board.D4, board.D5
)
buttons = keypad.Keys(button_pins,value_when_pressed=True,pull=True)

# THE GOLF CART!
golf_cart = Cart(i2c, mcp)

#print("Running self test")
#golf_cart.self_test()

# Make damn sure we default to going FORWARDS lol
golf_cart.set_direction(golf_cart.GO_FORWARD)

# Main loop. Watch for button presses
while True:
    button_event = buttons.events.get()

    if button_event:
        key_number= button_event.key_number
        # Most things are toggles, we only care when they're pressed
        if button_event.pressed:
            if key_number == 0:
                golf_cart.toggle_direction()
            if key_number == 1:
                golf_cart.toggle_stereo()
            if key_number == 2:
                golf_cart.toggle_headlights()
            if key_number == 3:
                golf_cart.set_brake_lights(True)
            if key_number == 4:
                golf_cart.set_blinkers(golf_cart.BLINKER_LEFT)
            if key_number == 5:
                golf_cart.set_blinkers(golf_cart.BLINKER_RIGHT)
        # Blinkers and brakes, we need to cancel when they're released
        if button_event.released:
            if key_number == 3:
                golf_cart.set_brake_lights(False)
            if key_number == 4 or key_number == 5:
                golf_cart.set_blinkers(golf_cart.BLINKER_OFF)