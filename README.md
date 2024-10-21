# Tema de casă 1 - ⁠Sistem de încărcare a unui vehicul electric
Codul simuleaza o stație de încărcare pentru un vehicul electric, folosind LED-uri pentru a indica progresul încărcării și starea bateriei. Două butoane sunt utilizate pentru a porni și a opri procesul de încărcare. 
Programul gestionează stările butoanelor, controlează aprinderea LED-urilor, și monitorizează timpul de apăsare pentru a realiza funcții suplimentare, cum ar fi in cazul acesta oprirea după o apăsare lungă.

În timpul încărcării, LED-urile indică progresul prin aprinderea succesivă a celor 4 LED-uri (LED1 - LED4), care corespund nivelurilor de încărcare ale bateriei.

Fiecare LED clipește înainte de a trece la următorul nivel de încărcare.
LED-urile sunt actualizate la fiecare INTERVAL de 3 secunde (3000ms), simulând creșterea nivelului de încărcare al bateriei.

Timpul curent este monitorizat folosind funcția millis(), care permite verificarea duratei scurse între acțiuni fără a bloca programul, spre deosebire de funcția delay(), care oprește temporar execuția codului.

Dacă nivelul bateriei depășește 4, procesul de încărcare se oprește automat și LED-urile sunt resetate.

Variabile importante:
previous_time_millis: reține timpul ultimei actualizări de nivel al bateriei, folosit pentru a determina când să crească nivelul bateriei.

baterie: indică nivelul curent al bateriei (0 - 4).

incarcare: variabilă booleană care indică dacă bateria este în proces de încărcare (1 = activă, 0 = oprită).

Timer_buton: variabilă care memorează momentul în care butonul de stop a fost apăsat, pentru a permite oprirea după o apăsare lungă (2 secunde).

Start/Stop încărcare: Apăsarea butonului de start pornește procesul de încărcare, iar apăsarea lungă a butonului de stop (2 secunde) îl oprește.

#Componente
4x LED-uri (3 albastre, unul verde)
1x LED RGB (pentru starea de liber sau ocupat)
2x Butoane (pentru start încărcare și stop încărcare)
8x Rezistoare (6x 100ohm, 2x 2K)
Breadboard
Linii de legătură

