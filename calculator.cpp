#include <stdio.h>
#include <stdlib.h>

void input_num(float* pary_num, char* pary_simbol, int num); // 입력
void print_value(float* pary_num, char* pary_simbol, int num, float value_num); // 출력
float calculation(float* pary_num, char* pary_simbol, int num); // 연산

int main(void) {
    float* pary_num; // 입력된 숫자
    char* pary_simbol; // 기호 저장
    int num = 0; // 연산에 쓰일 숫자의 개수
    char ch; // (Y/N)

    while (1) {
        printf("연산을 실행하시겠습니까?(Y/N) ");
        scanf_s(" %c", &ch, 1); // %c 앞에 공백 추가하여 남은 개행 문자를 소비, 그리고 크기를 추가

        switch (ch) {
        case 'y':
        case 'Y':
            printf("연산에 사용할 숫자의 개수를 입력해 주세요\n");
            scanf_s("%d", &num);
            if (num > 0) {
                pary_num = (float*)malloc(num * sizeof(float));
                pary_simbol = (char*)malloc((num - 1) * sizeof(char));
                if (pary_num == NULL || pary_simbol == NULL) {
                    printf("메모리 할당에 실패하였습니다\n");
                    return 1;
                }
                input_num(pary_num, pary_simbol, num);
                free(pary_num);
                free(pary_simbol);
            }
            else {
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

void input_num(float* pary_num, char* pary_simbol, int num) {
    for (int i = 0; i < num; i++) {
        printf("숫자를 입력하세요\n");
        scanf_s("%f", &pary_num[i]);
        if (i < num - 1) {
            printf("연산 기호를 입력하세요\n");
            scanf_s(" %c", &pary_simbol[i], 1); // %c 앞에 공백 추가하여 남은 개행 문자를 소비, 그리고 크기를 추가

            switch (pary_simbol[i]) {
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

float calculation(float* pary_num, char* pary_simbol, int num) {
    // 임시 배열을 사용하여 중간 결과를 저장
    float* temp_num = (float*)malloc(num * sizeof(float));
    char* temp_simbol = (char*)malloc((num - 1) * sizeof(char));

    for (int i = 0; i < num; i++) {
        temp_num[i] = pary_num[i];
    }
    for (int i = 0; i < num - 1; i++) {
        temp_simbol[i] = pary_simbol[i];
    }

    // 1단계: 곱셈과 나눗셈 처리
    for (int i = 0; i < num - 1; i++) {
        if (temp_simbol[i] == '*' || temp_simbol[i] == '/') {
            if (temp_simbol[i] == '*') {
                temp_num[i] = temp_num[i] * temp_num[i + 1];
            }
            else {
                if (temp_num[i + 1] != 0) {
                    temp_num[i] = temp_num[i] / temp_num[i + 1];
                }
                else {
                    printf("0으로 나눌 수 없습니다.\n");
                    free(temp_num);
                    free(temp_simbol);
                    exit(1);
                }
            }
            // 다음 숫자를 현재 숫자와 병합했으므로 다음 숫자를 건너뜁니다.
            for (int j = i + 1; j < num - 1; j++) {
                temp_num[j] = temp_num[j + 1];
                temp_simbol[j - 1] = temp_simbol[j];
            }
            num--;
            i--; // 현재 위치를 다시 검사합니다.
        }
    }

    // 2단계: 덧셈과 뺄셈 처리
    float value_num = temp_num[0];
    for (int i = 1, j = 0; i < num; i++, j++) {
        if (temp_simbol[j] == '+') {
            value_num += temp_num[i];
        }
        else if (temp_simbol[j] == '-') {
            value_num -= temp_num[i];
        }
    }

    free(temp_num);
    free(temp_simbol);

    return value_num;
}

void print_value(float* pary_num, char* pary_simbol, int num, float value_num) {
    for (int i = 0; i < num - 1; i++) {
        printf("%g %c ", pary_num[i], pary_simbol[i]);
    }
    printf("%g = %g\n", pary_num[num - 1], value_num);
}



//#include<stdio.h>
//#include<stdlib.h>
//
//void calculation(float* pary_num, char* pary_simbol,int &num);
//void print_value(float* pary_num, char* pary_simbol, int& num, float* value_num);
////함수선언
//
//int main(void)
//{
//	float* pary_num;//입력된 숫자
//	char* pary_simbol;//기호 저장
//	int num = 0;
//	char ch;
//	int temp;//가비지값 저장
//
//	while (1)
//	{
//		printf("연산을 실행하시겠습니까?(Y/N)");
//
//		temp = scanf("%c", &ch);
//
//		switch (ch)
//		{
//		case 'y':
//		case 'Y':
//			printf("연산에 사용할 숫자의 개수를 입력해 주세요\n");
//			scanf_s("%d", &num, sizeof(int));
//			if (num >= 0)
//			{
//				pary_num = (float*)malloc(num * sizeof(float));
//				pary_simbol = (char*)malloc(num * sizeof(char));
//				if (pary_num == NULL || pary_simbol == NULL);
//				{
//					printf("메모리 할당에 실패하였습니다");
//					return 1;
//				}
//				calculation(pary_num, pary_simbol, &num)
//			}
//			else
//				printf("연산에 사용될 수는 양의 정수여야 합니다\n문자열이나 0 이하의 수는 입력하지 마세요.\n");
//			break;
//		case 'n':
//		case 'N':
//			printf("연산을 종료합니다.");
//			break;
//		default:
//			printf("Y 또는 N중에서 입력해주세요");
//			break;
//		}
//	}
//
//	return 0;
//}
//
//void calculation(float* pary_num, char* pary_simbol, int& num)
//{
//	float value_num = 0;//연산 결과값
//	for (int i = 0; i < num; i++)
//	{
//		printf("숫자를 입력하세요\n");
//		scanf("%f", *pary_num[i]);
//		printf("연산 기호를 입력하세요\n");
//		scanf("%c", *pary_simbol[i]);
//		switch (*pary_simbol[i])
//		{
//		case '+':
//		case '-':
//		case '*':
//		case '/':
//			break;
//		defailt:
//			printf(" '+', '-', '*', '/' 중에서 입력하세요");
//		}
//	}
//
//	for (int i = 0; i < num; i++)
//	{
//		//value_num값 구함
//	}
//	print_value(* pary_num, * pary_simbol, & num, * value_num);
//}
//
//void print_value(float* pary_num, char* pary_simbol, int& num, float* value_num)
//{
//	for (int i = 0; i < (num * 2); i++)
//	{
//		i & 1 = 1 ? printf("%g", *pary_num[i]) : printf("%c", *pary_simbol[i]);
//	}
//	printf("=%g", float* value_num);
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//// 함수 선언
//void operate_arith(float* pary, char* operators, int n);
//
//int main(void)
//{
//    float* pary;
//    char* operators;
//    int n = 0;
//    char ch;
//    int temp;
//
//    while (1)
//    {
//        printf("연산을 실행하시겠습니까?(y / n): ");
//        temp = scanf(" %c", &ch);
//
//        switch (ch)
//        {
//        case 'y':
//        case 'Y':
//            printf("연산에 쓸 숫자의 개수를 입력하세요: ");
//            temp = scanf("%d", &n);
//
//            // 음수 또는 0을 입력한 경우 오류 처리
//            if (n <= 0) {
//                printf("잘못된 입력입니다. 숫자의 개수는 양의 정수이어야 합니다.\n");
//                break;
//            }
//
//            pary = (float*)malloc(n * sizeof(float));
//            operators = (char*)malloc((n - 1) * sizeof(char));
//            if (pary == NULL || operators == NULL) {
//                printf("메모리 할당에 실패했습니다.\n");
//                return 1;
//            }
//
//            printf("%d개의 숫자를 입력하세요:\n", n);
//            for (int i = 0; i < n; i++) {
//                printf("숫자 %d: ", i + 1);
//                if (scanf("%f", &pary[i]) != 1) {
//                    printf("잘못된 입력입니다. 숫자를 입력하세요.\n");
//                    free(pary);
//                    free(operators);
//                    pary = NULL;
//                    operators = NULL;
//                    while (getchar() != '\n');
//                    break;
//                }
//            }
//
//            if (pary != NULL) {
//                printf("%d개의 연산자를 입력하세요 (+, -, *, / 중 하나):\n", n - 1);
//                for (int i = 0; i < n - 1; i++) {
//                    printf("연산자 %d: ", i + 1);
//                    temp = scanf(" %c", &operators[i]);
//                    if (operators[i] != '+' && operators[i] != '-' && operators[i] != '*' && operators[i] != '/') {
//                        printf("잘못된 입력입니다. 올바른 연산자를 입력하세요.\n");
//                        free(pary);
//                        free(operators);
//                        pary = NULL;
//                        operators = NULL;
//                        while (getchar() != '\n');
//                        break;
//                    }
//                }
//
//                if (operators != NULL) {
//                    operate_arith(pary, operators, n); // 연산 수행
//                    free(pary); // 메모리 해제
//                    free(operators);
//                    pary = NULL;
//                    operators = NULL;
//                }
//            }
//
//            break;
//
//        case 'n':
//        case 'N':
//            printf("프로그램을 종료합니다.\n");
//            return 0;
//
//        default:
//            printf("'y' 또는 'n'에서 입력해 주세요\n");
//            break;
//        }
//
//        // 입력 버퍼 정리
//        while (getchar() != '\n');
//    }
//
//    return 0;
//}
//
//// 산술 연산 수행 함수
//void operate_arith(float* pary, char* operators, int n)
//{
//    float result = pary[0]; // 초기값 설정
//    char prev_op = '+'; // 이전 연산자 초기값 설정
//
//    for (int i = 1; i < n; i++)
//    {
//        switch (operators[i - 1])
//        {
//        case '*':
//            result *= pary[i];
//            break;
//
//        case '/':
//            // 0으로 나눌 때 오류 처리
//            if (pary[i] != 0) {
//                result /= pary[i];
//            }
//            else {
//                printf("0으로 나눌 수 없습니다.\n");
//                return;
//            }
//            break;
//
//        case '+':
//        case '-':
//            // 현재 연산자와 이전 연산자를 비교하여 우선 순위에 따라 연산 수행
//            if (prev_op == '+') {
//                result += pary[i];
//            }
//            else if (prev_op == '-') {
//                result -= pary[i];
//            }
//            break;
//
//        default:
//            printf("잘못된 연산 기호입니다. 다시 입력하세요.\n");
//            return;
//        }
//
//        prev_op = operators[i - 1]; // 현재 연산자를 이전 연산자로 설정
//    }
//
//    printf("최종 결과: %g\n", result);
//}
