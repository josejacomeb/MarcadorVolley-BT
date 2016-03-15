/*Marcador Ecuavolley -  Autor: José Jácome*/
//Alias para Pines de Desplazamiento
#define RD1 2
#define RD2 3
#define RD3 4
#define RD4 5
#define CLK 6
//Alias para entradas Digitales
#define Izq 7
#define Der 8
#define Reset 9
#define Subir 10
//Alias para LEDs de Cambio
#define LEDI 11
#define LEDD 12
//Funciones del Programa
void mostrar();
void inicializar();
void desplazamiento(int dato, int posicion);
void sumar(int lado);   //Suma del Lado Izquierdo(0) o Derecho (1)
void restar(int lado);   //Resta del Lado Izquierdo(0) o Derecho (1)
//Código para Formar los Numeros
int cero[7] = {1,0,0,0,0,0,0};
int uno[7] = {1,1,1,1,0,0,1};
int dos[7] = {0,1,0,0,1,0,0};
int tres[7] = {0,1,1,0,0,0,0};
int cuatro[7] = {0,0,1,1,0,0,1};
int cinco[7] = {0,0,1,0,0,1,0};
int seis[7] = {0,0,0,0,0,1,1};
int siete[7] = {1,1,1,1,0,0,0};
int ocho[7] = {0,0,0,0,0,0,0};
int nueve[7] = {0,0,1,0,0,0,0};
//Variables Auxiliares
int i = 0;
int j = 0;
//Tope de Puntos
int tope1 = 12;
int tope2 = 12;
int tope3 = 15;
//Muestra el Set Ganado por el equipo
int setD = 0;
int setI = 0;
//Cambios
short CambioI = 0;
short CambioD = 0;
//Variable para almacenar el Dato del Modulo BT
char bt;
//Donde se almacena el score
int marcador[4]={0,0,0,0};
//Variables para Sumar y Restar
int MarcadorD = 0, MarcadorI = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RD1, OUTPUT);
  pinMode(RD2, OUTPUT);
  pinMode(RD3, OUTPUT);
  pinMode(RD4, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LEDI, OUTPUT);
  pinMode(LEDD, OUTPUT);
  pinMode(Izq, INPUT);
  pinMode(Der, INPUT);
  pinMode(Reset, INPUT);
  pinMode(Subir, INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(LEDI,HIGH);
  digitalWrite(LEDD,HIGH);
  inicializar();
  delay(10);
}

void loop() {
  if(digitalRead(Izq)==LOW){
    delay(500);
    if(digitalRead(Izq)==HIGH){
      sumar(0);      
    }
    else{
      restar(0);
      delay(500);
      
    }
  }
  if(digitalRead(Der)==LOW){
    delay(500);
    if(digitalRead(Der)==HIGH){
      sumar(1);      
    }
    else{
      restar(1);
      delay(500);
      
    }
  }
  

}

