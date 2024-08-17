import digitalio
from adafruit_mcp230xx.mcp23017 import MCP23017


class Features:
    # GPIO Expander
    __mcp: MCP23017

    # Relays
    __direction_forward: digitalio.DigitalInOut
    __direction_backward: digitalio.DigitalInOut
    __stereo: digitalio.DigitalInOut
    __headlights: digitalio.DigitalInOut
    __brake_lights: digitalio.DigitalInOut
    __blinker_left: digitalio.DigitalInOut
    __blinker_right: digitalio.DigitalInOut

    def __init__(self, mcp):
        self.__mcp = mcp
        self.__direction_forward = self.__mcp.get_pin(0)
        self.__direction_backward = self.__mcp.get_pin(1)
        self.__stereo = self.__mcp.get_pin(2)
        self.__blinker_left = self.__mcp.get_pin(3)
        self.__blinker_right = self.__mcp.get_pin(4)
        self.__headlights = self.__mcp.get_pin(5)
        self.__brake_lights = self.__mcp.get_pin(6)

    #
    # Direction
    #
    def toggle_direction(self):
        # IMPORTANT:
        # Always turn one relay OFF before turning the other ON.

        # If we're going forward, go backward
        if self.__direction_forward.value:
            self.go_backward()
        else:
            self.go_forward()

        return self.__direction_forward.value


    def go_forward(self):
        self.__direction_backward.value = False
        self.__direction_forward.value = True


    def go_backward(self):
        self.__direction_forward.value = False
        self.__direction_backward.value = True


    #
    # Blinkers
    #
    def set_blinker_left(self):
        self.__blinker_left.value = True
        self.__blinker_right.value = False


    def set_blinker_right(self):
        self.__blinker_left.value = False
        self.__blinker_right.value = True


    def cancel_blinkers(self):
        self.__blinker_left.value = False
        self.__blinker_right.value = False


    #
    # Other accessories
    #
    def toggle_headlights(self) -> bool:
        self.__headlights.value = not self.__headlights.value
        return self.__headlights.value


    def toggle_stereo(self) -> bool:
        self.__stereo.value = not self.__stereo.value
        return self.__stereo.value


    def set_brake_lights(self, on: bool):
        self.__brake_lights.value = on
