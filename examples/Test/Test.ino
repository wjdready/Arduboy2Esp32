const int buttonPin = 16; //连接按键的数字端口编号
const int ledPin = 2; //连接LED的数字端口编号

//定义随按键状态而改变的变量
int buttonState = 0;

void setup() {
  //初始化LED驱动端口为输出
  pinMode(ledPin, OUTPUT);
  //初始化按键端口为输入
  pinMode(buttonPin, INPUT);
}

void loop(){
  //读取按键端口状态
  buttonState = digitalRead(buttonPin);

  //检测按键是否被按下
  //如果是，变量buttonState为常量值 HIGH:
  if (buttonState == HIGH) {
    //打开LED:
    digitalWrite(ledPin, HIGH);
}
else {
  //熄灭LED
  digitalWrite(ledPin, LOW);
  }
}