Dit is het deelte dat op de wemos moet draaien.


# Installeren

Om de software op de wemos te installeren word er gebruik gemaakt van Platform IO

Installeren word simpel gedaan met 1 commando

`pio run -e DOMOBJECT -t upload --upload-port UPLOAD_PORT`

Bij `DOMOBJECT` moet de naam van het juiste object worden ingevoerd. Keuze bestaat uit:
* bed
* chair
* tablelamp
* pillar
* wall
* door
* fridge

Bij `UPLOAD_PORT` moet de juiste USB port geselecteerd worden, dit is per besturingssysteem anders.

Verder kan er `pio device monitor` gebruikt worden om de Serial van de wemos uit te lezen.
