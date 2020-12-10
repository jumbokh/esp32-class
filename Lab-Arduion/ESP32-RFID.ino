#include <MFRC522.h> //biblioteca responsável pela comunicação com o módulo RFID-RC522
#include <SPI.h> //biblioteca para comunicação do barramento SPI

#define SS_PIN    21
#define RST_PIN   22

#define SIZE_BUFFER     18
#define MAX_SIZE_BLOCK  16

#define pinVerde     12
#define pinVermelho  32

//esse objeto 'chave' é utilizado para autenticação
MFRC522::MIFARE_Key key;
//código de status de retorno da autenticação
MFRC522::StatusCode status;

// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() {
  // Inicia a serial
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus

  pinMode(pinVerde, OUTPUT);
  pinMode(pinVermelho, OUTPUT);
  
  // Inicia MFRC522
  mfrc522.PCD_Init(); 
  // Mensagens iniciais no serial monitor
  Serial.println("將您的卡靠近讀卡機....");
  Serial.println();

}

void loop() 
{
   // Aguarda a aproximacao do cartao
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

    // Dump debug info about the card; PICC_HaltA() is automatically called
//  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  //chama o menu e recupera a opção desejada
  int opcao = menu();
   // verifica se ainda está com o cartão/tag
//  if ( ! mfrc522.PICC_IsNewCardPresent()) 
//  {
//    return;
//  }
  
  if(opcao == 0) 
    leituraDados();
  else if(opcao == 1) 
    gravarDados();
  else {
    Serial.println(F("選項錯誤!"));
    return;
  }
 
  //指示 PICC 在活動狀態下進入"停止"狀態
  mfrc522.PICC_HaltA(); 
  // 與身份驗證通信之後，必須調用“停止” PCD加密，否則無法啟動新的通信
  mfrc522.PCD_StopCrypto1();  
}

//faz a leitura dos dados do cartão/tag
void leituraDados()
{
  //打印卡/標籤的技術細節
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); 

  //準備密鑰-所有密鑰均設置為FFFFFFFFFFFFh（出廠默認設置）。
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //緩衝區以放置數據
  byte buffer[SIZE_BUFFER] = {0};

  //阻止我們進行操作
  byte bloco = 1;
  byte tamanho = SIZE_BUFFER;


  //對我們將要操作的塊進行身份驗證
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, bloco, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    digitalWrite(pinVermelho, HIGH);
    delay(1000);
    digitalWrite(pinVermelho, LOW);
    return;
  }

  //讀取塊數據
  status = mfrc522.MIFARE_Read(bloco, buffer, &tamanho);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    digitalWrite(pinVermelho, HIGH);
    delay(1000);
    digitalWrite(pinVermelho, LOW);
    return;
  }
  else{
      digitalWrite(pinVerde, HIGH);
      delay(1000);
      digitalWrite(pinVerde, LOW);
  }

  Serial.print(F("\nData block ["));
  Serial.print(bloco);Serial.print(F("]: "));

  //打印讀取的數據
  for (uint8_t i = 0; i < MAX_SIZE_BLOCK; i++)
  {
      Serial.write(buffer[i]);
  }
  Serial.println(" ");
}

//faz a gravação dos dados no cartão/tag
void gravarDados()
{
  //imprime os detalhes tecnicos do cartão/tag
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); 
  // aguarda 30 segundos para entrada de dados via Serial
  Serial.setTimeout(30000L) ;     
  Serial.println(F("Insira os dados a serem gravados com o caractere '#' ao final\n[máximo de 16 caracteres]:"));

  //Prepara a chave - todas as chaves estão configuradas para FFFFFFFFFFFFh (Padrão de fábrica).
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //buffer para armazenamento dos dados que iremos gravar
  byte buffer[MAX_SIZE_BLOCK] = "";
  byte bloco; //bloco que desejamos realizar a operação
  byte tamanhoDados; //tamanho dos dados que vamos operar (em bytes)

  //recupera no buffer os dados que o usuário inserir pela serial
  //serão todos os dados anteriores ao caractere '#'
  tamanhoDados = Serial.readBytesUntil('#', (char*)buffer, MAX_SIZE_BLOCK);
  //espaços que sobrarem do buffer são preenchidos com espaço em branco
  for(byte i=tamanhoDados; i < MAX_SIZE_BLOCK; i++)
  {
    buffer[i] = ' ';
  }
 
  bloco = 1; //bloco definido para operação
  String str = (char*)buffer; //transforma os dados em string para imprimir
  Serial.println(str);

  //Authenticate é um comando para autenticação para habilitar uma comuinicação segura
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                                    bloco, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    digitalWrite(pinVermelho, HIGH);
    delay(1000);
    digitalWrite(pinVermelho, LOW);
    return;
  }
  //else Serial.println(F("PCD_Authenticate() success: "));
 
  //Grava no bloco
  status = mfrc522.MIFARE_Write(bloco, buffer, MAX_SIZE_BLOCK);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    digitalWrite(pinVermelho, HIGH);
    delay(1000);
    digitalWrite(pinVermelho, LOW);
    return;
  }
  else{
    Serial.println(F("MIFARE_Write() success: "));
    digitalWrite(pinVerde, HIGH);
    delay(1000);
    digitalWrite(pinVerde, LOW);
  }
 
}

//menu para escolha da operação
int menu()
{
  Serial.println(F("\nEscolha uma opção:"));
  Serial.println(F("0 - Leitura de Dados"));
  Serial.println(F("1 - Gravação de Dados\n"));

  //fica aguardando enquanto o usuário nao enviar algum dado
  while(!Serial.available()){};

  //recupera a opção escolhida
  int op = (int)Serial.read();
  //remove os proximos dados (como o 'enter ou \n' por exemplo) que vão por acidente
  while(Serial.available()) {
    if(Serial.read() == '\n') break; 
    Serial.read();
  }
  return (op-48);//do valor lido, subtraimos o 48 que é o ZERO da tabela ascii
}
