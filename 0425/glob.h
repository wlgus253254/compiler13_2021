/*
 * glob.h - global variable for the project
 * programmer - ������, ���Ͽ�, ������
 * date -
 */

 // Symbol table ����
#define STsize 1000 // size of string table

int nextid; // identifier�� ù���ڰ� �ִ� string table �ε���
int nextfree; // identifier ���� ����ִ� string table �ε���

char ST[STsize]; // string table

// �� �� global ������
typedef enum _boolean {
	FALSE,
	TRUE
} boolean;
#define FALSE 0
#define TRUE 1

int lineNum; // line���� �����ִ� ����
enum tokentypes tn;
boolean STindex; // ST index�� ����ϴ� Identifier�� TRUE

enum errorTypes { illsp, illid, overst, notallowed, toolong }; //errortype �߰�
typedef enum errorTypes ERRORtypes;
ERRORtypes err; // ����Ÿ�� ���������� ����
int cErrors; // ���� ���� ����

int notallowed_i; // notallowedpositon[] �ε���
int notallowedposition[12]; // identifier���� ������ ���� character�� string table�� �ε����� ����