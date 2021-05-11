void main()
{
//VARIAVEIS
int cnt;
short minutos,segundos;
char m1,m2,s1,s2;
bit start,oldstate1,oldstate2;
char numeros[10] = {63,6,91,79,102,109,125,7,127,111};//7 segmentos CC
//ROTINA DE INTERRPÇÃO
void interrupt(){
TMR0 = 155;
cnt++;
INTCON.T0IF=0; //flag de interrpção
}
void main() {
//CONFIGURAÇÃO DOS REGISTROS
CMCON = 0b11111111;//desliga comparador analogico
OPTION_REG=0b00000001; //configura timer0
INTCON.GIE=1;  //habilita interrupcap global
INTCON.T0IE=1; //habilita interrupcao do timer0
TMR0=155;
TRISB=0b00000000;
TRISA=0b00011111;//pino RA4 definido como entrada.
//DEFINIÇÃO DE VALOR DAS VARIÁVEIS
segundos=0;
minutos=0;
//BIT DE STATUS
start=0;
oldstate1=0;
oldstate2=0;
while(1){
 if(cnt>=2500){
  cnt=0;
        if(start){
        segundos--;
        if(segundos<0){
                  segundos=59;
                  minutos--;
                  if(minutos<0){
                               TRISA.F4=0; //define pino RA4 como saída
                               PORTA.F4=1; //tanto faz o valor, o q queremos e //aterrar a base do transistor.
                               minutos=0;
                               segundos=0;
                               start=0;
                               }
                  }
        }
 }
//........AJUSTE DOS SEGUNDOS/MINUTOS..............
if(!PORTA.F1){//.........SEGUNDOS...........
if(PORTA.F0){
 oldstate1=1;
 }
 if(!PORTA.F0 && oldstate1){
              oldstate1=0;
              segundos++;
              if(segundos==60) segundos=0;
}
}else{//.................MINUTOS............
 if(PORTA.F0){
 oldstate1=1;
 }
 if(!PORTA.F0 && oldstate1){
              oldstate1=0;
              minutos++;
              if(minutos==60) minutos=0;
}
}
//..........START/PAUSE............
if(PORTA.F2){
              oldstate2=1;
}
if(!PORTA.F2 && oldstate2){
             oldstate2=0;
             start = ~start;
}
//DIGITOS
m1 = minutos/10;
m2 = minutos%10;
s1 = segundos/10;
s2 = segundos%10;
//DISPLAY DE 7 SEGMENTOS
if(PORTA.F1==0){
PORTA=0b01000000;
PORTB=numeros[s2];
delay_ms(1);
PORTA=0b10000000;
PORTB=numeros[s1];
delay_ms(1);
}else{
PORTA=0b01000000;
PORTB=numeros[m2];
delay_ms(1);
PORTA=0b10000000;
PORTB=numeros[m1];
delay_ms(1);
}
}
}
