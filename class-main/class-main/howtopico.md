좋습니다. 지금 프로젝트 기준으로, “새 C 파일 만들기 → CMake에 연결 → 빌드 결과 확인”까지를 가장 쉬운 흐름으로 정리해드릴게요.

기준 위치

소스(코드) 작업 폴더: pico_project
빌드 폴더(생성물): build_pico2w
빌드 설정 파일: CMakeLists.txt
핵심 개념 3개

소스 폴더와 빌드 폴더는 분리해서 사용합니다.
C 파일을 새로 만들면, 보통 CMakeLists에 연결을 추가해야 빌드에 포함됩니다.
빌드 산출물은 소스 폴더가 아니라 build_pico2w에 생성됩니다.
가장 쉬운 작업 순서

새 파일은 pico_project 안에 만듭니다.
CMakeLists.txt에서 새 파일을 타깃에 포함시킵니다.
빌드 폴더에서 다시 빌드합니다.
명령 예시(프로젝트 루트에서):
cmake -S . -B build_pico2w
cmake --build build_pico2w -j

질문하신 포인트별 정리

새 파일은 어디에 만들까?
현재 구조에서는 pico_project 바로 아래에 두는 것이 가장 단순합니다.
파일이 많아지면 하위 폴더를 만들어 관리해도 됩니다. 단, 그 경우 CMakeLists에서 경로를 정확히 써야 합니다.
경로는 어디로 지정할까?
CMake에서 소스 경로는 보통 프로젝트 루트 기준 상대경로를 씁니다.
현재 CMake는 APP_SOURCE 변수를 사용하므로, 새 메인 파일을 쓰고 싶으면 APP_SOURCE를 새 파일명으로 바꾸거나 빌드 시 -D 옵션으로 넘기면 됩니다.
CMakeLists 수정이 꼭 필요할까?
대부분 필요합니다.
“새 파일이 기존 실행파일에 포함되어야 하는 경우”는 거의 항상 CMakeLists에 추가/변경이 필요합니다.
예외는, 이미 와일드카드/자동수집 방식으로 작성된 프로젝트인데 현재 파일은 그런 방식이 아닙니다.
빌드 파일은 어디에 생길까?
전부 build_pico2w에 생깁니다.
예: my_project.elf, my_project.uf2, 오브젝트 파일들
파일 하나 만들 때마다 빌드 폴더가 새로 생기나?
아니요. 보통 빌드 폴더는 프로젝트/보드별로 하나를 계속 재사용합니다.
파일을 추가해도 기존 build_pico2w 안에서 증분 빌드됩니다.
보드가 다르면 별도 빌드 폴더를 새로 두는 게 좋습니다(예: build_pico, build_pico2w).
실전 케이스 3가지

기존 메인 파일을 새 파일로 교체
CMakeLists.txt에서 APP_SOURCE 기본값을 바꾸거나
빌드할 때 다음처럼 지정:
cmake -S . -B build_pico2w -DAPP_SOURCE=새파일이름.c
cmake --build build_pico2w -j
기존 실행파일에 새 보조 C 파일 추가
CMakeLists의 add_executable 목록에 파일을 추가하거나 target_sources를 사용해 추가해야 합니다.
추가 후 빌드하면 같은 my_project 타깃에 함께 링크됩니다.
새 파일을 아예 다른 실행파일로 빌드
CMakeLists에 add_executable(새타깃 ...)을 별도로 만들고
필요한 라이브러리 링크, pico_add_extra_outputs도 새 타깃 기준으로 추가합니다.
그러면 build_pico2w에 새 타깃 산출물이 함께 생깁니다.
원하시면 다음 단계로, 지금 프로젝트에 맞춰

단일 파일 교체 방식
보조 파일 추가 방식
새 실행파일 추가 방식
이 3가지를 실제 CMakeLists 예시 코드로 바로 작성해드리겠습니다.