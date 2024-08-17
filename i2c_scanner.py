import busio


def scan(i2c:busio.I2C):
    """
    Scan the i2c bus and report any addresses that are found
    :type i2c: busio.I2C
    """

    # Scan the bus
    while not i2c.try_lock():
        pass

    try:
        print(
            "Scanning I2C. Addresses found:",
            [hex(device_address) for device_address in i2c.scan()],
        )
    finally:  # unlock the i2c bus when ctrl-c'ing out of the loop
        i2c.unlock()

