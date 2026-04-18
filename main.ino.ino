// Projeto Sensor De Luminosidade com transição suave(fade)
// Autor: Arthur Miguel
// Descrição? Alterna entre modo Dia e Noite com base na luz do ambiente

int verde = 6;
int azul = 9;
int buzzer = 5;
int amarelo1 = 10;

int vermelho = 3;

int amarelo2 = 11;

int sensor = A0;
bool modoNoite = true;
void setup(){
  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(amarelo1, OUTPUT);
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}


void nightBuzzer(){
  
     tone(buzzer, 349);
     delay(100);

    noTone(buzzer);
    delay(100);

    tone(buzzer, 179);
    delay(100);
     
    noTone(buzzer);
    delay(100);
  


}

void dayBuzzer(){
  tone(buzzer, 679);
  delay(100);

  noTone(buzzer);
  delay(100);

  tone(buzzer, 579);
  delay(100);
  
  noTone(buzzer);
  delay(100);
  

 
}

void transicaoDia(){
  for(int i = 0; i <= 255; i++){
    analogWrite(azul, i);  // Dia sobe
    analogWrite(verde, i);


    // Noite desce
    analogWrite(amarelo1, 255 - i);
    analogWrite(vermelho, 255 - i);
    analogWrite(amarelo2, 255 - i);

    delay(1); // Delay de 1 milisegundo
  }
  
  analogWrite(azul, 255);
  analogWrite(verde, 255);
}


void transicaoNoite(){
  for(int i = 0; i <= 255; i++){ // For para o fade
    analogWrite(amarelo1, i); // Noite sobe
    analogWrite(vermelho, i);
    analogWrite(amarelo2, i);

    

    // Dia desce
    analogWrite(azul, 255 - i); // Isso subtrai o valor atual do for com o valor pwm do pino, isso faz efeito de fade apagando
    analogWrite(verde, 255 - i);
    delay(1);
  }
  analogWrite(amarelo1, 255); // Garantir o valor
  analogWrite(vermelho, 255);
  analogWrite(amarelo2, 255);
}

void desligar(){
  analogWrite(azul, 0);
  analogWrite(verde, 0);
  analogWrite(amarelo1, 0);
  analogWrite(amarelo2, 0);
  analogWrite(vermelho, 0);
  noTone(buzzer);
}

void loop(){
  int valor = analogRead(sensor);

  Serial.println("valor: ");
  Serial.println(valor);

  Serial.println(" | Sensor: ");
  Serial.println(valor < 50 ? "Noite" : "Dia");

  Serial.println(" | Sistema: ");
  Serial.println(modoNoite ? "Noite" : "Dia");

  if(modoNoite && valor < 45){         // 45 = limite para escuro
    // Função para buzzer
    nightBuzzer();                                                                                                      
    // Função para fade
    transicaoNoite();

    modoNoite = false; // No final muda para false, e passa para o proximo if

  }
if(!modoNoite && valor > 60){         // 60 = limite para claro
                                      // intervalo evita oscilações rapidas (histerese)
    dayBuzzer();
    transicaoDia();
    modoNoite = true; // para reiniciar o ciclo
 }                                                                          



  }
