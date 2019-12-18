
objects = [
    {"id": 1, "actuators": {"led": 1},                          "sensors": {"forceSensor": 1, "button": 1}},
    {"id": 2, "actuators": {"led": 1, "vibrator": 1},           "sensors": {"forceSensor": 1, "button": 1}},
    {"id": 3, "actuators": {"led": 1},                          "sensors": {"motionSensor": 1, "button": 1}},
    {"id": 4, "actuators": {"led": 1, "buzzer": 1},             "sensors": {"gasSensor": 1, "button": 1}},
    {"id": 5, "actuators": {"led": 1, "window": 1},             "sensors": {"dimmer": 1, "LDR": 1}},
    {"id": 6, "actuators": {"cooling": 1},                      "sensors": {"thermometer1": 1,"thermometer2": 1, "openClose": 1}},
    {"id": 7, "actuators": {"led1": 1, "led2": 1, "servo": 1},  "sensors": {"button1": 1, "button2": 1}}
]


def process_sensors(obj_id, sensors=[], pi_sensors=[]):
    pass


def process_actuators(obj_id, actuators=[], pi_actuators=[]):
    if actuators:
        pass
    pass


def web_translate_objects():
    web_objects = []

    for o in objects:
        web_objects.append(translate_object(o))

    return web_objects


def translate_object(obj):
    sensors = obj.get("sensors")
    actuators = obj.get("actuators")
    web_sensors = []
    web_actuators = []

    if sensors:
        web_sensors = [
            {"name": translate_component(obj["id"], s), "value": sensors[s]}
            for s in sensors
        ]

    if actuators:
        web_actuators = [
            {"name": translate_component(obj["id"], a), "value": actuators[a]}
            for a in actuators
        ]

    return {"name": translate_object_name(obj["id"]), "sensors": web_sensors, "actuators": web_actuators}


def translate_component(obj_id, sensorname):
    name = (str(obj_id) + sensorname)

    ### Sensors ###
    if name in ["1forceSensor", "2forceSensor"]:
        return "Druksensor Waarde"

    if name in ["1button", "2button", "3button", "4button"]:
        return "Knop Status"

    if name in ["3motionSensor"]:
        return "Beweging Gedetecteerd"

    if name in ["3motionSensor"]:
        return "Beweging Gedetecteerd"

    if name in ["4gasSensor"]:
        return "Gas Sensor Waarde"

    if name in ["5dimmer"]:
        return "Dimmer Waarde"

    if name in ["5dimmer"]:
        return "Dimmer Waarde"

    if name in ["5LDR"]:
        return "Licht Sterkte Waarde"

    if name in ["6thermometer1"]:
        return "Binnentemperatuur"

    if name in ["6thermometer2"]:
        return "Buitentemperatuur"

    if name in ["6openClose"]:
        return "Deur Gesloten"

    if name in ["7button1"]:
        return "Deurknop Binnen"

    if name in ["7button2"]:
        return "Deurknop Buiten"

    ### Actuators ###
    if name in ["1led", "2led", "3led", "4led", "5led"]:
        return "Licht Status"

    if name in ["2vibrator"]:
        return "Massage Status"

    if name in ["4buzzer"]:
        return "Alarm Status"

    if name in ["5window"]:
        return "Raam Dim Status"

    if name in ["6cooling"]:
        return "Koelkast Status"

    if name in ["7led1"]:
        return "Licht Binnen Status"

    if name in ["7led2"]:
        return "Licht Buiten Status"

    if name in ["7servo"]:
        return "Deur Status"

    print("NAME NOT FOUND: ", name)
    return "LEEG"


def translate_object_name(obj_id):
    return {"1": "Bed", "2": "Stoel", "3": "SchemerLamp", "4": "Zuil", "5": "Muur", "6": "Koelkast", "7": "Deur"}[str(obj_id)]

