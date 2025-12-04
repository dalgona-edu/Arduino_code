/*
 * 프로젝트 : 5-1 랜덤 숫자 추리 게임기
 * 동작설명
 * - 1~9 사이의 자연수 값으로 랜덤한 숫자가 정해집니다
 * - UP, DOWN, Enter 3가지의 버튼으로 게임기를 조종합니다
 * - UP,DOWN 버튼으로 숫자값을 조절한 후, Enter 버튼으로 정답을 맞춥니다
 * - 정답이 아니라면, 부저에서 짧은 소리가 한번, 정답이 맞다면, 노래소리가 나옵니다
 */

#define SW_UP_PIN    2        // 버튼 UP
#define SW_DW_PIN    3        // 버튼 DOWN
#define SW_ST_PIN    4        // 버튼 Enter
#define BUZZ_PIN     5        // 부저(Passive)
#define LED_A_PIN    9        // 3색 LED -> UP
#define LED_B_PIN   10        // 3색 LED -> START
#define LED_C_PIN   11        // 3색 LED -> DOWN

#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 

int tempo[] = {200, 300, 200, 300, 200, 300, 200, 300, 200, 300, 200, 300, 200, 300, 200, 300, 200, 300, 200, 300, 200, 300, 200, 300}; // duration 옵션 값 설정 
int notes[] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C }; 

int answer = 1;
int randomNumber = 0;

void setup() 
{
    pinMode(SW_UP_PIN, INPUT);    // 디지털 - 입력
    pinMode(SW_DW_PIN, INPUT);    // 디지털 - 입력
    pinMode(SW_ST_PIN, INPUT);    // 디지털 - 입력
    pinMode(BUZZ_PIN, OUTPUT);    // 디지털 - 출력
    pinMode(LED_A_PIN, OUTPUT);   // 디지털 - 출력
    pinMode(LED_B_PIN, OUTPUT);   // 디지털 - 출력
    pinMode(LED_C_PIN, OUTPUT);   // 디지털 - 출력
    randomSeed(analogRead(0));

    Serial.begin(9600);
    Serial.println("Welcome, DALGONA.edu~");

    randomNumber = random(1, 10); //1~9
    Serial.println("1부터 9까지의 랜덤 숫자를 맞춰보세요~");
}

void loop() 
{
    Serial.println(randomNumber);
    Serial.println(answer);
    if(digitalRead(SW_UP_PIN) == 0)
    {
        if(answer < 9)
        {
            answer++;
            Serial.println("1만큼 커졌어요!");
        }
        else
        {
            Serial.println("숫자는 9까지 커질 수 있어요!");
        }
        LED(1);
        tone (BUZZ_PIN, 392); 
        delay(700);
        noTone(BUZZ_PIN);
    }

    if(digitalRead(SW_DW_PIN) == 0)
    {
        if(answer > 1)
        {
            answer--;
            Serial.println("1만큼 작아졌어요!");
        }
        else
        {
            Serial.println("숫자는 1까지 작아질 수 있어요!");
        }
        LED(3);
        tone (BUZZ_PIN, 262);
        delay(700);
        noTone(BUZZ_PIN);
    }
    if(digitalRead(SW_ST_PIN) == 0)
    {
        LED(2);
        if(answer == randomNumber) // 정답
        {
            Serial.println("");
            end_buzzer();
            randomNumber = random(1, 10);
        }
        else
        {
            if(answer > randomNumber) // 정답보다 숫자가 큰 경우
            {
                Serial.println("정답은 더 작은 숫자에요!");
                tone (BUZZ_PIN, 262, 100); 
            }
            else // 정답보다 숫자가 작은 경우
            {
                Serial.println("정답은 더 큰 숫자에요!");
                tone (BUZZ_PIN, 392, 100); 
            }
        }
        delay(700);
    }
}

void LED(int temp)
{
    for(int i=9; i<12; i++) 
        digitalWrite(i, LOW);
    if(temp == 1)      
        digitalWrite(LED_A_PIN, HIGH);  // UP
    else if(temp == 2) 
        digitalWrite(LED_B_PIN, HIGH);  // START
    else if(temp == 3) 
        digitalWrite(LED_C_PIN, HIGH);  // DOWN
    else;
}

void end_buzzer()
{
    for (int i = 0; i < 12; i++) 
    { 
        tone (BUZZ_PIN, notes[ i ], tempo[ i ]); 
        delay (tempo[ i ]); 
    } 
    delay(100); // 멜로디 중간에 짧게 멈추는 용도 

    for (int i = 12; i < 24; i++) 
    { 
        tone (BUZZ_PIN, notes[ i ], tempo[ i ]); 
        delay(tempo[ i ]); 
    }
    noTone(BUZZ_PIN); 
}
