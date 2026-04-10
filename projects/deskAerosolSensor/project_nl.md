# Desktop Luchtkwaliteit Meter

Dit project maakt met een ***Cheap Yellow Display*** een live dashboard voor
binnenluchtkwaliteit met een SEN66-sensor en een kleurgecodeerde 
3x3 tegelweergave.
Het systeem toont continu fijnstofwaarden (PM1.0, PM2.5, PM4.0, PM10), CO2,
VOC-index, NOx-index, temperatuur en luchtvochtigheid.

Een duidelijke opstartflow begeleidt netwerkverbinding, sensor-opwarming en statusmeldingen rechtstreeks op het scherm.
Als er nog geen netwerk is ingesteld, kan configuratie via een captive WiFi-portaal
gebeuren zonder opnieuw te flashen.
Wanneer geconfigureerd, worden metingen als JSON-berichten naar een MQTT-broker
verstuurd op een instelbaar interval.
Tijdsynchronisatie zorgt voor bruikbare tijdstempels in telemetrie en diagnose.

Er is ook een simulatiemodus voorzien om de dashboardlogica te testen zonder 
fysieke sensorinput.

Het resultaat is een praktisch, leesbaar en inzetbaar desktopmonitoringsysteem 
voor realtime omgevingsinzichten.
