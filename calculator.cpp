#include <stdio.h>
#include <stdlib.h>

void input_num(float* pary_num, char* pary_simbol, int num); // 입력
void print_value(float* pary_num, char* pary_simbol, int num, float value_num); // 출력
float calculation(float* pary_num, char* pary_simbol, int num); // 연산

int main(void) 
{
    float* pary_num; // 입력된 숫자
    char* pary_simbol; // 기호 저장
    int num = 0; // 연산에 쓰일 숫자의 개수
    char ch; // (Y/N)

    while (1) {
        printf("연산을 실행하시겠습니까?(Y/N) ");
        scanf_s(" %c", &ch, 1); // %c 앞에 공백 추가하여 남은 개행 문자를 소비, 그리고 크기를 추가

        switch (ch) 
        {
        case 'y':
        case 'Y':
            printf("연산에 사용할 숫자의 개수를 입력해 주세요\n");
            scanf_s("%d", &num);
            if (num > 0) 
            {
                pary_num = (float*)malloc(num * sizeof(float));
                pary_simbol = (char*)malloc(num * sizeof(char));
                if (pary_num == NULL || pary_simbol == NULL) 
                {
                    printf("메모리 할당에 실패하였습니다\n");
                    return 1;
                }
                input_num(pary_num, pary_simbol, num);
                free(pary_num);
                free(pary_simbol);
            }
            else 
            {
                printf("연산에 사용될 수는 양의 정수여야 합니다\n문자열이나 0 이하의 수는 입력하지 마세요.\n");
            }
            break;
        case 'n':
        case 'N':
            printf("연산을 종료합니다.\n");
            return 0; // 프로그램 종료
        default:
            printf("Y 또는 N 중에서 입력해주세요\n");
            break;
        }
    }

    return 0;
}

void input_num(float* pary_num, char* pary_simbol, int num) 
{
    for (int i = 0; i < num; i++) 
    {
        printf("숫자를 입력하세요\n");
        scanf_s("%f", &pary_num[i]);
        if (i < num - 1) 
        {
            printf("연산 기호를 입력하세요\n");
            scanf_s(" %c", &pary_simbol[i], 1); // %c 앞에 공백 추가하여 남은 개행 문자를 소비, 그리고 크기를 추가

            switch (pary_simbol[i]) 
            {
            case '+':
            case '-':
            case '*':
            case '/':
                break;
            default:
                printf(" '+', '-', '*', '/' 중에서 입력하세요\n");
                i--; // 올바른 기호를 받을 때까지 반복
                break;
            }
        }
    }

    float result = calculation(pary_num, pary_simbol, num);
    print_value(pary_num, pary_simbol, num, result);
}

float calculation(float* pary_num, char* pary_simbol, int num) 
{
    // 임시 배열을 사용하여 중간 결과를 저장
    float* temp_num = (float*)malloc(num * sizeof(float));
    char* temp_simbol = (char*)malloc(num * sizeof(char));

    for (int i = 0; i < num; i++) 
    {
        temp_num[i] = pary_num[i];
        temp_simbol[i] = pary_simbol[i];
    }

    // 1단계: 곱셈과 나눗셈 처리
    for (int i = 0; i < num - 1; i++) 
    {
        if (temp_simbol[i] == '*' || temp_simbol[i] == '/') 
        {
            if (temp_simbol[i] == '*') 
            {
                temp_num[i] = temp_num[i] * temp_num[i + 1];
            }
            else {
                if (temp_num[i + 1] != 0) 
                {
                    temp_num[i] = temp_num[i] / temp_num[i + 1];
                }
                else 
                {
                    printf("0으로 나눌 수 없습니다.\n");
                    free(temp_num);
                    free(temp_simbol);
                    exit(1);
                }
            }
            // 다음 숫자를 현재 숫자와 병합했으므로 다음 숫자를 건너뜁니다.
            for (int j = i + 1; j < num - 1; j++) 
            {
                temp_num[j] = temp_num[j + 1];
                temp_simbol[j - 1] = temp_simbol[j];
            }
            num--;
            i--; // 현재 위치를 다시 검사합니다.
        }
    }

    // 2단계: 덧셈과 뺄셈 처리
    float value_num = temp_num[0];
    for (int i = 1, j = 0; i < num; i++, j++) 
    {
        if (temp_simbol[j] == '+') 
        {
            value_num += temp_num[i];
        }
        else if (temp_simbol[j] == '-') 
        {
            value_num -= temp_num[i];
        }
    }

    free(temp_num);
    free(temp_simbol);

    return value_num;
}

void print_value(float* pary_num, char* pary_simbol, int num, float value_num) 
{
    for (int i = 0; i < num - 1; i++) 
    {
        printf("%g %c ", pary_num[i], pary_simbol[i]);
    }
    printf("%g = %g\n", pary_num[num - 1], value_num);
}
