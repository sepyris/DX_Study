DX
- c++/DX를 이용하여 개인이 만든 메이플스토리 기본이동 및 미니게임

 스타브릿지
 
-10*12의 별을 랜덤한 정해진 위치에 맞게 별을 잇는 미니게임

 러닝미니게임
 
 -캐릭터가 자동으로 달리기 시작하며 점프,2단점프,숙이기를 이용하여
 
 발판이나 장애물을 건너 뛰는 미니게임

 계기
 
 메이플스토리에서 제일 인상깊었던 미니게임인 스타브릿지를 구현
 
 또한 라이브서버에서 해봤으면 좋겠는 미니게임인 러닝미니게임을 구현


문제:스타브릿지에서 별의 위치를 랜덤으로 생성하게 하는 로직에 문제가 발생

확인:최소 거리,이전 별과의 각도등을 고려하여 로직 작성하고 보니 맵은 나오는것을 확인 하였으나

긴 선 사이에 짧은 선이 생겨 미니맵으로 확인이 힘들며 디버그로 선을 보고 해도 알아보기 힘든 문제가 발생

해결:랜덤으로는 다시 문제가 생길 가능성이 높아 고정된 이미지 10개중 랜덤으로 나오게 설정


문제:스타브릿지에서실패하였으나 별의 이미지가 변경되어있는 상태가 발생

확인:실패시 이전의 이미지로 변경하는 방법을 사용하기 위해

이전상태를 저장하는 변수를 생성하였으나 초기화를 하지 않아서 이미지가 변경 되는 문제 
      
해결:상태저장 변수 초기화


문제:스타브릿지 스테이지 종료후 다음 이미지로 넘어간후 이전 이미지에서 완료 상태가 되는 별로 실패시

이미지가 변경 되는 문제
      
확인:다음 이미지로 넘어갈시 별의 상태를 원래대로 돌리게 하였으나

상태저장 변수가 그대로 여서 문제 발생
      
해결:스테이지를 넘어갈시 상태저장 변수도 초기화

​<img width="400" height="300" alt="스타브릿지1" src="https://github.com/user-attachments/assets/90b13194-f855-4108-9e52-40be3bb5d745" />
<img width="230" height="222" alt="스타브릿지2" src="https://github.com/user-attachments/assets/dc16851b-56c9-400f-86d3-884394608028" />
<img width="275" height="282" alt="스타브릿지3" src="https://github.com/user-attachments/assets/024c314c-9c22-4a6a-be0a-2f7dbf5d20bc" />
<img width="400" height="300" alt="스타브릿지4" src="https://github.com/user-attachments/assets/ffd85980-b358-4aec-b1ac-61f6bf112e63" />
<img width="904" height="418" alt="starbridge" src="https://github.com/user-attachments/assets/ac55967a-8782-489f-b3cf-27f530dc7eb8" />
<img width="400" height="300" alt="러닝1" src="https://github.com/user-attachments/assets/38a1923e-64f2-4354-ba85-adc7aa12d077" />
<img width="400" height="300" alt="러닝2" src="https://github.com/user-attachments/assets/5c535604-6836-41d3-856c-66dff58739aa" />
