Dit is het gedeelte dat de communicatie tussen de front-end en de wemos regelt

# Installeren

## Voorbereidingen
Zorg ervoor dat je alle compile tools voor de raspberry pi installeert.

## Compilen
Als alle tools geinstalleerd zijn is het programma eenvoudig te compilen met dit commando:\
`armv8-rpi3-linux-gnueabihf-g++ -std=c++17 *.cpp */*.cpp -o Main`

## Uploaden & Starten
### Uploaden
Om de binary (Main) op de raspberry pi te zetten kan er gebruik worden gemaakt van SCP:\
`scp Main pi@<host|IP>:/home/pi`\
Er word gevraagd om het wachtwoord van de pi gebruiker in te voeren, hierna word het bestand geupload naar de pi.

### Starten
Om het te starten moet er met SSH op de pi worden ingelogd. Hier kan er met `./Main` het programma worden gestart.\
Mogelijk moet er nog `chmod +X Main` worden gedaan om de permissies voor de binary goed te zetten.
