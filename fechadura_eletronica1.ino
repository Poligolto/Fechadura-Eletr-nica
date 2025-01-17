/* Programa: Fechadura Eletrônica */
/* Inclui a biblioteca de controle do teclado */
#include <Keypad.h>
/* Inclui a biblioteca do servo motor */
#include<Servo.h>
/* Cria um objeto servo para controle do servo */
Servo servo1;
/* Senha para destrancar a fechadura */
char* password = "123";
/* Quantidade de caracteres que a senha possui */
int caracteres = 3;
/* Pinos que estão conectados os LEDs */
const int ledVermelho = 11;
const int ledVerde = 12;
/* Pino que está conectado o servo */
const int Pin_Servo = 10;
/* Variável para leitura de posição da tecla
pressionada */
int posicao = 0;
/* Define o número de linhas e colunas do teclado */
const byte N_Lin = 4;
const byte N_Col = 4;
/* Construção da matriz de caracteres */
char m_tec[N_Lin][N_Col] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
/* Pinos utilizados pelas linhas e colunas do teclado
*/
byte Pin_Lin[N_Lin] = {9, 8, 7, 6};
byte Pin_Col[N_Col] = {5, 4, 3, 2};
/* Inicializa o teclado */
Keypad tec = Keypad( makeKeymap(m_tec), Pin_Lin, Pin_Col, N_Lin,
N_Col);
void setup() {
/* Configura os pinos dos LEDs como saída */
pinMode(ledVermelho, OUTPUT);
pinMode(ledVerde, OUTPUT);
/* Define o pino de dados para o servo */
servo1.attach(Pin_Servo);
/* Define a velocidade de comunicação serial em 9600
 bauds */
Serial.begin(9600);
/* Imprime no monitor serial o texto entre aspas */
Serial.println("Entre com a senha...");
/* Quebra uma linha no monitor serial */
Serial.println();
/* Inicia com a fechadura trancada */
trancada();
servo1.write(90);
}
void loop() {
/* Captura a tecla pressionada*/
char key = tec.getKey();
/* Se a tecla pressionada for “*” ou “#” reinicia a
 tentativa com a fechadura trancada */
if (key == '*' || key == '#') {
 posicao = 0;
 trancada();
}
/* Se as teclas pressionadas coincidirem com a
 senha, destranque a fechadura */
 if (key == password[posicao]) {
 posicao ++;
}
if (posicao == caracteres) {
 destrancada();
}
/* Pequena pausa para retomar a leitura */
delay(100);
}
/* Função que mantém a fechadura trancada */
void trancada()
{
/* LED Vermelho acende */
digitalWrite(ledVermelho, HIGH);
/* LED Verde apaga */
digitalWrite(ledVerde, LOW);
/* Servo na posição trancada */
servo1.write(90);
/* Imprime no monitor serial que a fechadura está
 TRANCADA */
Serial.println("TRANCADA");
}
/* Função que mantém a fechadura destrancada */
void destrancada()
{
/* LED Verde acende */
digitalWrite(ledVerde, HIGH);
/* LED Vermelho apaga */
digitalWrite(ledVermelho, LOW);
/* Servo na posição destrancada */
servo1.write(180);
/* Imprime no monitor serial que a fechadura está
 ABERTA */
Serial.println("ABERTA");
}