void mostrar(){
  if(CambioI == 1){
    digitalWrite(LEDI,LOW);
    }
  else{
      digitalWrite(LEDI,HIGH);
    }
   if(CambioD == 1){
    digitalWrite(LEDD,LOW);
    }
    else{
      digitalWrite(LEDD,HIGH);
      }
   for(i = 7;i>=0;i--){
      for(j = 0;j<=3;j++){
         if(i==7){
            if(setI == 0){
               digitalWrite(RD1,HIGH);
               digitalWrite(RD2,HIGH);
            }
            if(setI == 1)
               digitalWrite(RD1,LOW);
            if(setI == 2)
               digitalWrite(RD2,LOW);
            if(setD == 0){
               digitalWrite(RD3,HIGH);
               digitalWrite(RD4,HIGH);
            }
            if(setD == 1)
               digitalWrite(RD3,LOW);
            if(setD == 2)
               digitalWrite(RD4,LOW);
         }
         else{
            if(marcador[j] == 0){
               desplazamiento(cero[6-i],j);
            }
            else if(marcador[j] == 1){
               desplazamiento(uno[6-i],j);
            }
            else if(marcador[j] == 2){
               desplazamiento(dos[6-i],j);
            }
            else if(marcador[j] == 3){
               desplazamiento(tres[6-i],j);
            }
            else if(marcador[j] == 4){
               desplazamiento(cuatro[6-i],j);
            }
            else if(marcador[j] == 5){
               desplazamiento(cinco[6-i],j);
            }
            else if(marcador[j] == 6){
               desplazamiento(seis[6-i],j);
            }
            else if(marcador[j] == 7){
               desplazamiento(siete[6-i],j);
            }
            else if(marcador[j] == 8){
               desplazamiento(ocho[6-i],j);
            }
            else {
               desplazamiento(nueve[6-i],j);
            }

         }
      }
      digitalWrite(CLK,LOW);   //Envia la Señal de Reloj a 0 aceptar el Desplazamiento
      digitalWrite(CLK,HIGH);   //Realiza el Desplazamiento al Ponerse en 1
      delayMicroseconds(1);
   }
}
void inicializar(){
   int i = 0;
   for(i=0;i<8;i++){
      digitalWrite(13,LOW);
      if(i==0 | i == 1){
         digitalWrite(RD1,HIGH);
         digitalWrite(RD2,HIGH);
         digitalWrite(RD3,HIGH);
         digitalWrite(RD4,HIGH);
      }
      else{
         digitalWrite(RD1,LOW);
         digitalWrite(RD2,LOW);
         digitalWrite(RD3,LOW);
         digitalWrite(RD4,LOW);
      }
      digitalWrite(CLK,LOW);
      digitalWrite(CLK,HIGH);
      digitalWrite(13,HIGH);
      delay(1);
   }
}
//Funcion que hace funcionar al Registro de Desplazamiento 74164
void desplazamiento(int dato, int posicion){
   if(posicion == 0){
       if(dato== 0)
          digitalWrite(RD1,LOW);
       else
          digitalWrite(RD1,HIGH);
   }
   else  if(posicion == 1){
       if(dato== 0)
          digitalWrite(RD2,LOW);
       else
          digitalWrite(RD2,HIGH);
   }
   else  if(posicion == 2){
       if(dato== 0)
          digitalWrite(RD3,LOW);
       else
          digitalWrite(RD3,HIGH);
   }
   else{
       if(dato== 0)
          digitalWrite(RD4,LOW);
       else
          digitalWrite(RD4,HIGH);
   }
}
void sumar(int lado){
   if(lado==0){
      if(CambioI == 1){
         if(MarcadorI < tope1 || MarcadorI < tope2){
            MarcadorI += 1;
            marcador[0] = MarcadorI/10;
            marcador[1] = MarcadorI%10;
         }
      }
      else{
         CambioD = 0;
         digitalWrite(LEDD,LOW);
         CambioI = 1;
         digitalWrite(LEDI,HIGH);
      }
   }
   else{
      if(CambioD == 1){
         if(MarcadorD < tope1 || MarcadorD < tope2){
            MarcadorD += 1;
            marcador[2] = MarcadorD/10;
            marcador[3] = MarcadorD%10;
         }
      }
      else{
         CambioI = 0;
         digitalWrite(LEDI,LOW);
         CambioD = 1;
         digitalWrite(LEDD,HIGH);
      }
   }
   //Validar  con el Tope
   if(setI + setD <2){
      if(MarcadorI == tope1 || MarcadorD == tope1){
         if(lado == 0){
            setI += 1;
            CambioD = 1;
            CambioI = 0;
            }
         else{
            setD += 1;
            CambioD = 0;
            CambioI = 1;
         }
         marcador[0] = 0;
         marcador[1] = 0;
         marcador[2] = 0;
         marcador[3] = 0;
         MarcadorI = 0;
         MarcadorD = 0;
      }
   }
   else{
      if(MarcadorI == tope2 || MarcadorD == tope2 ){
         if(lado == 0)
            setI += 1;
         else
            setD += 1;
         marcador[0] = 0;
         marcador[1] = 0;
         marcador[2] = 0;
         marcador[3] = 0;
         MarcadorI = 0;
         MarcadorD = 0;
      }
   }
   Serial.print("MarcadorI: ");Serial.println(MarcadorI);
   Serial.print("MarcadorD: ");Serial.println(MarcadorD);
   mostrar();
}
void restar(int lado){
   if(lado==0){
      if(MarcadorI>0){
         MarcadorI -= 1;
         marcador[0] = MarcadorI/10;
         marcador[1] = MarcadorI%10;
         mostrar();
      }
   }
   else{
      if(MarcadorD>0){
         MarcadorD -= 1;
         marcador[2] = MarcadorD/10;
         marcador[3] = MarcadorD%10;
         mostrar();
      }
   }
   
}



