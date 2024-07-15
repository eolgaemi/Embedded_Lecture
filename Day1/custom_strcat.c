#include <stdio.h>

// const 안 쓰면 Runtime Error가 발생할 우려
// 문자열 상수는 동일하면 똑같은 주소를 리턴함
// fruit은 상수임. 포인터 자체는 상수고, 포인터 변수가 따로
// 포인터는 메모리의 주소를 저장 해 놓은 상수
// 전역변수 데이터 보호 X, 코드 수정하기 빡셈 쓰지마
// 펌웨어는 운영체제가 없기 때문에 전역변수 써야함
// static 프로그램 실행 시에 바로 Data 영역에 잡힘
// malloc은 프로그램 실행 시에 메모리 할당
// 지역 변수(스택)는 모두 auto가 생략됨
// CPU의 데이터 버스는 RAM의 한 주소의 D31~D0과 1대1로 연결
// CPU 최적 데이터 32bit=4byte=integer -> Data align이 안되면 -> 시간이 2배걸림
// 메모리 절약 <-> 실행속도 개선 딜레마
// 변수를 잡는다는 건 주소를 잡고 메모리 할당해 이름 넣은거고 자료형은 할당 될 메모리의 크기
// 포인터는 4byte다! char* 는 1바이트를 가리키는 포인터를 저장
// 코드는 가독성이 중요! 
// ASCII 0x30 은 0
// ASCII 0x41 은 A      0x61 은 a
// ASCII 0x0A 은 LF     0x0A 은 CR

void strcat1(char* str1, const char* str2);
char* strcat2(char* str1, const char* str2);

int main(int argc, char* argv[])
{
    char fruit_1[80] = "Straw";
    printf("Straw address : %p\n", "Straw");
    char fruit_2[80] = "Rasp";
    strcat1(fruit_1, "berry");
    strcat2(fruit_2, "berry");
    printf("result_1 : %s\n", fruit_1);
    printf("result_2 : %s\n", fruit_2);
    printf("berry address : %p\n", "berry");
    return 0;
}

void strcat1(char* str1, const char* str2){

    // \'0'을 지우기 위해 먼저 ++ 하고 검사 해서 '\0'의 주소를 겟
    while(*(++str1)!='\0');

    // '\0'의 주소 부터 str2의 값을 일단 넣고 증가
    // 그럼 '\0'이 덮어 씌워짐
    while((*str1 = *(str2++))!='\0'){
        str1++;
    }
}

char* strcat2(char* str1, const char* str2) {

    // strcat1보다 32bit OS = 4byte , 64bit OS = 8byte
    // 많이 씀 
    char* str_start = str1;

    while (*str1 != '\0') {
        str1++;
    }

    while (*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++;
    }

    // 이렇게 pointer변수를 return 할 때는
    // 1. static으로 잡은 것 일 때
    // 2. 매개변수의 주소를 return할 때
    // 두 가지 경우에서 수행
    // 3. 전역변수는 return 하는 게 의미없음
    return str_start;
}

