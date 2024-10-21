#include <Arduino.h>

// Definim pinii pentru LED-uri și butoane
#define LED1 10
#define LED2 9
#define LED3 8
#define LED4 7
#define LED_ROSU 4
#define LED_VERDE 6
#define LED_ALBASTRU 5

// Intervalul de timp în milisecunde între schimbările de stare
#define INTERVAL 3000 

// Definim pinii pentru butoanele de start și stop
#define BTNSTART 3
#define BTNSTOP 2

// Variabile globale
int previous_time_millis = 0; // Reține timpul anterior
int baterie;                  // Nivelul bateriei (de la 0 la 4)
int incarcare;                // Indică dacă bateria se încarcă (1) sau nu (0)
int Timer_buton = 0;          // Reține timpul la care a fost apăsat butonul STOP

void setup() {
  // Setăm pinii LED-urilor ca ieșiri
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  // Setăm pinii LED-urilor colorate ca ieșiri
  pinMode(LED_ROSU, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ALBASTRU, OUTPUT);

  // Setăm pinii butoanelor ca intrări cu rezistență de pull-up
  pinMode(BTNSTART, INPUT_PULLUP);
  pinMode(BTNSTOP, INPUT_PULLUP);
}

void loop() {
  // Citim starea butonului de start
  int buttonStart = digitalRead(BTNSTART);

  // Dacă butonul de start este apăsat
  if(buttonStart == LOW){
    delay(20); // Mică întârziere pentru a evita denaturarea semnalului
    incarcare = 1; // Pornim încărcarea
  }

  // Citim starea butonului de stop
  int buttonStop = digitalRead(BTNSTOP);

  // Dacă butonul de stop este apăsat
  if (buttonStop == LOW) {

    // Dacă Timer_buton este 0, înseamnă că acesta este momentul în care a fost apăsat
    if (Timer_buton == 0) {
      Timer_buton = millis(); // Înregistrăm timpul curent
    }

    // Dacă au trecut 2 secunde de când butonul a fost apăsat
    if (millis() - Timer_buton >= 2000) {
      delay(20); // Întârziere pentru debouncing
      incarcare = 0;  // Oprim încărcarea
      Timer_buton = 0; // Resetăm timer-ul pentru buton
    }
  } else {
    // Dacă butonul nu mai este apăsat, resetăm timer-ul
    Timer_buton = 0;
  }

  // Dacă bateria se încarcă
  if(incarcare){
    // LED-ul roșu este aprins (indică încărcarea)
    digitalWrite(LED_ROSU, HIGH);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ALBASTRU, LOW);
  }
  else{
    // Dacă nu se încarcă, LED-ul verde este aprins (indică completarea încărcării)
    digitalWrite(LED_ROSU, LOW);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_ALBASTRU, LOW);
    
    // Stingem toate LED-urile care indică nivelul bateriei
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    
    baterie = 0; // Resetăm nivelul bateriei
  }

  // Dacă încărcarea este activă
  if(incarcare){

    // Obținem timpul curent
    int current_time_millis = millis();
    
    // Dacă a trecut timpul definit de INTERVAL de la ultima actualizare
    if(current_time_millis - previous_time_millis >= INTERVAL) {

      // Actualizăm timpul anterior
      previous_time_millis = current_time_millis;

      // Creștem nivelul bateriei
      baterie++;

      // Dacă nivelul bateriei depășește 4, o resetăm și oprim încărcarea
      if(baterie > 4){
        baterie = -1;
        incarcare = 0;
      }
    }

    // Controlăm LED-urile în funcție de nivelul bateriei
    switch (baterie){
      case 0:
        // LED-ul 1 clipește pentru a indica nivelul 0
        digitalWrite(LED1, LOW);
        delay(200);
        digitalWrite(LED1, HIGH);
        delay(200);

        // Stingem toate celelalte LED-uri
        digitalWrite(LED_ROSU, LOW);
        digitalWrite(LED_VERDE, LOW);
        digitalWrite(LED_ALBASTRU, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        break;
      case 1:
        // LED-ul 1 este aprins, iar LED-ul 2 clipește
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        delay(200);
        digitalWrite(LED2, HIGH);
        delay(200);
        break;
      case 2:
        // LED-urile 1 și 2 sunt aprinse, iar LED-ul 3 clipește
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        delay(200);
        digitalWrite(LED3, HIGH);
        delay(200);
        break;
      case 3:
        // LED-urile 1, 2 și 3 sunt aprinse, iar LED-ul 4 clipește
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, LOW);
        delay(200);
        digitalWrite(LED4, HIGH);
        delay(200);
        break;
      case 4:
        // Toate LED-urile sunt aprinse (nivel maxim)
        digitalWrite(LED4, HIGH);
        break;
      default:
        break;
    }
  }
}
