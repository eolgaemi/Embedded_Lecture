#include <stdio.h>

// const �� ���� Runtime Error�� �߻��� ���
// ���ڿ� ����� �����ϸ� �Ȱ��� �ּҸ� ������
// fruit�� �����. ������ ��ü�� �����, ������ ������ ����
// �����ʹ� �޸��� �ּҸ� ���� �� ���� ���
// �������� ������ ��ȣ X, �ڵ� �����ϱ� ���� ������
// �߿���� �ü���� ���� ������ �������� �����
// static ���α׷� ���� �ÿ� �ٷ� Data ������ ����
// malloc�� ���α׷� ���� �ÿ� �޸� �Ҵ�
// ���� ����(����)�� ��� auto�� ������
// CPU�� ������ ������ RAM�� �� �ּ��� D31~D0�� 1��1�� ����
// CPU ���� ������ 32bit=4byte=integer -> Data align�� �ȵǸ� -> �ð��� 2��ɸ�
// �޸� ���� <-> ����ӵ� ���� ������
// ������ ��´ٴ� �� �ּҸ� ��� �޸� �Ҵ��� �̸� �����Ű� �ڷ����� �Ҵ� �� �޸��� ũ��
// �����ʹ� 4byte��! char* �� 1����Ʈ�� ����Ű�� �����͸� ����
// �ڵ�� �������� �߿�! 
// ASCII 0x30 �� 0
// ASCII 0x41 �� A      0x61 �� a
// ASCII 0x0A �� LF     0x0A �� CR

void strcat1(char* str1, const char* str2);
char* strcat2(char* str1, const char* str2);

int main(int argc, char* argv[])
{
    char fruit_1[80] = "Straw";
    printf("Straw address : %p", "Straw");
    char fruit_2[80] = "Rasp";
    strcat1(fruit_1, "berry");
    strcat2(fruit_2, "berry");
    printf("result_1 : %s\n", fruit_1);
    printf("result_2 : %s\n", fruit_2);
    printf("berry address : %p", "berry");
    return 0;
}

void strcat1(char* str1, const char* str2){

    // \'0'�� ����� ���� ���� ++ �ϰ� �˻� �ؼ� '\0'�� �ּҸ� ��
    while(*(++str1)!='\0');

    // '\0'�� �ּ� ���� str2�� ���� �ϴ� �ְ� ����
    // �׷� '\0'�� ���� ������
    while((*str1 = *(str2++))!='\0'){
        str1++;
    }
}

char* strcat2(char* str1, const char* str2) {

    // strcat1���� 32bit OS = 4byte , 64bit OS = 8byte
    // ���� �� 
    char* str_start = str1;

    while (*str1 != '\0') {
        str1++;
    }

    while (*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++;
    }

    // �̷��� pointer������ return �� ����
    // 1. static���� ���� �� �� ��
    // 2. �Ű������� �ּҸ� return�� ��
    // �� ���� ��쿡�� ����
    // 3. ���������� return �ϴ� �� �ǹ̾���
    return str_start;
}

