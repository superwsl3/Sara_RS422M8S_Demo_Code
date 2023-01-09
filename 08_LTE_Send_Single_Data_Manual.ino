/**************************************************************************************************************************************************************************
1.修改日期:2022/11/23
2.程式功能:
           (1).透過LTE發送單筆資料至IOT智慧聯網大平台
3.硬    體:
           (1).LTE
           (2).Mega2560開發版                                                             
4.線路連接:
           (1).LTE   :Serial1
           (2).Debug :Serial
5.指令說明:
           (1).AT+UHTTP=0                                                                                        //LTE設定Reset                      
           (2).AT+UHTTP=0,1,"iot.cht.com.tw"                                                                     //設定server 網址
           (3).AT+UHTTP=0,5,80                                                                                   //設定server Port
           (4).AT+UHTTP=0,9,"0:CK:PK2KT7K9MGRM4T4G9A"                                                            //設定http header格式
           (5).AT+UHTTP=0,9,"1:Content-Type: application/json"                                                   //設定傳送資料格式為Jason
           (6).AT+UDWNFILE="send.txt",35                                                                         //設定寫入jason檔案內容35個bytes(1)
           (7).[{"id":"station_1","value":["41"]}]                                                               //設定jason格式內容(2)
           (8).AT+URDFILE="send.txt"                                                                             //讀取EE檔案-確認讀取傳送jason檔案內容
           (9).AT+UHTTPC=0,4,"http://iot.cht.com.tw/iot/v1/device/32199934092/rawdata","result.txt","send.txt",0 //POST 資料給IOT
          (10).AT+URDFILE="result.txt"                                                                           //讀取IOT_Response結果
          (11).AT+UDELFILE="send.txt","USER"                                                                     //刪除前次檔案
          (12).AT+URDFILE="send.txt"                                                                             //讀取EE檔案-先確認傳送jason檔案內容(內容為空才執行下列(2)和(3))
          (13).AT+UHTTP=0,1                                                                                      //讀取server網址(確認用)
          (14).AT+UHTTP=2,5                                                                                      //讀取server Port(確認用) 
**************************************************************************************************************************************************************************/
//--Variable--//
unsigned char Communicate_Flag=0;
char Command_Data=0;
char Response_Data=0;                                                                                                           
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  if(Communicate_Flag==1){
    Communicate_Flag=0;
    Serial1.write(Command_Data);
  }else if(Communicate_Flag==2){
    Communicate_Flag=0;
    Serial.print(Response_Data);
  }
}
void LTE_Send_Command(void)
{
  while(Serial.available()){
    Command_Data= Serial.read();
  }
  Communicate_Flag=1;
}

void LTE_Rece(void)
{
  while(Serial1.available()){
    Response_Data= Serial1.read();
  }
  Communicate_Flag=2;
}
void serialEvent() {
  LTE_Send_Command();
}
void serialEvent1(){
  LTE_Rece();
}
