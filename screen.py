from lcd.lcd import LCD
from lcd.i2c_pcf8574_interface import I2CPCF8574Interface


# Screen layout:
######################
# Direction: Forward #
# Lights:    On      #
# Stereo:    On      #
# Blinkers:  Left    #
######################

class Screen:
    def __init__(self, i2c):
        self.__lcd = LCD(I2CPCF8574Interface(i2c, 0x27), num_rows=4, num_cols=20)

    __lcd: LCD

    __status: list = []

    def set_status(self, option: str, status: str):
        """
        Show status, we just list the last 4 things that changed.
        """
        # Add latest status to the list
        option += ":"
        while len(option) < 10:
            option += " "
        self.__status.append(f"{option} {status}")
        print(f"{option} {status}")  # Handy for debugging

        # Cull history
        while len(self.__status) > 4:
            self.__status.pop(0)

        # Update the display
        self.__lcd.clear()
        for i in range(0, 4):
            if len(self.__status) < i + 1:
                continue  # Don't print more status than we've collected
            self.__lcd.set_cursor_pos(i, 0)
            self.__lcd.print(self.__status[i])

    def __clear_line(self, row: int):
        """
        Clear the specified row.
        :param row: Row number
        """
        self.__lcd.set_cursor_pos(row, 0)
        for i in range(self.__lcd.num_cols):
            self.__lcd.print(" ")
