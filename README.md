# 영화관 좌석 예약 시스템

## 소개
영화관 좌석 예약 시스템은 사용자가 로그인하여 영화관 좌석을 예약하거나 취소할 수 있는 C 언어 기반 프로그램입니다. 프로그램은 사용자 인증을 통해 보안을 유지하며, 좌석 현황을 실시간으로 확인할 수 있습니다. 예약 상태는 파일로 저장 및 불러오기 기능을 제공하여 지속적인 데이터 관리를 지원합니다.

---

## 주요 기능
### 1. 로그인 기능
- **사용자 ID와 비밀번호 입력 후 로그인**
- 사용자 정보는 이진 탐색을 통해 빠르게 검색하여 인증 속도를 높였습니다.
- 로그인에 성공하면 사용자의 ID 번호가 반환되어 예약과 취소에 사용됩니다.

### 2. 좌석 확인 기능
- 영화관 좌석 현황을 3행 5열로 출력합니다.
- 빈 좌석은 `O`로 표시되고, 예약된 좌석은 사용자 ID 번호로 표시됩니다.

### 3. 좌석 예약 기능
- 사용자는 원하는 좌석(예: A2)을 입력하여 예약할 수 있습니다.
- 이미 예약된 좌석이거나 잘못된 입력인 경우 오류 메시지를 출력합니다.

### 4. 예약 취소 기능
- 사용자는 예약한 좌석(예: A2)을 선택하여 예약을 취소할 수 있습니다.
- 본인의 예약만 취소할 수 있으며, 잘못된 입력 시 오류 메시지를 출력합니다.

### 5. 파일 저장 및 불러오기
- 프로그램 실행 시 `user_data.txt`와 `reservation_data.txt` 파일로부터 사용자 정보와 좌석 예약 현황을 불러옵니다.
- 프로그램 종료 시 `reservation_data.txt` 파일에 현재 좌석 예약 상태를 저장합니다.

---

## 파일 형식
### `user_data.txt` (사용자 정보 파일)
- 사용자 ID, ID 번호, 비밀번호 정보를 저장합니다.
- 각 줄은 다음 형식으로 구성됩니다:
<id_num> <id> <password>

diff
코드 복사
- 예시:
1 user1 pass1 2 user2 pass2

diff
코드 복사

### `reservation_data.txt` (좌석 예약 파일)
- 좌석 예약 상태를 3행 5열 형식으로 저장합니다.
- 각 줄은 해당 행의 좌석 상태를 나타내며, 빈 좌석은 `0`, 예약된 좌석은 사용자 ID 번호로 표시됩니다.
- 예시:
0 0 1 0 0 2 0 0 0 0 0 0 0 0 3

yaml
코드 복사

---

## 사용 방법
1. **프로그램 실행**
./reservation_system

markdown
코드 복사
2. **로그인**
- ID와 비밀번호를 입력하여 로그인합니다.
3. **메뉴 선택**
1---좌석확인하기 2---예약하기 3---예약취소하기 4---다른 사용자로 로그인하기 5---종료하기

markdown
코드 복사
4. **좌석 예약 및 취소**
- 원하는 좌석(예: A2)을 입력하여 예약 또는 취소합니다.
5. **종료**
- 프로그램 종료 시 `reservation_data.txt` 파일에 좌석 상태가 저장됩니다.

---

## 빌드 및 실행
1. **컴파일**
gcc -o reservation_system reservation_system.c

markdown
코드 복사
2. **실행**
./reservation_system

yaml
코드 복사

---

## 참고 사항
- 사용자 정보 파일(`user_data.txt`)과 좌석 예약 파일(`reservation_data.txt`)이 동일한 디렉토리에 있어야 정상적으로 동작합니다.
- 사용자 ID는 최대 10명까지 지원하며, 좌석은 3행 5열(총 15석)으로 제한됩니다.

![image](https://github.com/user-attachments/assets/28467716-dcb3-47f3-96a9-d3bb02800bef)


