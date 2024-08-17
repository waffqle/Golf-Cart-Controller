from features import Features
from screen import Screen
from time import sleep


class Cart:
    def __init__(self, i2c, mcp):
        self.display = Screen(i2c)
        self.features = Features(mcp)

        display: Screen
        features: Features

    def set_direction(self, direction):
        """
        Go forwards and backwards!
        :param direction:
        """
        if direction == self.GO_FORWARD:
            self.display.set_status("Direction", "Forward")
            self.features.go_forward()
        elif direction == self.GO_BACKWARD:
            self.display.set_status("Direction", "Reverse")
            self.features.go_backward()
        else:
            self.features.go_forward()  # Let's default to NOT being in reverse
            raise Exception("Invalid direction")

    def toggle_direction(self):
        """
        Toggle between forwards and backwards!
        """
        forward = self.features.toggle_direction()
        self.display.set_status("Direction", "Forward" if forward else "Backward")

    def toggle_stereo(self):
        """
        Turn the stereo on and off
        """
        on = self.features.toggle_stereo()
        self.display.set_status("Stereo", "On" if on else "Off")

    def toggle_headlights(self):
        """
        Turn the headlights on and off
        """
        on = self.features.toggle_headlights()
        self.display.set_status("Headlight", "On" if on else "Off")

    def set_brake_lights(self, on: bool):
        """
        Turn the brake lights on and off
        :param on:
        """
        self.features.set_brake_lights(True if on else False)

    def set_blinkers(self, status: int):
        """
        Set the blinkers (Off, Left, Right)
        :param status:
        """
        if status == self.BLINKER_LEFT:
            self.display.set_status("Blinker", "Left")
            self.features.set_blinker_left()
        elif status == self.BLINKER_RIGHT:
            self.display.set_status("Blinker", "Right")
            self.features.set_blinker_right()
        else:
            self.display.set_status("Blinker", "Cancel")
            self.features.cancel_blinkers()

    def self_test(self):
        # Test everything
        print("Directions")
        self.set_direction(Cart.GO_FORWARD)
        sleep(1)
        print("Go backward")
        self.set_direction(Cart.GO_BACKWARD)
        sleep(1)
        print("Stereo")
        self.toggle_stereo()
        sleep(1)
        self.toggle_stereo()
        sleep(1)
        print("Headlights")
        self.toggle_headlights()
        sleep(1)
        self.toggle_headlights()
        sleep(1)
        print("Brake lights on")
        self.set_brake_lights(True)
        sleep(1)
        print("Brake lights off")
        self.set_brake_lights(False)
        sleep(1)
        print("Blinkers")
        self.set_blinkers(Cart.BLINKER_LEFT)
        sleep(1)
        self.set_blinkers(Cart.BLINKER_RIGHT)
        sleep(1)
        self.set_blinkers(Cart.BLINKER_OFF)

    # Drive directions
    GO_FORWARD: int = 0
    GO_BACKWARD: int = 1

    # Blinker statuses
    BLINKER_OFF: int = 0
    BLINKER_LEFT: int = 1
    BLINKER_RIGHT: int = 2
