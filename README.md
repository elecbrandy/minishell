# minishell

## 05.17

### libft 수정
- ft_strjoin free(s1)제거

### Makefile 수정
- c파일 추가

### parsing 수정
- $표시부분 환경변수로 치환완료 ($?는 어떤식으로 해야할지 생각, $$도 미정)
- 주석을 제외한 모든 부분 norm검사 통과
- node->path 추가(빌트인 함수를 제외하고 path가 없으면 에러처리로 할 예정)

### headerfile
- 전역변수 int g_errnum 추가

### main file
- 주석 처리를 제외한 부분 norm 통과를 위해 함수 분할
- errornum 작업중 / command not found와 몇몇 에러 출력은 stderror, perror로는 안됨(직접 출력해야하는듯함)

### 3. fd 설정
- head free 할때 node안에 있는 in,out fd 모두 close
- cat << a heredoc이 안읽힘 , fd가 3부터 시작을 안하는 경우?????

### ~~1. 의문의 엔터 (완)~~
- 미니쉘 진입 후 예를 들어 `cat a.txt`시 결과가 나온 이후 다시 nimishell$ 문구와 함께 명령어를 입력하려면 엔터를 한번 더 쳐야 진입이 가능했던 것
- 파이프가 없을 경우 자식 프로세서를 기다리지않고 부모프로세서가 먼저 시작해서 그런 경우 -> **`wait_process`를 통해서 자식 프로세서가 끝나는 것을 기다리고 실행되게 끔 수정**

### ~~2. 의문의 종료~~
- 파이프를 여러 개 사용했을시 결과 출력 후 바로 종료되는 문제
- `minishell.c`의 142줄 주석 처리 시 무한반복
- **`fork_process` 종료 전 다음 명령어 실행을 위해 입출력 fd를 초기화해서 해결한듯?**

### 3. fd 설정?
- 자식 프로세스에서 `redirect_io(node->in_fd, node->out_fd);` 함수를 통해 노드의 입출력을 그대로 적용하고 있는데, 노드의 내용을 보니 0번 노드 이후로 in_fd와 out_fd 모두 1로 찍혀있는 듯
- 그래서 자식 프로세스에서 노드 입출력을 적용할 경우 통신이 끊겨 무한 로딩 나는 경우 발생
- 해당 함수 주석 처리하고, 리다이렉션 없는 경우 정상 동작

### 4. libft 수정
- strjoin free(s1)제거

### Makefile 수정
- c파일 추가

### parsing 수정
- $표시부분 환경변수로 치환
- 주석을 제외한 거의 모든 부분 norm검사 통과
- node->path 추가(빌트인 함수를 제외하고 path가 없으면 에러처리로 할 예정)
