# Minishell

## Contributors
>**피어코딩으로 같이 작성**
<table align="center">
<tbody>
    <td align="center">
        <a href="https://github.com/bigeaglesman">
            <img src="https://avatars.githubusercontent.com/bigeaglesman" width="200px;" height="200px;" alt="조영호"/>
            <h3><b>조영호</b></h3>
        </a>
    </td>
    <td align="center">
        <a href="https://github.com/yoonc01">
            <img src="https://avatars.githubusercontent.com/u/143938662?v=4" width="200px;" height="200px;" alt="윤효준"/>
            <h3><b>윤효준</b></h3>
        </a>
    </td>
</tbody>
</table>

## 📝 프로젝트 소개
**Minishell**은 42 Seoul의 과제로, 기본적인 UNIX 쉘의 기능을 C 언어로 구현하는 프로젝트입니다. 이를 통해 쉘의 동작 원리를 이해하고, 시스템 호출 및 프로세스 관리를 학습하는 것을 목표로 합니다.

## 🎯 주요 기능
Minishell은 다음과 같은 기능을 지원합니다:

- **명령어 실행**: 사용자가 입력한 명령어를 실행합니다.
- **환경 변수 처리**: `$`로 시작하는 환경 변수를 지원합니다.
- **빌트인 명령어**:
  - `echo` (옵션: `-n`)
  - `cd` (상대경로 및 절대경로)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **리다이렉션**:
  - 입력 리다이렉션: `<`
  - 출력 리다이렉션: `>`
  - 출력 추가 모드 리다이렉션: `>>`
  - 히어독(Heredoc): `<<`
- **파이프라인**: `|`를 사용하여 명령어의 출력을 다음 명령어의 입력으로 연결합니다.
- **시그널 처리**: `Ctrl+C`, `Ctrl+D`, `Ctrl+\` 등의 시그널을 처리합니다.
- **명령어 역사 관리**: 이전에 입력한 명령어의 기록을 관리합니다.

## 📂 디렉토리 구조
```
Re_minishell/
├── .github/ # GitHub 관련 설정 파일
├── .vscode/ # VSCode 설정 파일
├── includes/ # 헤더 파일
├── lib/
│ └── libft/ # Libft 라이브러리
├── src/ # 소스 코드
├── .gitignore # Git 무시 파일 목록
├── Makefile # 빌드 설정 파일
└── env_rule.txt # 환경 변수 규칙 파일 및 feature 정리
```

## 🚀 빌드 및 실행 방법
1. **프로젝트 클론**
```bash
git clone https://github.com/yoonc01/Re_minishell.git
cd Re_minishell
```
2. **빌드**
```bash
make
```
3. **실행**
```
./minishell
```
