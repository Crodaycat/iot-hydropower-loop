import paho.mqtt.client as mqtt
import time

# Configuración del broker MQTT
broker_address = "192.168.43.129"
broker_port = 1883
topic_esp = "hydro/esp"
topic_raspberry = "hydro/raspberry"
state_of_system = "ON"

# Callback cuando se establece la conexión con el broker MQTT
def on_connect(client, userdata, flags, rc):
    print("Conectado al broker con resultado: " + str(rc))
    # Suscribirse al topic
    client.subscribe(topic_esp)

# Callback cuando se recibe un mensaje MQTT
def on_message(client, userdata, msg):
    global state_of_system
    principal, auxiliar, current_state = msg.payload.decode().split(",")
    if current_state != state_of_system:
        client.publish(topic_raspberry,state_of_system)
    print("Current state",current_state)
    print("Estado tanque principal: " + principal)
    print("Estado tanque auxiliar: " + auxiliar)
    print_state_of_system()
    if int(principal) < 50 and int(auxiliar) < 50:
        print("Tanque principal y auxiliar lleno")
        if current_state == "ON":
            turn_off_system(client)
        else:
            return
    elif int(auxiliar) > 110 and int(principal) > 110:
        print("Tanque principal y auxiliar vacio")
        if current_state == "ON":
            turn_off_system(client)
        else:
            return
    elif current_state == "OFF":
        turn_on_system(client)
    

def print_state_of_system():
    global state_of_system
    if state_of_system == "ON":
        print("Sistema encendido")
    else:
        print("Sistema apagado")


def turn_on_system(client):
    global state_of_system
    if state_of_system == 'ON':
            return
    print("Iniciando sistema...")
    state_of_system = "ON"
    client.publish(topic_raspberry,state_of_system)
    

def turn_off_system(client):
    global state_of_system
    if state_of_system == 'OFF':
            return
    print("Apagando sistema...")
    state_of_system = "OFF"
    client.publish(topic_raspberry,state_of_system)

# Crear instancia del cliente MQTT
client = mqtt.Client()

# Configurar los callbacks
client.on_connect = on_connect
client.on_message = on_message

# Conectar al broker MQTT
client.connect(broker_address, broker_port, 60)

# Loop principal
client.loop_start()

while True:
    time.sleep(1)


# Detener el loop
#client.loop_stop()
#client.disconnect()
